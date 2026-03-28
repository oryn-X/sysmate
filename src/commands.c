#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "help.h"
#include "system_ops.h"
#include "ui.h"

/* Dispatch the requested command after validating its arguments. */
int execute_command(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    const char *command = argv[1];

    /* System commands */
    if (strcmp(command, "update") == 0 || strcmp(command, "-u") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate update", STATUS_ERROR);
            return 1;
        }
        return handle_update();
    }
    else if (strcmp(command, "clean") == 0 || strcmp(command, "-c") == 0)
    {
        if (argc != 2)
        {
             print_status("Usage: sysmate clean", STATUS_ERROR);
            return 1;
        }
        return handle_clean();
    }

    /* File commands */
    else if (strcmp(command, "ls") == 0 || strcmp(command, "-l") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate ls", STATUS_ERROR);
            return 1;
        }
        return handle_ls(0);
    }
    else if (strcmp(command, "ls-l") == 0 || strcmp(command, "-ll") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate ls-l", STATUS_ERROR);
            return 1;
        }
        return handle_ls_long();
    }
    else if (strcmp(command, "delete") == 0 || strcmp(command, "-d") == 0)
    {
        if (argc != 3)
        {
            print_status("Usage: sysmate delete <number>", STATUS_ERROR);
            return 1;
        }

        char *endptr;
        long value = strtol(argv[2], &endptr, 10);

        if (*endptr != '\0' || value < 1)
        {
            print_status("Invalid index", STATUS_ERROR);
            return 1;
        }

        return handle_delete((int)value);
    }
    else if (strcmp(command, "info") == 0 || strcmp(command, "-i") == 0)
    {
        if (argc != 3)
        {
            print_status("Usage: sysmate info <number>", STATUS_ERROR);
            return 1;
        }

        char *endptr;
        long value = strtol(argv[2], &endptr, 10);

        if (*endptr != '\0' || value < 1)
        {
            print_status("Invalid index", STATUS_ERROR);
            return 1;
        }

        return handle_info((int)value);
    }

    /* Doctor commands */
    else if (strcmp(command, "doctor-dev") == 0 || strcmp(command, "-dd") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate doctor-dev", STATUS_ERROR);
            return 1;
        }
        return handle_doctor_dev();
    }
    else if (strcmp(command, "doctor-web") == 0 || strcmp(command, "-dw") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate doctor-web", STATUS_ERROR);
            return 1;
        }
        return handle_doctor_web();
    }

    /* Git commands */
    else if (strcmp(command, "gitsync") == 0 || strcmp(command, "-gs") == 0)
    {
        if (argc != 3)
        {
            print_status("Usage: sysmate gitsync <commit-message>", STATUS_ERROR);
            return 1;
        }
        return handle_gitsync(argv[2]);
    }

    /* Help and version */
    else if (strcmp(command, "help") == 0 || strcmp(command, "-h") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate help", STATUS_ERROR);
            return 1;
        }
        return print_help();
    }
    else if (strcmp(command, "version") == 0 || strcmp(command, "-v") == 0)
    {
        if (argc != 2)
        {
            print_status("Usage: sysmate version", STATUS_ERROR);
            return 1;
        }
        return version();
    }

    print_unknown_command(argv[1]);
    return 1;
}
 