#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# include "filesys.h"


char *fs_name;


int main(int argc, char *argv[])
{
    extern char *optarg;
    extern int optopt;
    extern int optind;

	int opt;
	
/*	put ':' in the starting of the
	string so that program can
	distinguish between '?' and ':'
*/
	while((opt = getopt(argc, argv, ":f:c:p:g:se:d")) != -1)
	{
		switch(opt)
		{
			case 'f':
                /* record file name */
				printf("filesystem filename: %s\n", optarg);
				fs_name = fsname(fs_name, optarg);
				printf("registered filesystem name: %s\n", fs_name);
				break;
			case 'c':
                /* create */
				printf("option: %c : create filesystem, size: %d\n", opt, atoi(optarg));
				create_fs();
				sync_fs();
				mount_fs();
				printf("done\n");
				break;
			case 'p':
				printf("option: %c : put file \'%s\' into filesystem\n", opt, optarg);
                /* put */
				break;
			case 'g':
				printf("option: %c : get file \'%s\' from filesystem\n", opt, optarg);
                /* get */
				break;
			case 's':
                /* show */
				printf("option: %c : show filesystem contents\n", opt);
				print_fs();
				break;
			case 'e':
				printf("option: %c : erase file \'%s\' from filesystem\n", opt, optarg);
                /* erase */
				break;
			case 'd':
				printf("option: %c : destroy filesystem\n", opt);
                /* destroy */
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		}
	}
	
/*	optind is for the extra arguments
	which are not parsed
*/
	for(; optind < argc; optind++){	
		printf("extra arguments: %s\n", argv[optind]);
	}
	
    if (fs_name) {
        free(fs_name);
    }
    
	return 0;
}
