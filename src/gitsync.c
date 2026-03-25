#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

/* Stage, commit, rebase, and push the current repository. */
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

        /* Stage all pending changes before creating the commit. */
        if (run_system("Staging files" C_RESET, "git add .") != 0)
        {
            return 1;
        }

        /* Build the commit command from the user-supplied message. */
        strcpy(command, "git commit -m \"");
        strcat(command, message);
        strcat(command, "\"");

        if (run_system("Creating commit" C_RESET, command) != 0)
        {
            return 1;
        }
        /* Rebase on the latest remote changes, then push the updated branch. */
        if (run_system("Pulling latest changes" C_RESET, "git pull --rebase") != 0)
        {
            return 1;
        }
        if (run_system("Pushing changes" C_RESET, "git push") != 0)
        {
            return 1;
        }

        print_status("Git sync completed successfully", 0);
        return 0;
    }

}
