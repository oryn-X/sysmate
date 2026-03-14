#include <stdio.h>

#include "system_ops.h"
#include "ui.h"

int handle_update(void)
{
    print_mode("update");
    printf("sudo apt update && sudo apt upgrade -y\n");
    return 0;
}

int handle_clean(void)
{
    print_mode("clean");
    return 0;
}

int handle_ls(void)
{
    print_mode("ls");
    return 0;
}
