#include <stdio.h>

#include "ui.h"

void print_usage(void)
{
    printf("Usage:\n");
    printf("  sysmate update\n");
    printf("  sysmate clean\n");
    printf("  sysmate ls\n");
}

void print_mode(const char *mode)
{
    printf("Mode: %s\n", mode);
}

void print_unknown_command(const char *command)
{
    printf("Unknown command: %s\n", command);
    print_usage();
}
