#include "filesys.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


superblock_t sb;
inode_t *inodes;
diskblock_t *dbs;


char *fsname(char *dst, char *src)
{
    if (strlen(src) > FS_NAME_CAP) {
        return 0;
    }

    dst = malloc(strlen(src) + 1);
    strcpy(dst, src);

    return dst;
}

void create_fs()
{
    int i;

    sb.num_inodes = 10;
    sb.num_blocks = 100;
    sb.size_blocks = sizeof (diskblock_t);

    inodes = malloc(sizeof(inode_t) * sb.num_inodes);
    for (i = 0; i < sb.num_inodes; i++)
    {
        inodes[i].size = -1;
        inodes[i].first_block = -1;
        strcpy(inodes[i].name, "emptyfi");
    }
    
    dbs = malloc(sizeof(diskblock_t) * sb.num_blocks);
    for ( i = 0; i < sb.num_blocks; i++)
    {
        dbs[i].next_block_num = -1;
    }
    
}

void mount_fs()
{
    int i;
    FILE *file;
    file = fopen("fs_data", "r");

    fread(&sb, sizeof(superblock_t), 1, file);

    fread(inodes, sizeof(inode_t), sb.num_inodes, file);
    fread(dbs, sizeof(diskblock_t), sb.num_blocks, file);
    
    fclose(file);
}

void sync_fs()
{
    int i;
    FILE *file;
    file = fopen("fs_data", "w+");

    fwrite(&sb, sizeof(superblock_t), 1, file);

    fwrite(inodes, sizeof(inode_t), sb.num_inodes, file);
    fwrite(dbs, sizeof(diskblock_t), sb.num_blocks, file);

    fclose(file);
}

void print_fs()
{
    int i;

    printf("Superblock:\tnum inodes: %d\tnum blocks: %d\tsize blocks: %d\n", sb.num_inodes, sb.num_blocks, sb.size_blocks);
    printf("inodes:\n");
    for ( i = 0; i < sb.num_inodes; i++)
    {
        printf("size: %d\tblock: %d\tname: %s\n", inodes[i].size, inodes[i].first_block, inodes[i].name);
    }
    for ( i = 0; i < sb.num_blocks; i++)
    {
        printf("block num: %d, next block: %d\n", i, dbs[i].next_block_num);
    }    

}
