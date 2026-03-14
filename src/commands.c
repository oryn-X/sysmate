#include <string.h>

#include "commands.h"
#include "system_ops.h"
#include "ui.h"

int execute_command(const char *command)
{
    if (strcmp(command, "update") == 0)
    {
        return handle_update();
    }

    if (strcmp(command, "clean") == 0)
    {
        return handle_clean();
    }

    if (strcmp(command, "ls") == 0)
    {
        return handle_ls();
    }

    print_unknown_command(command);
    return 1;
}
