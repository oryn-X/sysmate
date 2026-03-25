#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

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
                    }
                    else
                    {

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

int handle_info(int target)
{

    FILE *fp = fopen(".sysmate_index", "r");

    /* Check index file open error */
    if (fp == NULL)
    {
        print_status("Cannot open file.", 1);
        return 1;
    }

    char buffer[256];
    int line_count = 0;
    int file_index;
    char file_name[256];
    char current_dir[256];
    char full_path[512];
    struct stat st;
    char Permissions_owner[1024];
    char Permissions_group[1024];
    char Permissions_other[1024];
    char last_modified[256];
    struct tm *time_info;
    struct passwd *owner_info;
    struct group *group_info;

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

            print_mode("info");

            if (getcwd(current_dir, sizeof(current_dir)) == NULL)
            {
                print_status("Cannot get current directory", 1);
                fclose(fp);
                return 1;
            }

            snprintf(full_path, sizeof(full_path), "%s/%s", current_dir, file_name);

            if (stat(full_path, &st) != 0)
            {
                print_status("Cannot get file information", 1);
                fclose(fp);
                return 1;
            }

            printf(C_YELLOW "[•]" C_RESET " Name            : " C_BLUE "%s\n" C_RESET, file_name);
            printf(C_YELLOW "[•]" C_RESET " " C_WHITE "Path" C_RESET "            : " C_CYAN "%s\n" C_RESET, full_path);

            if (S_ISDIR(st.st_mode))
            {
                printf(C_YELLOW "[•]" C_RESET " " C_WHITE "Type" C_RESET "            : " C_SKY "Directory\n" C_RESET);
            }
            else if (S_ISREG(st.st_mode))
            {
                printf(C_YELLOW "[•]" C_RESET " " C_WHITE "Type" C_RESET "            : " C_MINT "File\n" C_RESET);
            }
            else
            {
                printf(C_YELLOW "[•]" C_RESET " " C_WHITE "Type" C_RESET "            : " C_ORANGE "Other\n" C_RESET);
            }

            printf(C_YELLOW "[•]" C_RESET " " C_WHITE "Size" C_RESET "            : " C_ORANGE "%ld bytes\n" C_RESET, st.st_size);

            owner_info = getpwuid(st.st_uid);
            group_info = getgrgid(st.st_gid);

            if (owner_info != NULL)
            {
                printf(C_YELLOW "[•]" C_RESET " Owner           : " C_INDIGO "%s\n" C_RESET, owner_info->pw_name);
            }
            else
            {
                printf(C_YELLOW "[•]" C_RESET " Owner           : " C_RED "Unknown\n" C_RESET);
            }
            if (group_info != NULL)
            {
                printf(C_YELLOW "[•]" C_RESET " Group           : " C_INDIGO "%s\n" C_RESET, group_info->gr_name);
            }
            else
            {
                printf(C_YELLOW "[•]" C_RESET " Group           : " C_RED "Unknown\n" C_RESET);
            }

            build_permissions(st.st_mode, Permissions_owner, S_IRUSR, S_IWUSR, S_IXUSR);
            build_permissions(st.st_mode, Permissions_group, S_IRGRP, S_IWGRP, S_IXGRP);
            build_permissions(st.st_mode, Permissions_other, S_IROTH, S_IWOTH, S_IXOTH);
            printf(C_YELLOW "[•]" C_RESET " Owner Perms     : %s\n", Permissions_owner);
            printf(C_YELLOW "[•]" C_RESET " Group Perms     : %s\n", Permissions_group);
            printf(C_YELLOW "[•]" C_RESET " Other Perms     : %s\n", Permissions_other);

            time_info = localtime(&st.st_mtime);
            if (time_info == NULL)
            {
                print_status("Cannot format modification time", 1);
                fclose(fp);
                return 1;
            }

            if (strftime(last_modified, sizeof(last_modified), "%Y-%m-%d %H:%M", time_info) == 0)
            {
                print_status("Cannot build modification time", 1);
                fclose(fp);
                return 1;
            }

            FILE *file_linse = fopen(full_path, "r");
            if (file_linse == NULL)
            {
                print_status("Cannot open file.", 1);
                return 1;
            }

            while (fgets(buffer, sizeof(buffer), file_linse) != NULL)
            {
                line_count++;
            }

            if (line_count != 0)
            {
                printf(C_YELLOW "[•]" C_RESET " Line Count      : " C_SKY "%d\n" C_RESET, line_count);
            }
            else
            {

                printf(C_YELLOW "[•]" C_RESET " Line Count      : " C_SKY "N/A\n" C_RESET);
            }

            printf(C_YELLOW "[•]" C_RESET " Last Modified   : " C_ROSE "%s\n" C_RESET, last_modified);

            fclose(file_linse);
            fclose(fp);
            return 0;
        }
    }

    /* Handle missing index */
    print_status("Index not found", 1);
    fclose(fp);
    return 1;
}

void build_permissions(int mode, char *permissions_text, int read_flag, int write_flag, int exec_flag)
{

    permissions_text[0] = '\0';

    if (mode & read_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_MINT "Read" C_RESET);
        }
        else
        {
            strcat(permissions_text, ", ");
            strcat(permissions_text, C_MINT "Read" C_RESET);
        }
    }

    if (mode & write_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_GOLD "Write" C_RESET);
        }
        else
        {
            strcat(permissions_text, ", ");
            strcat(permissions_text, C_GOLD "Write" C_RESET);
        }
    }

    if (mode & exec_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_SKY "Execute" C_RESET);
        }
        else
        {
            strcat(permissions_text, ", ");
            strcat(permissions_text, C_SKY "Execute" C_RESET);
        }
    }

    if (permissions_text[0] == '\0')
    {
        strcpy(permissions_text, C_GRAY "None" C_RESET);
    }
}