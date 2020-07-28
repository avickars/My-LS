#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()

#include "optionsStruct.h"
#include "printer.h"


#define SIZEOFSUBDIRECTORY 1024

void read_directory(char *dir, Options *options) {
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, NULL);
    while (n--) {
//        printf("%s\n", namelist[n]->d_name);
        print(namelist[n], options);
        free(namelist[n]);
    }
    free(namelist);
//



//    char subDirectory[SIZEOFSUBDIRECTORY];
//    DIR *directory;
//    struct dirent *de;
//    if ((directory = opendir (dir)) == NULL) {
//        return;
//    }
//
//    while ((de = readdir(directory)) != NULL) {
//        // Removing the current directory form output
//        if (strcmp(de->d_name, ".") == 0) {
//            continue;
//        }
//
//        // Removing the parent directory from output
//        if (strcmp(de->d_name, "..") == 0) {
//            continue;
//        }
//
//        // Removing hidden files from output
//        if (de->d_name[0]=='.') {
//            continue;
//        }
//        strcpy(subDirectory, dir);
//        strcat(subDirectory,"/");
//        strcat(subDirectory,de->d_name);
//
//        // Passing to a print routine
//        print(subDirectory, options);
//
//        // If user asks to recursively print the names
//        if (options->R) {
//            // CITATION: https://www.programiz.com/c-programming/examples/lexicographical-order
//            read_directory(subDirectory, options); // Recursively enters read_directory again
//        }
//    }
//    closedir(directory);
}

