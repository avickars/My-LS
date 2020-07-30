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

        int directories[numArgs];
        int numDirectories = 0;

        // Simple singly linked list to grab any arguements that are directories, this way tey are printed last as per ls
        struct List list = {0 ,NULL, NULL, NULL};

        for (int i = firstLocationArg; i < numArgs; ++i) {
            // Testing if the argument is a directory
            if (isDirectory(args[i])) {
                // If argument is a directory, add it to the list
                addNode(&list, i);
                // Then skip it (i.e. don't print it yet)
                continue;
            }

            // Reading paths that are not directories
            options.path = args[i];
            read_directory(options.path, &options);
        }

        // If there are any directories, reading them how
        if (list.size > 0) {
            do {
                printf("\n%s:\n", args[getCurrentNodeNum(&list)]);
                options.path = args[getCurrentNodeNum(&list)];
                read_directory(options.path, &options);
            } while (nextNode(&list) == 0);
        }




    } else {
        // Single Path passed as an argument
        read_directory(options.path, &options);
    }

    return 0;
}
