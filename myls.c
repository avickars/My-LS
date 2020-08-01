#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()
#include <string.h>
#include "list.h"
#include "sort.h"
#include <stdio.h>

#include "printer.h"

static void freeItem(void *item) {
    free(item);
};


int main(int numArgs, char *args[]) {
    // Declaring a struct to record to handle the arguements
    struct Options options = {false, false, false, NULL};

    Sizes sizes = {0, 0,0,0,0};

    // Handling the arguements
    int firstLocationArg = arguements_handler(&options, numArgs, args);

    // Reading the directory
    if (options.path == NULL) {
        // If no path argument was passed
        read_directory(".", &options);
    } else if ((numArgs - firstLocationArg) > 1){
        // If multiple path arguements were passed

        // Creating a list to hold regular arguements, so that they can be sorted
        List argsList = {0 , NULL, NULL, NULL};

        // Creating a list to hold arguements that are paths
        List directoryList = {0 , NULL, NULL, NULL};
        for (int i = firstLocationArg; i < numArgs; ++i) {
            char *arg = (char *) malloc(strlen(args[i]) + 1);
            strcpy(arg, args[i]);
            if (isDirectory(args[i])) {
//                getSizes(arg, &options, &sizes);

                // Extracting any directories to be printed after
                addNode(&directoryList, arg);
            } else {
                addNode(&argsList, arg);
            }
        }
        if (argsList.size > 1) {
            // Sorting the arguements that are files
            selectionSort(&argsList);
            Node *current = argsList.head;
            do {
                read_directory(current->item, &options);
                current = current->next;
            } while (current != NULL);
            listFree(&argsList, freeItem);
        }

        if (directoryList.size > 0) {
            // Sorting the arguements that are directories
//            selectionSort(&directoryList);
            Node *current = directoryList.head;
            do {
                printf("\n%s:\n", (char *) current->item);
                read_directory(current->item, &options);
                current = current->next;
            } while (current != NULL);
            listFree(&directoryList, freeItem);
        }
    } else {
        read_directory(args[firstLocationArg], &options);
    }

    return 0;
}
