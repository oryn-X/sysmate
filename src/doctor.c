#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system_ops.h"
#include "ui.h"

int doctor_total;
int doctor_pass;
int doctor_missing;
char doctor_missing_packages[2024];


int handle_doctor_dev(void)
{
    char command[MAX_LEN];
    doctor_total = 0;
    doctor_pass = 0;
    doctor_missing = 0;
    doctor_missing_packages[0] = '\0';

    print_mode("doctor-dev  ");
    printf("\n");
    print_status("Checking development tools...", 0);
    printf("──────────────────────────────────\n");

    // ===== Core Build Tools =====
    run_doctor("gcc        -> C compiler", "which gcc > /dev/null 2>&1", "gcc");
    run_doctor("g++        -> C++ compiler", "which g++ > /dev/null 2>&1", "g++");
    run_doctor("make       -> build system", "which make > /dev/null 2>&1", "make");
    // ===== Version Control =====
    run_doctor("git        -> version control", "which git > /dev/null 2>&1", "git");
    // ===== Scripting & Tools =====
    run_doctor("python3    -> scripting", "which python3 > /dev/null 2>&1", "python3");
    run_doctor("pip3       -> python packages", "which pip3 > /dev/null 2>&1", "python3-pip");
    // ===== Summary Table =====
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

        printf("Do you want to install the missing packages? (Y/N): ");

        if (fgets(ny, sizeof(ny), stdin) == NULL)
        {
            print_status("Input error", 1);
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

            printf(C_YELLOW "Done installation [ %s ]\n" C_RESET, doctor_missing_packages);
            return 0;
        }
        else if (ny[0] == 'n' || ny[0] == 'N')
        {
            return 1;
        }
        else
        {
            print_status("Enter a valid choice Y or N", 1);
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int run_doctor(const char *msg, const char *cmd, const char *package)
{
    doctor_total++;
    int result = system(cmd);
    if (result != 0)
    {
        printf("[ " C_RED "FAIL" C_RESET " ] ");
        print_status(msg, 1);
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
        print_status(msg, 2);
        doctor_pass++;
    }

    return 0;
}
