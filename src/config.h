#ifndef SEEAPI_CONFIG_H
#define SEEAPI_CONFIG_H 1

#include <stdio.h>

typedef struct Config {
    FILE *log_file;
    FILE *log_stdout;
    FILE *log_stderr;
    void *log_syslog;
} Config;

struct foo {
    int x;
int y;
};
void config_init(Config *config);

#endif
