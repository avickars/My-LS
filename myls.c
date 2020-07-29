#include "optionsStruct.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL


int main(int numArgs, char *args[]) {
    // Declaring a struct to record to handle the arguements
    struct Options options = {false, false, false, NULL};

    // Handling the arguements
    arguements_handler(&options, numArgs, args);

    // Reading the directory
    if (options.path == NULL) {
        // If no path argument was passed
        read_directory(".", &options);
    } else {
        // If a path argument was passed
        read_directory(options.path, &options);
    }


    return 0;
}
