#ifndef FILESYS_H
#define FILESYS_H


#define BLOCK_SIZE 512
#define FS_NAME_CAP 100


typedef struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
} superblock_t;

typedef struct inode
{
    int size;
    char name[8];
    int first_block;
    int nextblock_num;
} inode_t;

typedef struct disk_block
{
    int next_block_num;
    char data[BLOCK_SIZE];
} diskblock_t;

/*
 * Copy filesystem file name from command line argument to buffer.
 * malloc() the space required for dst - needs freeing later.
 * Returns poiter to dst.
 */
char *fsname(char *dst, char *src);

/*
 * Initialize new filesystem
 */
void create_fs();

/*
 * Load a filesystem
 */
void mount_fs();

/*
 * Write the filesystem
 */
void sync_fs();

void print_fs();

void destroy_fs();

int allocate_file(char name[8]);
void set_filesize(int fnum, int size);
void write_byte(int fnum, int pos, char *data);

#endif
