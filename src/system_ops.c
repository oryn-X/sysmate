#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

// this is for update command START
int handle_update(void)
{

    char command[300];
    print_status("Starting system update...", 0);
    strcpy(command, "sudo apt update && sudo apt full-upgrade -y");
    int result = system(command);
    if (result != 0)
    {
        print_status("System update failed.\n", 1);
        return 1;
    }

    print_status("System update completed.\n", 0);
    return 0;
}

// this is for update command END

int handle_clean(void)
{
    print_mode("clean");

    system("df -h");

    print_status("Cleaning apt cache", 0);
    system("sudo apt clean");

    print_status("Running apt autoclean", 0);
    system("sudo apt autoclean");

    print_status("Removing unused packages", 0);
    system("sudo apt autoremove -y");

    print_status("Clearing user cache", 0);
    system("rm -rf ~/.cache/*");

    print_status("Clearing thumbnails", 0);
    system("rm -rf ~/.cache/thumbnails/*");

    print_status("Cleaning logs", 0);
    system("sudo journalctl --vacuum-time=7d");

    print_status("Clearing temp files", 0);
    system("sudo rm -rf /tmp/*");

    print_status("Clearing var temp", 0);
    system("sudo rm -rf /var/tmp/*");

    print_status("Removing crash reports", 0);
    system("sudo rm -rf /var/crash/*");

    print_status("Cleaning apt partial packages", 0);
    system("sudo rm -rf /var/cache/apt/archives/partial/*");

    printf("\nSystem cleaned successfully.\n\n");

    system("df -h");

    return 0;
}

int handle_ls(void)
{
    print_mode("ls");
    return 0;
}
