#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

int handle_gitsync(const char *message)
{
char command[MAX_LEN];

    print_mode("gitsync");

    if (message == NULL)
    {
        print_status("Missing commit message", 1);
        return 1;
    }
    else if (message[0] == '\0')
    {
        print_status("Empty commit message", 1);
        return 1;
    }
    else
    {
        printf("Commit message: %s\n", message);

        if (run_system("Staging files" C_RESET, "git add .") != 0)
        {
            return 1;
        }

        strcpy(command, "git commit -m \"");
        strcat(command, message);
        strcat(command, "\"");

        if (run_system("Creating commit"C_RESET, command) != 0)
        {
            return 1;
        }
        if (run_system("Pulling latest changes"C_RESET, "git pull --rebase") != 0)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}