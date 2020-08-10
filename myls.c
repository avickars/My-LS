#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()
#include <string.h>
#include <stdio.h>
#include <sys/stat.h> // For stat
#include "printer.h"
#include "arguements.h"
#include "directory.h"
#include "list.h"
#include "sort.h"

static void freeItem(void *item) {
    free(item);
};

int main(int numArgs, char *args[]) {
    // Declaring a struct to record to handle the arguements
    struct Options options = {false, false, false, NULL};

    // Handling the arguements
    int firstLocationArg = arguements_handler(&options, numArgs, args);

    // Defining a dummy struct to hold the max lengths of the lstat values.  I don't actually need it, but I need to pass it
    Sizes dummySizes = {-1, -1,-1,-1,-1, false};

    // Reading the directory
    if (options.path == NULL) {
        // Printing the current path if we want recursion.  (Doing this to mimick ls)
        if (options.R) {
            printf(".:\n");
        }
        // If no path argument was passed
        read_directory(".", &options, &dummySizes);
    } else if ((numArgs - firstLocationArg) > 1){
        // If multiple path arguements were passed

        // Defining a struct to hold the max lengths of the lstat values
        Sizes argsSizes = {0, 0,0,0,0};

        // Creating a list to hold regular arguements, so that they can be sorted
        List argsList = {0 , NULL, NULL, NULL};

        // Creating a list to hold arguements that are paths
        List directoryList = {0 , NULL, NULL, NULL};
        for (int i = firstLocationArg; i < numArgs; ++i) {
            char *arg = (char *) malloc(strlen(args[i]) + 1);
            strcpy(arg, args[i]);
            struct stat sb;
            if (isDirectory(arg)) {
                if (lstat(arg, &sb) == -1) {
                    perror("lstat");
                }

                // Testing if a directory is a soft link, if yes and l is an arguement, we print it with the files.
                // Otherwise we print it with the directories.  Doing this to mimic ls
                if (S_ISLNK(sb.st_mode) && options.l) {
                    getSizes(arg, &options, &argsSizes);
                    addNode(&argsList, arg);
                } else {
                    // Extracting any directories to be printed after
                    addNode(&directoryList, arg);
                }
            } else {
                // Testing if the file exists so it won't get put on the list
                if (lstat(arg, &sb) == -1) {
                    perror("lstat");
                    free(arg);
                    continue;
                }
                getSizes(arg, &options, &argsSizes);
                addNode(&argsList, arg);
            }
        }

        if (argsList.size > 0) {
            // Sorting the arguements that are files
            selectionSort(&argsList);
            Node *current = argsList.head;
            do {
                read_directory(current->item, &options, &argsSizes);
                current = current->next;
            } while (current != NULL);
            listFree(&argsList, freeItem);
            printf("\n");
        }

        // If there are any directories, we'll send them to be read now
        if (directoryList.size > 0) {
            // Sorting the arguements that are directories
            selectionSort(&directoryList);

            Node *current = directoryList.head;
            do {
                // Testing if quotes need to wrap the directory name
                if (quotesNeeded(current->item)) {
                    printf("\'%s\':\n", (char *) current->item);
                } else {
                    printf("%s:\n", (char *) current->item);
                }

                read_directory(current->item, &options, &dummySizes);
                printf("\n");
                current = current->next;
            } while (current != NULL);
            listFree(&directoryList, freeItem);
        }
    } else {
        read_directory(args[firstLocationArg], &options, &dummySizes);
    }

    return 0;
}
