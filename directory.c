#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()
#include "sort.h"

#include "optionsStruct.h"
#include "printer.h"

#define SIZEOFSUBDIRECTORY 1024

int mySort(const struct dirent **e1, const struct dirent **e2) {
    const char *a = (*e1)->d_name;
    const char *b = (*e2)->d_name;
    return strcmp(a, b);
}

void read_directory(char *dir, Options *options) {
    // Create a buffer
    struct dirent **namelist;
    int n;

    char subDirectory[SIZEOFSUBDIRECTORY];

    n = scandir(dir, &namelist, NULL, NULL);

    selectionSort(namelist, n);
    while (n--) {
//        strcpy(subDirectory, dir);
//        strcat(subDirectory,"/");
//        strcat(subDirectory,namelist[n]->d_name);
//        print(subDirectory, options, namelist[n]->d_name);

        printf("%s \n",namelist[n]->d_name);
        free(namelist[n]);


    }
    free(namelist);
}

