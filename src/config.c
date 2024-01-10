#include <stdio.h>
#include "config.h"

void config_init(Config *config) {
    config->log_file = NULL;
    config->log_stdout = NULL;
    config->log_stderr = NULL;
    config->log_syslog = NULL;
}

void config_enable_log_file(Config *config, const char *path) {
    FILE *fd = fopen(path, "a+");
    config->log_file = fd;
    if (!fd) {
        perror("fopen log file");
    }
}

void config_enable_log_stdout(Config *config) {
    config->log_stdout = stdout;
}

void config_enable_log_stderr(Config *config) {
    config->log_stderr = stderr;
}

void config_enable_log_syslog(Config *config) {
    fprintf(stderr, "TODO: logging to syslog not yet implemented...\n");
}
//     self.output.append((f'config_enable_log_file(config, "{path}");\n'))
// if stderr:
//     self.output.append(("config_enable_log_stderr(config);\n"))
// if stdout:
//     self.output.append(("config_enable_log_stdout(config);\n"))
// if syslog:
//     self.output.append(("config_enable_log_syslog(config);\n"))
