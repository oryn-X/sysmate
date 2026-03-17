#include <stdio.h>
#include "ui.h"

/* Show basic usage instructions */
void print_usage(void)
{
    printf("Try:\n");
    printf("  sysmate help or sysmate -h\n");
    printf("  sysmate version or sysmate -v\n");
}

/* Print current mode (e.g., ls, clean) */
void print_mode(const char *mode)
{
    printf(C_BPURPLE "[OK] Mode: %s\n" C_RESET, mode);
}

/* Print status message (success or error) */
void print_status(const char *status, int is_error)
{
    if (is_error == 0)
    {
        /* Success message */
        printf(C_GREEN "%s\n" C_RESET, status);
    }
    else if (is_error == 1)
    {
        /* Error message */
        printf(C_RED "%s\n" C_RESET, status);
    }
}

/* Handle unknown command input */
void print_unknown_command(const char *com)
{
    printf("Unknown command: %s\n", com);
    print_usage();
}