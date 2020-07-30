#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()
#include <sys/stat.h> // For stat
#include "sort.h"

#include "structures.h"
#include "printer.h"
#include "list.h"

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
    List directoriesList = {0 ,NULL, NULL, NULL};


    char subDirectory[SIZEOFSUBDIRECTORY];

    if (isDirectory(dir)) {
//        print(dir, options, dir);


        // Scanning the directory
        numFiles = scandir(dir, &namelist, NULL, NULL);

        // Sorting the elements in the directory
        selectionSort(namelist, numFiles);

        while (numFiles--) {
            strcpy(subDirectory, dir);
            strcat(subDirectory,"/");
            strcat(subDirectory,namelist[numFiles]->d_name);

            if (print(subDirectory, options, namelist[numFiles]->d_name) == -1) {
                free(namelist[numFiles]);
                continue;
            }

            if (options->R) {
                // Testing if the path is a directory, as per ls, we display it after, adding nodes to a list to keep track of what needs to be displayed
                if (isDirectory(subDirectory)) {
                    char *dirPath = (char *) malloc(sizeof(subDirectory));
                    strcpy(dirPath, subDirectory);
                    addNode(&directoriesList, dirPath);
                }

            }
            free(namelist[numFiles]);
        }
        if (directoriesList.size > 0) {
            do {
                printf("\n%s:\n", (char *) getCurrentNodeItem(&directoriesList));
                read_directory((char *) getCurrentNodeItem(&directoriesList), options);
            } while (nextNode(&directoriesList) == 0);
            listFree(&directoriesList, freeItem);
        }



        free(namelist);
    } else {
        print(dir, options, dir);
    }



 }

