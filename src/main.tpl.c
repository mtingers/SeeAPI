#include "seeapi.h"
#include "config.h"

int main(int argc, char **argv) {

    // configure
    Config config;
    config_init(&config);

    // placeholder for generated code
    // <|CODE|>

    // runtime
    VirtualMachine vm = vm_init(config);
    vm_run(vm);

    return 0;
}
