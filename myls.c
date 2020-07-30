#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()
#include "list.h"


#include <stdio.h>
#include "structures.h"
#include "directory.h"

void freeItem(void *item) {
    free(item);
}



int main(int numArgs, char *args[]) {
    // Declaring a struct to record to handle the arguements
    struct Options options = {false, false, false, NULL};

    // Handling the arguements
    int firstLocationArg = arguements_handler(&options, numArgs, args);


    // Reading the directory
    if (options.path == NULL) {
        // If no path argument was passed
        read_directory(".", &options);
    } else if (firstLocationArg > -1) {
        // Multiple paths passed as an argument

        // Simple singly linked list to grab any arguements that are directories, this way they are printed last as per ls
        List list = {0 ,NULL, NULL, NULL};

        for (int i = firstLocationArg; i < numArgs; ++i) {
            // Testing if the argument is a directory
            if (isDirectory(args[i])) {
                // If argument is a directory, add it to the list
                int *argNum = (int *) malloc(sizeof(int));
                *argNum = i;
                addNode(&list, argNum);
                // Then skip it (i.e. don't print it yet)
                continue;
            }

            // Reading paths that are not directories
            options.path = args[i];
            read_directory(options.path, &options);
        }

//      If there are any directories, reading them here
        if (list.size > 0) {
            do {
                printf("\n%s:\n", args[*(int*) getCurrentNodeItem(&list)]);
                options.path = args[*(int*) getCurrentNodeItem(&list)];
                read_directory(options.path, &options);
            } while (nextNode(&list) == 0);

            listFree(&list,freeItem);
        }

    } else {
        // Single Path passed as an argument
        read_directory(options.path, &options);
    }

    return 0;
}
