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

int handle_clean(void)
{
    print_mode("clean");
    strcpy(command, "sudo apt clean && sudo apt autoclean && sudo apt autoremove -y");
    result = system(command);
    if (result != 0)
    {
        printf("erorr");
        return 1;
    }
    

    print_status("Cleaning apt cache", 0);
    print_status("Running apt autoclean", 0);
    print_status("Removing unused packages", 0);
    printf("\nSystem cleaned successfully.\n\n");

    return 0;
}

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
