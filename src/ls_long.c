#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "ui.h"
#include "system_ops.h"
 
int handle_ls_long(void)
{

    handle_ls(1);
    print_mode("ls-l");
    DIR *dir = opendir(".");
    int index = 1;
    char current_dir[256];
    char full_path[512];
    char type[64];
    char Permissions_o[256];
    char Permissions_g[256];
    char Permissions_t[256];
    const char *type_color;
    const char *name_color;

    struct dirent *dire;
    struct stat st;

    if (dir == NULL)
    {
        print_status("Cannot open directory.", STATUS_ERROR);
        return 1;
    }

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        print_status("Cannot get current directory", STATUS_ERROR);
        closedir(dir);
        return 1;
    }

    printf("NUM   TYP   OWN   GRO   OTH   FILE NAME\n");

    while ((dire = readdir(dir)) != NULL)
    {
        if (strcmp(dire->d_name, ".") == 0 ||
            strcmp(dire->d_name, "..") == 0 ||
            strcmp(dire->d_name, ".sysmate_index") == 0)
        {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", current_dir, dire->d_name);

        if (stat(full_path, &st) != 0)
        {
            print_status("Cannot get file information", STATUS_ERROR);
            closedir(dir);
            return 1;
        }

        if (S_ISDIR(st.st_mode))
        {
            strcpy(type, "DIR");
            type_color = C_WHITE;
            name_color = C_WHITE;
        }
        else if (S_ISREG(st.st_mode))
        {
            strcpy(type, "FIL");
            type_color = C_BLUE;
            name_color = C_BLUE;
        }
        else
        {
            strcpy(type, "OTH");
            type_color = C_ORANGE;
            name_color = C_ORANGE;
        }

        build_perm_ls_long(st.st_mode, Permissions_o, S_IRUSR, S_IWUSR, S_IXUSR);
        build_perm_ls_long(st.st_mode, Permissions_g, S_IRGRP, S_IWGRP, S_IXGRP);
        build_perm_ls_long(st.st_mode, Permissions_t, S_IROTH, S_IWOTH, S_IXOTH);

        printf(C_YELLOW "[%02d]" C_RESET "  "
                        "%s%-3s" C_RESET "   " C_WHITE "%-3s" C_RESET "   " C_WHITE "%-3s" C_RESET "   " C_WHITE "%-3s" C_RESET "   "
                        "%s%s" C_RESET "\n",
               index,
               type_color, type,
               Permissions_o,
               Permissions_g,
               Permissions_t,
               name_color, dire->d_name);

        index++;
    }
    printf(C_DARK_GREEN "Note:" C_WHITE " To view detailed file information, use: sysmate info <number> " C_BPURPLE "\n" C_RESET);

    closedir(dir);
    return 0;
}

void build_perm_ls_long(int mode, char *permissions_text, int read_flag, int write_flag, int exec_flag)
{
    /* Append granted permissions and add separators only after the first entry. */
    permissions_text[0] = '\0';

    if (mode & read_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_MINT "r" C_RESET);
        }
        else
        {
            strcat(permissions_text, C_MINT "r" C_RESET);
        }
    }
    else
    {
        strcat(permissions_text, "-");
    }
    if (mode & write_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_GOLD "w" C_RESET);
        }
        else
        {
            strcat(permissions_text, C_GOLD "w" C_RESET);
        }
    }
    else
    {
        strcat(permissions_text, "-");
    }
    if (mode & exec_flag)
    {
        if (permissions_text[0] == '\0')
        {
            strcpy(permissions_text, C_SKY "x" C_RESET);
        }
        else
        {
            strcat(permissions_text, C_SKY "x" C_RESET);
        }
    }
    else
    {
        strcat(permissions_text, "-");
    }
    if (permissions_text[0] == '\0')
    {
        strcpy(permissions_text, C_GRAY "---" C_RESET);
    }
}
