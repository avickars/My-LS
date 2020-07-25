#include <sys/stat.h> // For stat
#include <stdio.h> // For printf()
#include <stdlib.h> // For exit()

#include "optionsStruct.h"

void print(char *dir, Options *options) {
    if (options->i || options->l) {
        struct stat sb;
        if (lstat(dir, &sb) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        if (options->i && !(options->l)) {
            printf("%7ld %s \n", (long) sb.st_ino, dir);
        } else if (!(options->i) && options->l) {
            printf("%s \n", dir);
            printf("%d \n",sb.st_mode);
            printf("%ld \n",sb.st_nlink);
            printf("%d \n",sb.st_uid);
            printf("%ld \n",sb.st_size);
//            printf("%d \n",sb.st_mtim);
        } else {
            printf("here1");
        }

    } else {
        printf("%s \n", dir);
    }


}
