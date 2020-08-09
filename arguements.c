#include <string.h> // For strlen()
#include <stdio.h>
#include "arguements.h"

int arguements_handler(Options *options, int numArgs,char *args[]) {
    bool pastOptions = false;
    int firstLocationArg = -1;

    // Iterating through arguements
    for (int i = 1; i < numArgs; ++i) {
        // If an argument starts '-', iterate through it
        if (args[i][0] == '-' && !pastOptions) {
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
            pastOptions = true;
            if (numArgs - i > 1) {
                options->path = args[i];
                firstLocationArg = i;
                return i;
            }
            firstLocationArg = i;
            options->path = args[i];
        }
    }
    return firstLocationArg;
}

