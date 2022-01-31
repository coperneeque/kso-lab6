#include "filesys.h"

#include <stdlib.h>
#include <string.h>


char *fsname(char *dst, char *src)
{
    if (strlen(src) > FS_NAME_CAP) {
        return 0;
    }

    dst = malloc(strlen(src) + 1);
    strcpy(dst, src);

    return dst;
}
