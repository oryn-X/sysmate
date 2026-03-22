#include <stdio.h>
#include "ui.h"

#define VERSION "1.0.0"

int print_help(void)
{
    printf("\033[2J\033[H\n");

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
    printf(C_YELLOW "   ⚡ SYSMATE v%s\n" C_RESET, VERSION);
    printf(C_YELLOW "   ─────────────────────────────\n\n" C_RESET);

    /* Description */
    printf(C_WHITE "   A fast Linux system helper for developers.\n\n" C_RESET);

    /* Usage */
    printf(C_GREEN "   USAGE\n" C_RESET);
    printf("     " C_WHITE "sysmate <command>\n");
    printf("     sysmate delete <index>\n");
    printf("     sysmate doctor-dev\n\n" C_RESET);

    /* Commands */
    printf(C_GREEN "   COMMANDS\n" C_RESET);
    printf("     " C_CYAN "update        " C_RESET "→ Update & upgrade system\n");
    printf("     " C_CYAN "clean         " C_RESET "→ Remove unused packages\n");
    printf("     " C_CYAN "ls            " C_RESET "→ List files & create index\n");
    printf("     " C_CYAN "delete <id>   " C_RESET "→ Delete file by index\n");
    printf("     " C_CYAN "doctor-dev    " C_RESET "→ Check dev environment\n");
    printf("     " C_CYAN "help          " C_RESET "→ Show this menu\n");
    printf("     " C_CYAN "version       " C_RESET "→ Show version\n\n");

    /* Shortcuts */
<<<<<<< HEAD
    printf(C_GREEN "  SHORTCUTS\n" C_RESET);
    printf("    " C_CYAN "-u" C_RESET "          update\n");
    printf("    " C_CYAN "-c" C_RESET "          clean\n");
    printf("    " C_CYAN "-d" C_RESET "          delete\n");
    printf("    " C_CYAN "-h" C_RESET "          help\n");
    printf("    " C_CYAN "-dd" C_RESET "         doctor-dev\n\n");
    printf("    " C_CYAN "-v" C_RESET "          version\n\n");
=======
    printf(C_GREEN "   SHORTCUTS\n" C_RESET);
    printf("     " C_CYAN "-u   " C_RESET "update\n");
    printf("     " C_CYAN "-c   " C_RESET "clean\n");
    printf("     " C_CYAN "-d   " C_RESET "delete\n");
    printf("     " C_CYAN "-h   " C_RESET "help\n");
    printf("     " C_CYAN "-v   " C_RESET "version\n\n");
>>>>>>> 0e6e8c8 (help file)

    /* Examples */
    printf(C_GREEN "   EXAMPLES\n" C_RESET);
    printf("     " C_WHITE "sysmate update\n");
    printf("     sysmate clean\n");
    printf("     sysmate ls\n");
    printf("     sysmate delete 3\n");
    printf("     sysmate doctor-dev\n\n" C_RESET);

    /* Notes */
    printf(C_GREEN "   NOTES\n" C_RESET);
    printf("     " C_WHITE "• Run 'sysmate ls' before delete\n");
    printf("     • Uses .sysmate_index for tracking files\n");
    printf("     • doctor-dev checks essential tools\n\n" C_RESET);

    /* Links */
    printf(C_GREEN "   LINKS\n" C_RESET);
    printf("     " C_WHITE "GitHub  : https://github.com/oryn-X/sysmate\n");
    printf("     Discord : https://discord.gg/v38BhC8f\n");
    printf("     Website : https://gorootaccess.com (coming soon)\n\n" C_RESET);

    /* Developers */
    printf(C_GREEN "   DEVELOPERS\n" C_RESET);
    printf("     " C_WHITE "• oryn-X\n");
    printf("     • Mohamed Abdelsamea\n");
    printf("     • Mohamed Hany\n\n" C_RESET);

    /* Organization */
    printf(C_GREEN "   ORGANIZATION (ROOT ACCESS)\n" C_RESET);
    printf("     " C_WHITE "An open-source community building tools for developers.\n");
    printf("     We focus on automation, productivity, and real-world solutions.\n\n" C_RESET);

    return 0;
}

int version(void)
{
    printf("sysmate version %s\n", VERSION);
    return 0;
}