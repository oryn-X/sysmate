#include <stdio.h>
#include "ui.h"

/* Print the short command usage summary. */
void print_usage(void)
{
    printf(C_CYAN "Try:\n" C_RESET);
    printf("  sysmate help or sysmate -h\n");
    printf("  sysmate version or sysmate -v\n");
}
 
/* Print the active command mode banner. */
void print_mode(const char *mode)
{
    printf(C_CYAN "[MODE] %s\n" C_RESET, mode);
}
 
/* Print a status line using the requested message style. */
void print_status(const char *status, int is_error)
{
    if (is_error == STATUS_OK)
    {
        printf(C_GREEN "[OK] %s\n" C_RESET, status);
    }
    else if (is_error == STATUS_ERROR)  
    {
        printf(C_RED "[ERROR] %s\n" C_RESET, status);
    }
    else if (is_error == STATUS_INFO)
    {
        printf(C_GREEN "[INFO] %s\n" C_RESET, status);
    }
    else if (is_error == STATUS_PLAIN)
    {
        printf(" %s\n", status);
    }
}

/* Report an unknown command and show the usage hint. */
void print_unknown_command(const char *com)
{
    printf("Unknown command:" C_RED " %s\n" C_RESET, com);
    print_usage();
}
