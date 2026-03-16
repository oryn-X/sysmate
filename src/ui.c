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

    printf("\033[38;5;82m[OK]%s\033[0m Mode: \n", mode);
}

void print_status(const char *status, int is_erorr)
{

    if (is_erorr == 0)
    {
        printf("\033[38;5;82m%s\033[0m\n", status);
    }
    else if (is_erorr == 1)
    {
        printf("\033[38;5;196m%s \033[0m\n", status);
    }
}

void print_unknown_command(const char *command)
{
    printf("Unknown command: %s\n", command);
    print_usage();
}
