#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()
#include <sys/stat.h> // For stat
#include "sort.h"

#include "structures.h"
#include "printer.h"

#define SIZEOFSUBDIRECTORY 1024

int isDirectory(char *file) {
    struct stat sb;
    stat(file, &sb);
    return S_ISDIR(sb.st_mode);
}

void read_directory(char *dir, Options *options) {
    // Create a buffer
    struct dirent **namelist;
    int numFiles;
    int result = 0;

    char subDirectory[SIZEOFSUBDIRECTORY];

    if (isDirectory(dir)) {
        print(dir, options, dir);
        numFiles = scandir(dir, &namelist, NULL, NULL);
        selectionSort(namelist, numFiles);

        while (numFiles--) {
            strcpy(subDirectory, dir);
            strcat(subDirectory,"/");
            strcat(subDirectory,namelist[numFiles]->d_name);

            if ((result = print(subDirectory, options, namelist[numFiles]->d_name)) == -1) {
                free(namelist[numFiles]);
                continue;
            }

            if (options->R) {
                if (isDirectory(namelist[numFiles]->d_name)) {
                    read_directory(namelist[numFiles]->d_name, options);
                }

            }
            free(namelist[numFiles]);


        }
        free(namelist);
    } else {
        print(dir, options, dir);
    }



 }

