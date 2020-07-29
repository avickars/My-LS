#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL

#include <stdio.h>
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
        for (int i = firstLocationArg; i < numArgs; ++i) {
            options.path = args[i];
            read_directory(options.path, &options);

        }
    } else {
        // Single Path passed as an argument
        read_directory(options.path, &options);
    }

    return 0;
}
