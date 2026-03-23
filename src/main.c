#include "commands.h"
#include "ui.h"

/* Entry point of the program */
int main(int argc, char *argv[])
{
    /* Pass user input to command handler */
    return execute_command(argc, argv);
}
 