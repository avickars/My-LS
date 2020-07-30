#include <dirent.h>
#include <string.h>
#include <stdio.h>


int selectionSort(struct dirent **namelist, int size) {
    int result = 0;
    int swap = -1;
    struct dirent *temp;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            // Testing if there is a higher element
            if (swap > 0) {
                result = strcmp(namelist[swap]->d_name, namelist[j]->d_name);
            } else {
                result = strcmp(namelist[i]->d_name, namelist[j]->d_name);
            }
            // If there is a higher element, make it the new highest one
            if (result < 0) {
                swap = j;
            }
        }

        // Swapping to elements
        if (swap > -1) {
            temp = namelist[i];
            namelist[i] = namelist[swap];
            namelist[swap] = temp;
        }
        // Resetting the swap value
        swap = -1;
    }

    return 0;
}
