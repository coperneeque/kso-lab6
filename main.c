#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    extern char *optarg;
    extern int optopt;
    extern int optind;

	int opt;
	
/*	put ':' in the starting of the
	string so that program can
	distinguish between '?' and ':'

	while((opt = getopt(argc, argv, ":if:lrx")) != -1)
*/
	while((opt = getopt(argc, argv, ":f:cp:g:se:d")) != -1)
	{
		switch(opt)
		{
			case 'f':
				printf("filesystem filename: %s\n", optarg);
                /* record file name */
				break;
			case 'c':
				printf("option: %c : create filesystem\n", opt);
                /* create */
				break;
			case 'p':
				printf("option: %c : put file %s into filesystem\n", opt, optarg);
                /* put */
				break;
			case 'g':
				printf("option: %c : get file %s from filesystem\n", opt, optarg);
                /* get */
				break;
			case 's':
				printf("option: %c : show filesystem contents\n", opt);
                /* display */
				break;
			case 'e':
				printf("option: %c : erase file %s from filesystem\n", opt, optarg);
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
	
	return 0;
}
