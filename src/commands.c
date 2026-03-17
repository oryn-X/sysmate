#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "help.h"
#include "system_ops.h"
#include "ui.h"


int execute_command(int argc, char *argv[])
{
    if (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "update") == 0)
    {
        return handle_update();
    }
    else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "clean") == 0)
    {
        return handle_clean();
    }
    else if (strcmp(argv[1], "ls") == 0)
    {
        return handle_ls();
    }else if (strcmp(argv[1], "-d") == 0)
    {
        
    }
    
    
    else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        return print_help();
    }
    else if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "-v") == 0)
    {
       return version();
    }

    print_unknown_command(argv[1]);
    return 1;
}
