#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()

#include "optionsStruct.h"
#include "printer.h"


#define SIZEOFSUBDIRECTORY 1024

void read_directory(char *dir, Options *options) {
    char subDirectory[SIZEOFSUBDIRECTORY];
    DIR *directory;
    struct dirent *de;
    if ((directory = opendir (dir)) == NULL) {
        return;
    }

    while ((de = readdir(directory)) != NULL) {
        // Removing the current directory and the parent directory from output
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }
        strcpy(subDirectory, dir);
        strcat(subDirectory,"/");
        strcat(subDirectory,de->d_name);

        // Passing to a print routine
        print(subDirectory, options);

        // If user asks to recursively print the names
        if (options->R) {
            // CITATION: https://www.programiz.com/c-programming/examples/lexicographical-order
            read_directory(subDirectory, options); // Recursively enters read_directory again
        }

        printf("************************************************************\n");
    }
    closedir(directory);
}

