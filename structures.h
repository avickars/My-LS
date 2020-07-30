#ifndef CMPT300ASSIGNMENT4_STRUCTURES_H
#define CMPT300ASSIGNMENT4_STRUCTURES_H

#include <stdbool.h> // For bool

typedef struct Options
{
    bool i;
    bool l;
    bool R;
    char *path;
} Options;

typedef struct Node
{
    int directoryNumber;
    struct Node *next;
} Node;

typedef struct List
{
    int size;
    struct Node *head;
    struct Node *tail;
} List;




#endif //CMPT300ASSIGNMENT4_STRUCTURES_H
