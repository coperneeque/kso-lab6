#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# include "filesys.h"


char *fs_name;


int main(int argc, char *argv[])
{
    create_fs();
    sync_fs();
    print_fs();

    return 0;
}
