#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()
#include <sys/stat.h> // For stat

#include "structures.h"
#include "printer.h"
#include "list.h"

#define SIZEOFSUBDIRECTORY 1024

int isDirectory(char *file) {
    struct stat sb;
    stat(file, &sb);
    return S_ISDIR(sb.st_mode);
}

static void freeItem(void *item) {
    free(item);
};




void read_directory(char *dir, Options *options) {
    char subDirectory[SIZEOFSUBDIRECTORY];
    struct dirent **namelist;
    int numFiles;
    List directoriesList = {0 ,NULL, NULL, NULL};
    if (isDirectory(dir)) {
        // Scanning the directory
        numFiles = scandir(dir, &namelist, NULL, alphasort);

        // Iterating through the directory
        for (int i = 0; i < numFiles ; i++) {
            strcpy(subDirectory, dir);
            strcat(subDirectory,"/");
            strcat(subDirectory,namelist[i]->d_name);

            // If print() returns an option we don't want to print or traverse, we'll just skip it
            if (print(subDirectory, options, namelist[i]->d_name) == -1) {
                free(namelist[i]);
                continue;
            }

            // If we are doing a recursive traversal
            if (options->R) {
                // Testing if the path is a directory, as per ls we display it after, adding nodes to a list to keep track of what needs to be displayed
                if (isDirectory(subDirectory)) {
                    char *dirPath = (char *) malloc(sizeof(subDirectory));
                    strcpy(dirPath, subDirectory);
                    addNode(&directoriesList, dirPath);
                }
            }
            free(namelist[i]);


        }
        if (directoriesList.size > 0) {
            Node *current = directoriesList.head;
            do {
                printf("\n%s:\n", (char *)  current->item);
                read_directory((char *) current->item, options);
                current = current->next;
            } while (current != NULL);
            listFree(&directoriesList, freeItem);
        }
        free(namelist);
        memset(subDirectory, 0, SIZEOFSUBDIRECTORY);
    } else {
        print(dir, options, dir);
    }

 }

