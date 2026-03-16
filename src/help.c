#include <stdio.h>

/* Colors */
#define C_RESET "\033[0m"
#define C_CYAN "\033[1;36m"
#define C_GREEN "\033[1;32m"
#define C_YELLOW "\033[1;33m"

void print_help(void)
{
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

    printf(C_YELLOW);
    printf("┌────────────────────────────────────────────┐\n");
    printf("│                SYSMATE HELP                │\n");
    printf("└────────────────────────────────────────────┘\n");
    printf(C_RESET);

    printf("\n");

    /* Usage */
    printf(C_GREEN "USAGE\n" C_RESET);
    printf("┌────────────────────────────────────────────┐\n");
    printf("│ sysmate <command>                          │\n");
    printf("└────────────────────────────────────────────┘\n");

    printf("\n");

    /* Commands */
    printf(C_GREEN "COMMANDS\n" C_RESET);

    printf("┌──────────┬─────────────────────────────────┐\n");
    printf("│ Command  │ Description                     │\n");
    printf("├──────────┼─────────────────────────────────┤\n");

    printf("│ " C_CYAN "update" C_RESET "   │ Update and upgrade system       │\n");
    printf("│ " C_CYAN "clean" C_RESET "    │ Clean unused packages           │\n");
    printf("│ " C_CYAN "ls" C_RESET "       │ List files in current directory │\n");
    printf("│ " C_CYAN "help" C_RESET "     │ Show help menu                  │\n");
    printf("│ " C_CYAN "version" C_RESET "  │ Show tool version               │\n");

    printf("└──────────┴─────────────────────────────────┘\n");

    printf("\n");

    /* Examples */
    printf(C_GREEN "EXAMPLES\n" C_RESET);

    printf("┌──────────────────────┬──────────────────────┐\n");
    printf("│ Command              │ Action               │\n");
    printf("├──────────────────────┼──────────────────────┤\n");
    printf("│ sysmate update       │ Update system        │\n");
    printf("│ sysmate clean        │ Clean system         │\n");
    printf("│ sysmate ls           │ List files           │\n");
    printf("└──────────────────────┴──────────────────────┘\n");

    printf("\n");
}