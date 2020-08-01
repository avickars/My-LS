#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()
#include "list.h"
#include "sort.h"

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
    } else {
        List argsList = {0 , NULL, NULL, NULL};
        List directoryList = {0 , NULL, NULL, NULL};
        for (int i = firstLocationArg; i < numArgs; ++i) {
            char *arg = (char *) malloc(sizeof(args[i]));
            arg = args[i];
            if (isDirectory(args[i])) {
                addNode(&directoryList, arg);
            } else {
                addNode(&argsList, arg);
            }
        }
        if (argsList.size > 1) {
            selectionSort(&argsList);
            Node *current = argsList.head;
            do {
                read_directory(current->item, &options);
                current = current->next;
            } while (current != NULL);
        }

        if (directoryList.size > 0) {
            selectionSort(&directoryList);
            Node *current = directoryList.head;
            do {
                printf("\n%s:\n", (char *) current->item);
                read_directory(current->item, &options);
                current = current->next;
            } while (current != NULL);
        }
    }

    return 0;
}
