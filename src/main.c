#include "commands.h"
#include "ui.h"



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage();
        return 1;
    }

    return execute_command(argc, argv);
}
