#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "system_ops.h"
#include "ui.h"

#define MAX_LEN 300

/* Store shell commands */
char command[MAX_LEN];

int doctor_total;
int doctor_pass;
int doctor_missing;
char doctor_missing_packages[2024];

/* Store system() result */
int result;

/* Update the system */
int handle_update(void)
{
    print_status("Starting system update...", 0);

    strcpy(command, "sudo apt update && sudo apt full-upgrade -y");
    result = system(command);

    if (result != 0)
    {
        print_status("System update failed.\n", 1);
        return 1;
    }

    print_status("System update completed.\n", 0);
    return 0;
}

/*Clean system files and unused data */
int handle_clean(void)
{
    print_mode("clean");

    run_system("Showing disk usage", "df -h");
    run_system("Cleaning apt cache", "sudo apt clean && sudo apt autoclean");
    run_system("Removing unused packages", "sudo apt autoremove -y");
    run_system("Clearing thumbnails", "rm -rf ~/.cache/thumbnails/*");
    run_system("Clearing pip cache", "rm -rf ~/.cache/pip");
    run_system("Showing disk usage after cleaning", "df -h");
    print_status("\nSystem cleaned successfully.\n\n", 0);
    return 0;
}

/* List files and create .sysmate_index */
int handle_ls(void)
{
    print_mode("ls");

    DIR *dir = opendir(".");
    struct dirent *entry;
    int index = 1;
    FILE *fp = fopen(".sysmate_index", "w");

    /* Check directory open error */
    if (dir == NULL)
    {
        print_status("Cannot open directory.", 1);
        return 1;
    }
    /* Check index file open error */
    else if (fp == NULL)
    {
        print_status("Cannot open file.", 1);
        closedir(dir);
        return 1;
    }

    /* Read directory entries */
    while ((entry = readdir(dir)) != NULL)
    {
        /* Skip current directory, parent directory, and index file */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".sysmate_index") == 0)
        {
            continue;
        }

        /* Print file name and save it in index file */
        printf("[%d] %s\n", index, entry->d_name);
        fprintf(fp, "%d|%s\n", index, entry->d_name);
        index++;
    }

    /* Close opened resources */
    fclose(fp);
    closedir(dir);

    return 0;
}

/* Delete file by index */
int handle_delete(int target)
{
    FILE *fp = fopen(".sysmate_index", "r");

    /* Check index file open error */
    if (fp == NULL)
    {
        print_status("Cannot open file.", 1);
        return 1;
    }

    char buffer[256];
    int file_index;
    char file_name[256];

    /* Read index file line by line */
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        /* Extract file index and file name */
        int result = sscanf(buffer, "%d|%s", &file_index, file_name);
        if (result != 2)
        {
            continue;
        }

        /* Match the requested index */
        if (file_index == target)
        {
            char ny[8];
            int attempts = 3;

            /* Ask for delete confirmation */
            while (attempts > 0)
            {
                printf("Delete " C_YELLOW "%s" C_RESET "? (y/n): ", file_name);

                if (fgets(ny, sizeof(ny), stdin) == NULL)
                {
                    print_status("Input error", 1);
                    fclose(fp);
                    return 1;
                }

                /* Delete file if user confirms */
                if (ny[0] == 'y' || ny[0] == 'Y')
                {
                    if (remove(file_name) == 0)
                    {
                        printf(C_CYAN "Deleted -> %s\n" C_RESET, file_name);
                        fclose(fp);
                        return 0;
                    }
                    else
                    {
                        print_status("Failed to delete file", 1);
                        fclose(fp);
                        return 1;
                    }
                }
                /* Cancel delete if user declines */
                else if (ny[0] == 'n' || ny[0] == 'N')
                {
                    printf(C_YELLOW "Canceled -> %s\n" C_RESET, file_name);
                    fclose(fp);
                    return 1;
                }
                /* Ask again if input is invalid */
                else
                {
                    print_status("Please enter y or n", 1);
                    attempts--;
                    printf("Attempts left: %d\n", attempts);

                    if (attempts == 0)
                    {
                        print_status("Sorry, the attempts have ended.", 1);
                        fclose(fp);
                        return 1;
                    }
                }
            }
        }
    }

    /* Handle missing index */
    print_status("Index not found", 1);
    fclose(fp);
    return 1;
}

int handle_doctor_dev(void)
{
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
            run_system("Error installation", command);
            printf(C_YELLOW "done installation [ %s ]\n" C_RESET, doctor_missing_packages);
        }
        else if (ny[0] == 'n' || ny[0] == 'N')
        {
            return 1;
        }
        else
        {
            print_status(" Enter a valid choice Y or N", 1);
        }

        return 0;
    }
    else
    {

        return 1;
    }
}
/* run in CMD */
int run_system(const char *msg, const char *cmd)
{

    print_status(msg, 2);

    int result = system(cmd);

    if (result != 0)
    {
        print_status("[FAILED]\n", 1);
        return 1;
    }

    return 0;
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