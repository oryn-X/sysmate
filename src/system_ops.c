#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "system_ops.h"
#include "ui.h"

#define MAX_LEN 300

/* Store shell commands */
char command[MAX_LEN];

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

/* Clean system files and unused data */
int handle_clean(void)
{
    print_mode("clean");

    run_clean("Showing disk usage", "df -h");
    run_clean("Cleaning apt cache", "sudo apt clean && sudo apt autoclean");
    run_clean("Removing unused packages", "sudo apt autoremove -y");
    run_clean("Clearing thumbnails", "rm -rf ~/.cache/thumbnails/*");
    run_clean("Clearing pip cache", "rm -rf ~/.cache/pip");
    run_clean("Showing disk usage after cleaning", "df -h");
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

    print_mode("doctor-dev");

    print_status("Checking development tools...", 0);

    int total = 0;
    int ok = 0;
    int missing = 0;
    // ===== Core Build Tools =====
    run_doctor("gcc        -> C compiler",        "which gcc > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("g++        -> C++ compiler",      "which g++ > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("make       -> build system",      "which make > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("cmake      -> build generator",   "which cmake > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Version Control =====
    run_doctor("git        -> version control",   "which git > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Scripting & Tools =====
    run_doctor("python3    -> scripting",         "which python3 > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("pip        -> python packages",   "which pip > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("node       -> JS runtime",        "which node > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("npm        -> node packages",     "which npm > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Debugging & System =====
    run_doctor("gdb        -> debugger",          "which gdb > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("valgrind   -> memory checker",    "which valgrind > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("pkg-config -> library helper",    "which pkg-config > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Networking & CLI Tools =====
    run_doctor("curl       -> HTTP client",       "which curl > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("wget       -> downloader",        "which wget > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Optional Dev Tools =====
    run_doctor("docker     -> containers",        "which docker > /dev/null 2>&1", &total, &ok, &missing);
    run_doctor("code       -> VS Code",           "which code > /dev/null 2>&1", &total, &ok, &missing);

    // ===== Summary Table =====
    printf("\n");
    printf("=====================================\n");
    printf("        SysMate Doctor Summary       \n");
    printf("=====================================\n");

    printf("| %-12s | %-5d |\n", "Total Checks", total);
    printf("| %-12s | %-5d |\n", "OK", ok);
    printf("| %-12s | %-5d |\n", "Missing", missing);

    printf("=====================================\n");

    if (missing > 0)
    {
        return 1;
    }
    else
    {

        return 0;
    }
}
/* run in CMD */
int run_clean(const char *msg, const char *cmd)
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

int run_doctor(const char *msg, const char *cmd, int *t, int *o, int *m)
{
    (*t)++;
    int result = system(cmd);
    if (result != 0)
    {
        printf("[" C_RED "NO" C_RESET "] ");
        print_status(msg, 1);
        (*m)++;
        return 1;
    }
    else
    {

        printf("[" C_GREEN "OK" C_RESET "] ");
        print_status(msg, 2);
        (*o)++;
    }

    return 0;
}