#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "system_ops.h"
#include "ui.h"

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
        printf(" %2d | %s\n", index, entry->d_name);
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

        char *separator = strchr(buffer, '|');
        if (separator == NULL)
        {
            continue;
        }

        if (sscanf(buffer, "%d", &file_index) != 1)
        {
            continue;
        }

        strcpy(file_name, separator + 1);

        int len = strlen(file_name);
        if (len > 0 && file_name[len - 1] == '\n')
        {
            file_name[len - 1] = '\0';
        }

        /* Match the requested index */
        if (file_index == target)
        {
            char ny[8];
            int attempts = 3;

            /* Ask for delete confirmation */
            while (attempts > 0)
            {

                if (strlen(file_name) > 20)
                {
                    printf("Are you sure Delete " C_YELLOW " %.20s..." C_RESET "? (y/n): ", file_name);
                }
                else
                {
                    printf("Are you sure Delete " C_YELLOW " %s" C_RESET "? (y/n): ", file_name);
                }

                if (fgets(ny, sizeof(ny), stdin) == NULL)
                {
                    print_status("Input error", 1);
                    fclose(fp);
                    handle_ls();
                    return 1;
                }

                /* Delete file if user confirms */
                if (ny[0] == 'y' || ny[0] == 'Y')
                {
                    if (remove(file_name) == 0)
                    {

                        if (strlen(file_name) > 20)
                        {
                            printf(C_CYAN "Deleted -> %.20s...\n" C_RESET, file_name);
                        }
                        else
                        {
                            printf(C_CYAN "Deleted -> %s\n" C_RESET, file_name);
                        }

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

                    if (strlen(file_name) > 20)
                    {
                       printf(C_YELLOW "Canceled -> %.20s...\n" C_RESET, file_name);
                    }else{

                        printf(C_YELLOW "Canceled -> %s\n" C_RESET, file_name);
                    }
                    
                    
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