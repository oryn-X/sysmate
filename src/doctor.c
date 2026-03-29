#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

char command[MAX_LEN];
int doctor_total;
int doctor_pass;
int doctor_missing;
char doctor_missing_packages[2024];

/* Check common native development tools. */
int handle_doctor_dev(void)
{

    doctor_init();
    print_mode("doctor-dev  ");
    print_status("Checking basic system tools...", STATUS_OK);
    printf("──────────────────────────────────\n");

    /* Check the core build, version control, and scripting tools used in local dev setups. */
    run_doctor("gcc        : compiler tool", "which gcc > /dev/null 2>&1", "gcc");
    run_doctor("g++        : C++ compiler", "which g++ > /dev/null 2>&1", "g++");
    run_doctor("make       : build tool", "which make > /dev/null 2>&1", "make");
    run_doctor("git        : version control", "which git > /dev/null 2>&1", "git");
    run_doctor("python3    : scripting language", "which python3 > /dev/null 2>&1", "python3");
    run_doctor("pip3       : Python package manager", "which pip3 > /dev/null 2>&1", "python3-pip");
    return doctor_print_summary();
}

/* Check common web development tools. */
int handle_doctor_web(void)
{

    doctor_init();
    print_mode("doctor-dev  ");
    printf("\n");
    print_status("Checking development tools...", STATUS_OK);
    printf("──────────────────────────────────\n");

    /* Check the runtime, package, networking, and container tools used for web work. */
    run_doctor("node       : JavaScript runtime", "which node > /dev/null 2>&1", "nodejs");
    run_doctor("npm        : package manager", "which npm > /dev/null 2>&1", "npm");
    run_doctor("npx        : package runner", "which npx > /dev/null 2>&1", "npm");
    run_doctor("git        : version control", "which git > /dev/null 2>&1", "git");
    run_doctor("curl       : HTTP client", "which curl > /dev/null 2>&1", "curl");
    run_doctor("docker     : containers", "which docker > /dev/null 2>&1", "docker.io");
    return doctor_print_summary();
}

/* Run one doctor check and update the summary counters. */
int run_doctor(const char *msg, const char *cmd, const char *package)
{
    doctor_total++;
    int result = system(cmd);
    if (result != 0)
    {
        printf("[ " C_RED "FAIL" C_RESET " ] ");
        print_status(msg, STATUS_ERROR);
        if (doctor_missing_packages[0] == '\0')
        {
            strcpy(doctor_missing_packages, package);
        }
        else
        {
            strcat(doctor_missing_packages, " ");
            strcat(doctor_missing_packages, package);
        }

        doctor_missing++;
        return 1;
    }
    else
    {
        printf("[ " C_GREEN "PASS" C_RESET " ] ");
        print_status(msg, STATUS_PLAIN);
        doctor_pass++;
    }

    return 0;
}

/* Reset doctor counters before a new scan. */
void doctor_init(void)
{

    doctor_total = 0;
    doctor_pass = 0;
    doctor_missing = 0;
    doctor_missing_packages[0] = '\0';
}

/* Print doctor results and optionally install missing packages. */
int doctor_print_summary()
{

    printf("\n");
    printf("╭─ Final Summary ──────────────────────────╮\n");
    printf("│ Checks:   %-30d │\n", doctor_total);
    printf("│ Passed:   %-30d │\n", doctor_pass);
    printf("│ Missing:  %-30d │\n", doctor_missing);
    printf("╰──────────────────────────────────────────╯\n");
    printf(C_RED " %s\n" C_RESET, doctor_missing_packages);
    if (doctor_missing > 0)
    {
        char ny[8];

        /* Offer to install every missing package in one apt command. */
        printf("Do you want to install the missing packages? (Y/N): ");

        if (fgets(ny, sizeof(ny), stdin) == NULL)
        {
            print_status("Input error", STATUS_ERROR);
            return 1;
        }

        if (ny[0] == 'y' || ny[0] == 'Y')
        {
            strcpy(command, "sudo apt install -y ");
            strcat(command, doctor_missing_packages);

            if (run_system("Installing missing packages", command) != 0)
            {
                return 1;
            }

            printf(C_YELLOW "Installed missing packages [ %s ]\n" C_RESET, doctor_missing_packages);
            return 0;
        }
        else if (ny[0] == 'n' || ny[0] == 'N')
        {
            return 1;
        }
        else
        {
            print_status("Enter a valid choice Y or N", STATUS_ERROR);
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
