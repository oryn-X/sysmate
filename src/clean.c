#include <stdio.h>
#include <stdlib.h>

#include "system_ops.h"
#include "ui.h"


int handle_clean(void)
{
    print_mode("clean");
    int clean_failed = 0;

    /* Before cleaning */
    run_info("Showing disk usage" C_RESET, "df -h");

    /* Core cleanup */
    if (run_system("Cleaning apt cache" C_RESET, "sudo apt clean && sudo apt autoclean") != 0)
        clean_failed = 1;
    if (run_system("Removing unused packages" C_RESET, "sudo apt autoremove -y") != 0)
        clean_failed = 1;
    if (run_system("Fixing broken packages" C_RESET, "sudo apt --fix-broken install -y") != 0)
        clean_failed = 1;

    /* Logs cleanup */
    if (run_system("Cleaning system logs (limit size)" C_RESET, "sudo journalctl --vacuum-size=100M") != 0)
        clean_failed = 1;
    // if (run_system("Clearing user cache" C_RESET, "rm -rf ~/.cache/*") != 0)
    //  clean_failed = 1;
    /* User cache cleanup */
    if (run_system("Clearing thumbnails" C_RESET, "rm -rf ~/.cache/thumbnails/*") != 0)
        clean_failed = 1;
    if (run_system("Clearing pip cache" C_RESET, "rm -rf ~/.cache/pip") != 0)
        clean_failed = 1;

    /* Optional cleanup */
    run_info("Cleaning unused Flatpak packages" C_RESET, "command -v flatpak >/dev/null && flatpak uninstall --unused -y");
    run_info("Cleaning old Snap versions" C_RESET, "command -v snap >/dev/null && sudo snap set system refresh.retain=2");

    /* After cleaning */
    run_info("Showing disk usage after cleaning" C_RESET, "df -h");

    if (clean_failed)
        return 1;

    print_status("\nSystem cleaned successfully.\n", 0);
    return 0;
}


/* Run in CMD */
int run_system(const char *msg, const char *cmd)
{

    print_status(msg, 0);

    int result = system(cmd);

    if (result != 0)
    {
        print_status("[FAILED]\n", 1);
        return 1;
    }

    return 0;       
}

/* For Warning messages */
int run_info(const char *msg, const char *cmd)
{
    print_status(msg, 0);
    int result = system(cmd);

    if (result != 0)
    {
        printf(C_YELLOW "[WARNING]\n" C_RESET);
        return 1;
    }

    return 0;
}