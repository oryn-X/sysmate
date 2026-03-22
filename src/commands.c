#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "help.h"
#include "system_ops.h"
#include "ui.h"

int execute_command(int argc, char *argv[])
{

    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    /* Get the command entered by the user */
    const char *command = argv[1];

    /* Execute system update */
    if (strcmp(command, "update") == 0 || strcmp(command, "-u") == 0)
    {
        /* Ensure no extra arguments */
        if (argc != 2)
        {
            print_usage();
            return 1;
        }

        return handle_update();
    }

    /* Clean unused packages */
    else if (strcmp(command, "clean") == 0 || strcmp(command, "-c") == 0)
    {
        if (argc != 2)
        {
            print_usage();
            return 1;
        }

        return handle_clean();
    }

    /* List files and build index */
    else if (strcmp(command, "ls") == 0)
    {
        if (argc != 2)
        {
            print_usage();
            return 1;
        }

        return handle_ls();
    }

    /* Delete file by index */
    else if (strcmp(command, "delete") == 0 || strcmp(command, "-d") == 0)
    {
        /* Ensure index argument is provided */
        if (argc != 3)
        {
            print_status("Usage: sysmate delete <number>", 1);
            return 1;
        }

        /* Convert argument to integer */
        char *endptr;
        long value = strtol(argv[2], &endptr, 10);

        if (*endptr != '\0' || value < 1)
        {
            print_status("Invalid index", 1);
            return 1;
        }

        int target = (int)value;
        return handle_delete(target);
    }
    else if (strcmp(command, "doctor-dev") == 0 || strcmp(command, "-dd") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: Sysmate doctor <option>", 1);
            return 1;
        }
        return handle_doctor_dev();
    }

    /* Show help menu */
    else if (strcmp(command, "help") == 0 || strcmp(command, "-h") == 0)
    {
        if (argc != 2)
        {
            print_unknown_command(argv[1]);
            return 1;
        }
        return print_help();
    }

    /* Show version */
    else if (strcmp(command, "version") == 0 || strcmp(command, "-v") == 0)
    {
        if (argc != 2)
        {
            print_unknown_command(argv[1]);
            return 1;
        }
        return version();
    }

    /* Handle unknown command */
    print_unknown_command(argv[1]);
    return 1;
}
