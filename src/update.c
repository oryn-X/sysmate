#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

/* Run the system update and upgrade workflow. */
int handle_update(void)
{
    char command[MAX_LEN];
    print_status("Starting system update...", STATUS_OK);

    strcpy(command, "sudo apt update && sudo apt full-upgrade -y");
    int result = system(command);

    if (result != 0)
    {
        print_status("System update failed.\n", STATUS_ERROR);
        return 1;
    }

    print_status("System update completed.\n", STATUS_OK);
    return 0;
}      
    