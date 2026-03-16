#include <stdio.h>
#include "ui.h"
#define VERSION 1.0
/* Colors */


// help
int print_help(void)
{
    printf("\033[2J\033[H");
    printf("\n");

    /* Logo */
    printf(C_CYAN);
    printf("   ███████╗██╗   ██╗███████╗███╗   ███╗ █████╗ ████████╗███████╗\n");
    printf("   ██╔════╝╚██╗ ██╔╝██╔════╝████╗ ████║██╔══██╗╚══██╔══╝██╔════╝\n");
    printf("   ███████╗ ╚████╔╝ ███████╗██╔████╔██║███████║   ██║   █████╗  \n");
    printf("   ╚════██║  ╚██╔╝  ╚════██║██║╚██╔╝██║██╔══██║   ██║   ██╔══╝  \n");
    printf("   ███████║   ██║   ███████║██║ ╚═╝ ██║██║  ██║   ██║   ███████╗\n");
    printf("   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝\n");
    printf(C_RESET);

    printf("\n");

    printf(C_YELLOW "  SYSMATE HELP\n" C_RESET);
    printf(C_YELLOW "  ────────────\n\n" C_RESET);

    /* Usage */
    printf(C_GREEN "  USAGE\n" C_RESET);
    printf("    " C_WHITE "sysmate <command>" C_RESET "\n\n");

    /* Commands */
    printf(C_GREEN "  COMMANDS\n" C_RESET);
    printf("    " C_CYAN "update" C_RESET "     Update and upgrade system\n");
    printf("    " C_CYAN "clean" C_RESET "      Clean unused packages\n");
    printf("    " C_CYAN "ls" C_RESET "         List files in current directory\n");
    printf("    " C_CYAN "help" C_RESET "       Show help menu\n");
    printf("    " C_CYAN "version" C_RESET "    Show tool version\n\n");

    /* Shortcuts */
    printf(C_GREEN "  SHORTCUTS\n" C_RESET);
    printf("    " C_CYAN "-u" C_RESET "          update\n");
    printf("    " C_CYAN "-c" C_RESET "          clean\n");
    printf("    " C_CYAN "-h" C_RESET "          help\n");
    printf("    " C_CYAN "-v" C_RESET "          version\n\n");

    return 0;
}
// sysmate version
int version(void)
{
    printf("sysmate version %0.1f\n", VERSION);
    return 0;
}