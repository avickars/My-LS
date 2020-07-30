#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()
#include "list.h"


#include <stdio.h>
#include "structures.h"
#include "directory.h"

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

        // Simple singly linked directoriesList to grab any arguements that are directoriesList, this way they are printed last as per ls
        List directoriesList = {0 , NULL, NULL, NULL};

        for (int i = firstLocationArg; i < numArgs; ++i) {
            // Testing if the argument is a directory
            if (isDirectory(args[i])) {
                // If argument is a directory, add it to the directoriesList
                int *argNum = (int *) malloc(sizeof(int));
                *argNum = i;
                addNode(&directoriesList, argNum);
                // Then skip it (i.e. don't print it yet)
                continue;
            }

            // Reading paths that are not directoriesList
            options.path = args[i];
            read_directory(options.path, &options);
        }

//      If there are any directoriesList, reading them here
        if (directoriesList.size > 0) {
            do {
                printf("\n%s:\n", args[*(int*) getCurrentNodeItem(&directoriesList)]);
                options.path = args[*(int*) getCurrentNodeItem(&directoriesList)];
                read_directory(options.path, &options);
            } while (nextNode(&directoriesList) == 0);

            listFree(&directoriesList, freeItem);
        }

    } else {
        // Single Path passed as an argument
        read_directory(options.path, &options);
    }

    return 0;
}
