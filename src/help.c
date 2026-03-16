#include <stdio.h>

void print_help(void)
{
    printf("\033[3J");
    printf("\033[2J");
    printf("\033[H");
    printf("\n");
    /* Logo */
    printf("\033[1;36m");
    printf("   ███████╗██╗   ██╗███████╗███╗   ███╗ █████╗ ████████╗███████╗\n");
    printf("   ██╔════╝╚██╗ ██╔╝██╔════╝████╗ ████║██╔══██╗╚══██╔══╝██╔════╝\n");
    printf("   ███████╗ ╚████╔╝ ███████╗██╔████╔██║███████║   ██║   █████╗  \n");
    printf("   ╚════██║  ╚██╔╝  ╚════██║██║╚██╔╝██║██╔══██║   ██║   ██╔══╝  \n");
    printf("   ███████║   ██║   ███████║██║ ╚═╝ ██║██║  ██║   ██║   ███████╗\n");
    printf("   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝\n");
    printf("\033[0m\n");

    printf("\033[1;33m");
    printf("┌──────────────────────────────────────────────────────────────┐\n");
    printf("│                    SYS MATE CLI HELP                         │\n");
    printf("└──────────────────────────────────────────────────────────────┘\n");
    printf("\033[0m\n");

    printf("\033[1;32mUsage:\033[0m\n");
    printf("  sysmate <command>\n\n");

    printf("\033[1;33mCommands:\033[0m\n");

    printf("┌──────────────┬───────────────────────────────────────────────┐\n");
    printf("│ Command      │ Description                                   │\n");
    printf("├──────────────┼───────────────────────────────────────────────┤\n");
    printf("│ update       │ Update and upgrade the system                 │\n");
    printf("│ clean        │ Remove unused packages and system cache       │\n");
    printf("│ ls           │ List files in the current directory           │\n");
    printf("│ --help       │ Show help information                         │\n");
    printf("│ --ver        │ Show tool version                             │\n");
    printf("└──────────────┴───────────────────────────────────────────────┘\n\n");

    printf("\033[1;33mExamples:\033[0m\n");

    printf("┌─────────────────────────────────────────────┐\n");
    printf("│ sysmate update                              │\n");
    printf("│ sysmate clean                               │\n");
    printf("│ sysmate ls                                  │\n");
    printf("└─────────────────────────────────────────────┘\n\n");

    printf("\033[1;34mTip:\033[0m Run with sudo for full system access\n\n");
}