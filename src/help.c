#include <stdio.h>
#include "ui.h"

#define VERSION 1.0

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
    printf("    " C_WHITE "sysmate <command>" C_RESET "\n");
    printf("    " C_WHITE "sysmate delete <index>" C_RESET "\n");
    printf("    " C_WHITE "sysmate doctor-dev" C_RESET "\n\n");

    /* Commands */  
    printf(C_GREEN "  COMMANDS\n" C_RESET);
    printf("    " C_CYAN "update"      C_RESET "  Update and upgrade system\n");
    printf("    " C_CYAN "clean"       C_RESET "   Clean unused packages\n");
    printf("    " C_CYAN "ls"          C_RESET "      List files and build .sysmate_index\n");
    printf("    " C_CYAN "delete"      C_RESET "  Delete file by index\n");
    printf("    " C_CYAN "doctor-dev"  C_RESET " Check development tools\n");
    printf("    " C_CYAN "help"        C_RESET "    Show help menu\n");
    printf("    " C_CYAN "version"     C_RESET " Show tool version\n\n");

    /* Shortcuts */
    printf(C_GREEN "  SHORTCUTS\n" C_RESET);
    printf("    " C_CYAN "-u" C_RESET "          update\n");
    printf("    " C_CYAN "-c" C_RESET "          clean\n");
    printf("    " C_CYAN "-d" C_RESET "          delete\n");
    printf("    " C_CYAN "-h" C_RESET "          help\n");
    printf("    " C_CYAN "-dd" C_RESET "         doctor-dev\n\n");
    printf("    " C_CYAN "-v" C_RESET "          version\n\n");

    /* Examples */
    printf(C_GREEN "  EXAMPLES\n" C_RESET);
    printf("    " C_WHITE "sysmate update" C_RESET "\n");
    printf("    " C_WHITE "sysmate clean" C_RESET "\n");
    printf("    " C_WHITE "sysmate ls" C_RESET "\n");
    printf("    " C_WHITE "sysmate delete 3" C_RESET "\n");
    printf("    " C_WHITE "sysmate doctor-dev" C_RESET "\n\n");

    /* Notes */
    printf(C_GREEN "  NOTES\n" C_RESET);
    printf("    " C_WHITE "Run 'sysmate ls' before using delete." C_RESET "\n");
    printf("    " C_WHITE "'delete' uses the index stored in .sysmate_index." C_RESET "\n");
    printf("    " C_WHITE "'doctor-dev' checks core development tools." C_RESET "\n\n");

    return 0;
}

int version(void)
{
    printf("sysmate version %.1f\n", VERSION);
    return 0;
}