#include "structures.h"
#include "arguements.h"
#include "directory.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc()


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
        struct List list = {0 ,NULL, NULL};

        for (int i = firstLocationArg; i < numArgs; ++i) {
            // Testing if the argument is a directory
            if (isDirectory(args[i])) {

                // If argument is a directory, add it to the list
                if (list.size == 0) {
                    list.head = (Node *) malloc(sizeof(struct Node));
                    list.head->directoryNumber = i;
                    list.head->next = NULL;
                    list.size++;
                    list.tail = list.head;
                } else {
                    list.tail->next = (Node *) malloc(sizeof(struct Node));
                    list.tail = list.tail->next;
                    list.tail->next = NULL;
                    list.tail->directoryNumber = i;
                }
                // Then skip it (i.e. don't print it yet)
                continue;
            }
            options.path = args[i];
            read_directory(options.path, &options);
        }

        // If there are any directories, we'll print them out now
        Node *temp = list.head;
        while (temp != NULL) {
            options.path = args[temp->directoryNumber];
            read_directory(options.path, &options);
            temp = temp->next;
        }

    } else {
        // Single Path passed as an argument
        read_directory(options.path, &options);
    }

    return 0;
}
