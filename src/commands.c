#include <string.h>

#include "commands.h"
#include "help.h"
#include "system_ops.h"
#include "ui.h"

int execute_command(const char *command)
{
    if (strcmp(command, "update") == 0)
    {
        return handle_update();
    }
    else if (strcmp(command, "clean") == 0)
    {
        return handle_clean();
    }
    else if (strcmp(command, "ls") == 0)
    {
        return handle_ls();
    }
    // 
    else if (strcmp(command, "--help") == 0)
    {
        print_help();
        return 0;
    }else if (strcmp(command, "--ver") == 0)
    {
        
    }
    

    print_unknown_command(command);
    return 1;
}
