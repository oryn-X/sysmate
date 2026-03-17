#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dirent.h>

#include "system_ops.h"
#include "ui.h"
#define MAX_LEN 300
char command[MAX_LEN];
int result;

// this is for update command START
int handle_update(void)
{

    print_status("Starting system update...", 0);
    strcpy(command, "sudo apt update && sudo apt full-upgrade -y");
    result = system(command);
    if (result != 0)
    {
        print_status("System update failed.\n", 1);
        return 1;
    }

    print_status("System update completed.\n", 0);
    return 0;
}

// this is for update command END

// this is for clean command START

int handle_clean(void)
{
    print_mode("clean");

    // before cleaning
    strcpy(command, "df -h");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] Unable to show disk usage\n", 1);
    }

    // step 1
    print_status("Cleaning apt cache", 0);
    strcpy(command, "sudo apt clean && sudo apt autoclean");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] apt cache cleaning failed\n", 1);
    }

    // step 2
    print_status("Removing unused packages", 0);
    strcpy(command, "sudo apt autoremove -y");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] Removing unused packages failed\n", 1);
    }

    // step 3
    print_status("Clearing thumbnails", 0);
    strcpy(command, "rm -rf ~/.cache/thumbnails/*");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] Clearing thumbnails failed\n", 1);
    }

    // step 4
    print_status("Clearing pip cache", 0);
    strcpy(command, "rm -rf ~/.cache/pip");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] Clearing pip cache failed\n", 1);
    }

    // after cleaning
    strcpy(command, "df -h");
    result = system(command);
    if (result != 0)
    {
        print_status("[FAILED] Unable to show disk usage\n", 1);
    }

    print_status("\nSystem cleaned successfully.\n\n", 0);

    return 0;
}
// this is for clean command END

int handle_ls(void)
{
    print_mode("ls");

    /*    DIR *dir = opendir(".");
    struct dirent *entry;
    int index = 1;
    if (dir == NULL)
    {
        print_status("Cannot open directory.", 1);
        return 1;
    } */

    return 0;
}
