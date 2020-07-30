#include <dirent.h>
#include <string.h>
#include <stdio.h>


int selectionSort(struct dirent **namelist, int size) {
    int result = 0;
    int swap = -1;
    struct dirent *temp;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (swap > 0) {
                result = strcmp(namelist[swap]->d_name, namelist[j]->d_name);
            } else {
                result = strcmp(namelist[i]->d_name, namelist[j]->d_name);
            }

            if (result < 0) {
                swap = j;
            }
        }

        if (swap > -1) {
            temp = namelist[i];
            namelist[i] = namelist[swap];
            namelist[swap] = temp;
        }
        swap = -1;
    }

    return 0;
}
