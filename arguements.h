#ifndef CMPT300ASSIGNMENT4_ARGUEMENTS_H
#define CMPT300ASSIGNMENT4_ARGUEMENTS_H

#include <stdbool.h>

typedef struct Options
{
    bool i;
    bool l;
    bool R;
    char *path;
} Options;

int arguements_handler(Options *options, int numArgs,char *args[]);



#endif //CMPT300ASSIGNMENT4_ARGUEMENTS_H
