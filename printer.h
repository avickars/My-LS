#ifndef CMPT300ASSIGNMENT4_PRINTER_H
#define CMPT300ASSIGNMENT4_PRINTER_H
#include <stdbool.h>
#include "arguements.h"
typedef struct Sizes
{
    int inodeLength;
    int linksLength;
    int userLength;
    int groupLength;
    int sizeLength;
    bool extraNameSpace;
} Sizes;

bool quotesNeeded(char *name);

int print(char *dir, Options *options, char *name, Sizes *sizes);

void getSizes(char *dir,Options *options,Sizes * sizes);

#endif //CMPT300ASSIGNMENT4_PRINTER_H
