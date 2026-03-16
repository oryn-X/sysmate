#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "help.h"
#include "system_ops.h"
#include "ui.h"


int execute_command(const char *command)
{
    if (strcmp(command, "-u") == 0 || strcmp(command, "update") == 0)
    {
        return handle_update();
    }
    else if (strcmp(command, "-c") == 0 || strcmp(command, "clean") == 0)
    {
        return handle_clean();
    }
    else if (strcmp(command, "ls") == 0)
    {
        return handle_ls();
    }
    
    else if (strcmp(command, "help") == 0 || strcmp(command, "-h") == 0)
    {
        return print_help();
    }
    else if (strcmp(command, "version") == 0 || strcmp(command, "-v") == 0)
    {
       return version();
    }

    print_unknown_command(command);
    return 1;
}
