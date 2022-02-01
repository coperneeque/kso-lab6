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
        strcpy(inodes[i].name, "no_name");
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

void destroy_fs()
{
    if (dbs)    free(dbs);
    if (inodes) free(inodes);
}

int allocate_file(char name[8])
{
    int in = find_inode();
    int blk = find_block();

    inodes[in].first_block = blk;
    dbs[blk].next_block_num = -2;

    strcpy(inodes[in].name, name);
}

int find_inode()
{
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        if (inodes[i].first_block == -1)
        {
            return i;
        }
        
    }
    return -1;
}

int find_block()
{
    int i;
    for (i = 0; i < sb.num_blocks; i++)
    {
        if (dbs[i].next_block_num == -1)
        {
            return i;
        }
        
    }
    return -1;
}

void set_filesize(int fnum, int size)
{
    int num;
    int bn;
    int next_num;
    int empty;

    num = size / BLOCK_SIZE;
    if (size % BLOCK_SIZE > 0)
    {
        ++num;
    }
    
    bn = inodes[fnum].first_block;
    --num;

    /* increase file if needed */
    while (num > 0)
    {
        /* next block number */
        next_num = dbs[bn].next_block_num;
        if (next_num == -2)
        {
            empty = find_block();
            dbs[bn].next_block_num = empty;
            dbs[empty].next_block_num = -2;
        }
        bn = dbs[bn].next_block_num;
        --num;
    }
    shorten_file(bn);
    dbs[bn].next_block_num = -2;
}

void shorten_file(int blk_num)
{
    int n = dbs[blk_num].next_block_num;
    if (n >= 0)
    {
        shorten_file(n);
    }
    dbs[blk_num].next_block_num = -1;
}

int get_block(int fnum, int offset)
{
    int shift;
    int blk_num;

    while (shift > 0)
    {
// FIXME:
        blk_num = dbs[blk_num].next_block_num;
        --shift;
    }
    

    return blk_num;
}

void write_byte(int fnum, int pos, char *data)
{
    int rel_blk;
    int offset;
    int blk_num;

    /* which block */
    rel_blk = pos / BLOCK_SIZE;
    blk_num = get_block(fnum, rel_blk);
    offset = pos % BLOCK_SIZE;

    dbs[blk_num].data[offset] = (*data);
}
