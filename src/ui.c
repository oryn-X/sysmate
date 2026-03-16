#include <stdio.h>

#include "ui.h"

/* Colors */


void print_usage(void)
{
    printf("Try:\n");
    printf("  sysmate --help \n");
    printf("  sysmate --version\n");
}

void print_mode(const char *mode)
{
    printf(C_BPURPLE "[OK] Mode: %s\n" C_RESET, mode);
}

void print_status(const char *status, int is_erorr)
{
    if (is_erorr == 0)
    {
        // successfully = 0
        printf(C_GREEN "%s\033[0m\n", status);
    }
    else if (is_erorr == 1)
    {
        // Erorr = 1
        printf(C_RED "%s\n" C_RESET, status);
    }
}

void print_unknown_command(const char *command)
{
    printf("Unknown command: %s\n", command);
    print_usage();
}
