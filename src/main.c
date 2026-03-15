#include "commands.h"
#include "ui.h"

// test
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage();
        return 1;
    }

    return execute_command(argv[1]);
}
