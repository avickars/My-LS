#include <string.h> // For strlen()
#include "optionsStruct.h"

#include <stdio.h>

void arguements_handler(Options *options, int numArgs,char *args[]) {
    // Iterating through arguements
    for (int i = 1; i < numArgs; ++i) {
        // If an argument starts '-', iterate through it
        if (args[i][0] == '-') {
            for (int j = 1; j < strlen(args[i]); ++j) {
                if (args[i][j] == 'i') {
                    options->i = true;
                }

                if (args[i][j] == 'l') {
                    options->l = true;
                }

                if (args[i][j] == 'R') {
                    options->R = true;
                }
            }
        } else {
            options->path = args[i];
        }


    }
    printf("Arg: %s \n", options->path);
}

