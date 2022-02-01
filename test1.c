#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# include "filesys.h"


char *fs_name;


int main(int argc, char *argv[])
{
    create_fs();
    mount_fs();
     allocate_file("nowy");
    set_filesize(0, 1000);
    print_fs();
    set_filesize(0, 3000);
    print_fs();
    set_filesize(0, 100);
    print_fs();
    sync_fs();

    return 0;
}
