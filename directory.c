#include <string.h> // For strcmpy()
#include <dirent.h> // For readdir()
#include <stddef.h> // For NULL
#include <stdio.h> // For printf()
#include <stdlib.h> // For free()
#include <sys/stat.h> // For stat

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

static bool skip(struct dirent *nameList) {
    // Removing the current directory form output
    if (strcmp(nameList->d_name, ".") == 0) {
        return true;
    }

    // Removing the parent directory from output
    if (strcmp(nameList->d_name, "..") == 0) {
        return true;
    }

    // Removing hidden files from output
    if (nameList->d_name[0]=='.') {
        return true;
    }

    return false;
}



void read_directory(char *dir, Options *options, Sizes *sizes) {
    char subDirectory[SIZEOFSUBDIRECTORY];
    struct dirent **namelist;
    int numFiles;
    List directoriesList = {0 ,NULL, NULL, NULL};

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
        Sizes dirSizes = {-1,-1,-1,-1,-1 , false};
        for (int i = 0; i < numFiles; ++i) {
            // Testing if the file is something we don't want to consider in our spacing (i.e. we wont print it later), if yes lets skip it
            if (skip(namelist[i])) {
                continue;
            }
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

            // Testing if the file is something we don't want to print, if yes lets skip it
            if (skip(namelist[i])) {
                // Freeing the namelist
                free(namelist[i]);
                continue;
            } else {
                print(subDirectory, options, namelist[i]->d_name, &dirSizes);
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

            // Freeing the namelist
            free(namelist[i]);

            // Resetting subDirectory
            memset(subDirectory, 0, SIZEOFSUBDIRECTORY);
        }
        if (directoriesList.size > 0) {
            Node *current = directoriesList.head;
            Sizes subDirSizes = {0,0,0,0,0 , false};
            do {
                printf("\n%s:\n", (char *)  current->item);
                read_directory((char *) current->item, options, &subDirSizes);
                current = current->next;
            } while (current != NULL);
            listFree(&directoriesList, freeItem);
        }
        free(namelist);

    } else {
        print(dir, options, dir, sizes);
    }

 }

