#include "commands.h"
#include "ui.h"

/* Delegate CLI processing to the command dispatcher. */
int main(int argc, char *argv[])
{
    return execute_command(argc, argv);
}
