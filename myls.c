#include "optionsStruct.h"
#include "arguements.h"
#include "directory.h"


int main(int numArgs, char *args[]) {
    // Declaring a struct to record to handle the arguements
    struct Options options = {false, false, false};

    // Handling the arguements
    arguements_handler(&options, numArgs, args);

    read_directory(".", &options);

    return 0;
}
