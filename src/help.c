#include <stdio.h>
#include "ui.h"

#define VERSION "1.0.0"

/* Print the full help screen. */
int print_help(void)
{
    printf("\033[2J\033[H\n");

    /* Logo  */
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
    printf(C_YELLOW "   ─────────────────────────────────────────────\n\n" C_RESET);

    /* Description */
    printf(C_WHITE "   A modular Linux CLI helper for system tasks, file tools,\n");
    printf("   developer checks, and simple Git workflows.\n\n" C_RESET);

    /* Usage */
    printf(C_GREEN "   USAGE\n" C_RESET);
    printf("     " C_WHITE "sysmate <command>\n");
    printf("     sysmate delete <index>\n");
    printf("     sysmate info <index>\n");
    printf("     sysmate gitsync \"commit message\"\n\n" C_RESET);

    /* Commands */
    printf(C_GREEN "   COMMANDS\n" C_RESET);
    printf("     " C_CYAN "update          " C_RESET "→ Update and upgrade the system\n");
    printf("     " C_CYAN "clean           " C_RESET "→ Clean unused packages and caches\n");
    printf("     " C_CYAN "ls              " C_RESET "→ List files and create .sysmate_index\n");
    printf("     " C_CYAN "ls-l            " C_RESET "→ Long file list with type and permissions\n");
    printf("     " C_CYAN "delete <index>  " C_RESET "→ Delete a file by index\n");
    printf("     " C_CYAN "info <index>    " C_RESET "→ Show detailed information about a file\n");
    printf("     " C_CYAN "doctor-dev      " C_RESET "→ Check development tools and environment\n");
    printf("     " C_CYAN "gitsync <msg>   " C_RESET "→ Add, commit, pull, and push changes\n");
    printf("     " C_CYAN "help            " C_RESET "→ Show this help screen\n");
    printf("     " C_CYAN "version         " C_RESET "→ Show current version\n\n");

    /* Shortcuts */
    printf(C_GREEN "   SHORTCUTS\n" C_RESET);
    printf("     " C_CYAN "-u    " C_RESET "update\n");
    printf("     " C_CYAN "-c    " C_RESET "clean\n");
    printf("     " C_CYAN "-l    " C_RESET "ls\n");
    printf("     " C_CYAN "-ll   " C_RESET "ls-l\n");
    printf("     " C_CYAN "-d    " C_RESET "delete\n");
    printf("     " C_CYAN "-i    " C_RESET "info\n");
    printf("     " C_CYAN "-dd   " C_RESET "doctor-dev\n");
    printf("     " C_CYAN "-gs   " C_RESET "gitsync\n");
    printf("     " C_CYAN "-h    " C_RESET "help\n");
    printf("     " C_CYAN "-v    " C_RESET "version\n\n");

    /* Examples */
    printf(C_GREEN "   EXAMPLES\n" C_RESET);
    printf("     " C_WHITE "sysmate update\n");
    printf("     sysmate clean\n");
    printf("     sysmate ls\n");
    printf("     sysmate ls-l\n");
    printf("     sysmate delete 3\n");
    printf("     sysmate info 3\n");
    printf("     sysmate doctor-dev\n"); 
    printf("     sysmate gitsync \"update readme\"\n\n" C_RESET);

    /* Notes */
    printf(C_GREEN "   NOTES\n" C_RESET);
    printf("     " C_WHITE "• Run 'sysmate ls' before using delete or info\n");
    printf("     • File indexing is stored in .sysmate_index\n");
    printf("     • ls-l shows a compact long-view for files\n");
    printf("     • doctor-dev checks essential development tools\n");
    printf("     • gitsync is intended for Git repositories only\n\n" C_RESET);

    /* Links */
    printf(C_GREEN "   LINKS\n" C_RESET);
    printf("     " C_WHITE "GitHub   : https://github.com/oryn-X/sysmate\n");
    printf("     Discord  : https://discord.gg/v38BhC8f\n");
    printf("     Website  : https://gorootaccess.com (coming soon)\n\n" C_RESET);

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

/* Print the current application version. */
int version(void)
{
    printf(C_CYAN "sysmate" C_RESET " version " C_YELLOW "%s\n" C_RESET, VERSION);
    return 0;
}
