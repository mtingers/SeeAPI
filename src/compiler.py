#!/usr/bin/env python
import sys
from pprint import pprint
from ruamel.yaml import YAML
from typing import Callable

from ruamel.yaml.constructor import DuplicateKeyError

MAIN_SETUP = open("main.tpl.c").read()


class Namespace:
    def __init__(self, name: str):
        self.name = name
        self.variables: dict[str, dict[str, str]] = {}
        self.functions: dict[str, dict[str, str]] = {}


class Compiler:
    def __init__(self, path: str):
        self.data: dict = {}
        self.namespaces: list[Namespace] = [Namespace("__main__")]
        self.cur_namespace: Namespace = self.namespaces[0]
        self.output: list[str] = []
        self.compiler_args: list[str] = []
        with open(path) as stream:
            yaml = YAML(typ="safe")
            self.data = yaml.load(stream)

    def parse(self):
        matches = {
            "compiler": {
                "call": self.parse_compiler,
            },
            "import": {
                "call": self.parse_import,
            },
            "routes": {
                "call": self.parse_routes,
            },
            "variables": {
                "call": self.parse_variables,
            },
            "functions": {"call": self.parse_functions},
            "log": {"call": self.parse_log},
            # TODO:
            # "postgres": {"call": self.parse_postgres},
            # "redis": {"call": self.parse_redis},
        }
        for key, value in self.data.items():
            found = False
            func: Callable | None = None
            for match in matches.keys():
                if key.startswith(match):
                    found = True
                    func = matches[match]["call"]
                    break
            if not found:
                raise NameError(f"invalid key: {key}")
            if func:
                func(value | {"__name__": key.split(" ", 1)[1] if " " in key else key})

    def emit(self):
        x = MAIN_SETUP.replace("<|CODE|>", "    \n    ".join(self.output))
        for line in x.split("\n"):
            if line.strip():
                print(line.rstrip())

    def parse_import(self, values):
        pprint(values)

    def parse_compiler(self, values):
        # compiler:
        #   output-name: seeapi-test-basic
        #   cflags: -Wall -O2
        #   ldflags: -L/usr/local/include -lm
        #   ldlibs:
        pprint(values)
        output_name = ""
        for key, value in values.items():
            if value is None:
                continue
            if key == "output-name":
                output_name = value
            elif key in ("output-name", "cflags", "ldflags", "ldlibs"):
                self.compiler_args.append(value.split(" "))

        if not output_name:
            output_name = "seeapi-a.out"
        self.compiler_args.append("-o")
        self.compiler_args.append(output_name)

    def parse_routes(self, values):
        pprint(values)

    def parse_functions(self, values):
        name = values.get("__name__")
        if name in self.cur_namespace.functions:
            raise DuplicateKeyError(
                f"Function '{name}' previously defined in namespace '{self.cur_namespace.name}"
            )
        funcs = {}
        values.pop("__name__")
        for key, value in values.items():
            if key in funcs:
                raise DuplicateKeyError(f"duplicate definition of function '{name}.{key}'")
            funcs[key] = {'orgin': value, 'code': ''}
            args = value.get("args")
            cmod = value.get("cmodule.define")
            return_path = ''
            function_name = ''
            function_args = ''
            if cmod:
                path = cmod.get("path")
                function_name = cmod.get("function-name")
                function_args = cmod.get("function-args")
            for k, v in value.items():
                if k in ('args', 'cmodule.define', 'function-args', 'function-name'):
                    continue
                if k.startswith("<|"):
                    return_path = (k, v)
            funcs[key]['args'] = args
            funcs[key]['cmodule.define'] = cmod
            funcs[key]['return_path'] = return_path
            funcs[key]['function_name'] = function_name
            funcs[key]['function_args'] = function_args
        self.cur_namespace.functions[name] = funcs
        pprint(self.cur_namespace.functions)

    # functions F:
    #   read-version:
    #     args: {path: str}
    #     <|file.read: $path
    #
    #   c-file-example:
    #     args: {value: str}
    #     cmodule.define:
    #       path: filename.c
    #       function-name: echo
    #       function-args: {$value}

    def parse_postgres(self, values):
        pprint(values)

    def parse_log(self, values):
        path: str = values.get("file", "")
        stderr: bool = values.get("stderr", False)
        stdout: bool = values.get("stdout", False)
        syslog: bool = values.get("syslog", False)
        if path:
            self.output.append((f'config_enable_log_file(config, "{path}");\n'))
        if stderr:
            self.output.append(("config_enable_log_stderr(config);\n"))
        if stdout:
            self.output.append(("config_enable_log_stdout(config);\n"))
        if syslog:
            self.output.append(("config_enable_log_syslog(config);\n"))

    def parse_redis(self, values):
        pass

    def parse_variables(self, values):
        pass


if __name__ == "__main__":
    c = Compiler(sys.argv[1])
    c.parse()
    c.emit()
