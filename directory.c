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




void read_directory(char *dir, Options *options, Sizes *sizes) {
    char subDirectory[SIZEOFSUBDIRECTORY];
    struct dirent **namelist;
    int numFiles;
    List directoriesList = {0 ,NULL, NULL, NULL};
//    S_ISLNK(sb.st_mode) && options.l
    if (isDirectory(dir)) {

        struct stat sb;
        if (lstat(dir, &sb) == -1) {
            perror("lstat");
            return;
            //        exit(EXIT_FAILURE);
        }
        if (S_ISLNK(sb.st_mode) && options->l) {
            // Testing if this is a soft link directory, if yes as per ls, we won't read its contents, just print it
            print(dir, options, dir, sizes);
            return;
        }



        // Scanning the directory
        numFiles = scandir(dir, &namelist, NULL, alphasort);

        // Getting the lengths of each lstat() value for print in this directory
        Sizes dirSizes = {0,0,0,0,0 , false};
        for (int i = 0; i < numFiles; ++i) {
            strcpy(subDirectory, dir);
            strcat(subDirectory,"/");
            strcat(subDirectory,namelist[i]->d_name);
            getSizes(subDirectory, options, &dirSizes);
            memset(subDirectory, 0, SIZEOFSUBDIRECTORY);
        }
        // Iterating through the directory to print
        for (int i = 0; i < numFiles ; i++) {
            strcpy(subDirectory, dir);
            strcat(subDirectory,"/");
            strcat(subDirectory,namelist[i]->d_name);

            // If print() returns an option we don't want to print or traverse, we'll just skip it
            if (print(subDirectory, options, namelist[i]->d_name, &dirSizes) == -1) {
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

            memset(subDirectory, 0, SIZEOFSUBDIRECTORY);
        }
        if (directoriesList.size > 0) {
            Node *current = directoriesList.head;
            do {
                printf("\n%s:\n", (char *)  current->item);
                read_directory((char *) current->item, options, sizes);
                current = current->next;
            } while (current != NULL);
            listFree(&directoriesList, freeItem);
        }
        free(namelist);

    } else {
        print(dir, options, dir, sizes);
    }

 }

