#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

// this is for update command
int handle_update(void)
{

    char command[300];
    print_mode("update");
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

int handle_clean(void)
{
    print_mode("clean");
    return 0;
}

int handle_ls(void)
{
    print_mode("ls");
    return 0;
}
