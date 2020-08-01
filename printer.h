#ifndef CMPT300ASSIGNMENT4_PRINTER_H
#define CMPT300ASSIGNMENT4_PRINTER_H

typedef struct Sizes
{
    int userLength;
    int groupLength;
    int sizeLength;
    int linksLength;
    int inodeLength;
} Sizes;

int print(char *dir, Options *options, char *name);

void getSizes(char *dir,Options *options,Sizes * sizes);



#endif //CMPT300ASSIGNMENT4_PRINTER_H
