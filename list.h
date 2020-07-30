//
// Created by aidan on 2020-07-29.
//

#ifndef CMPT300ASSIGNMENT4_LIST_H
#define CMPT300ASSIGNMENT4_LIST_H

typedef struct List
{
    int size;
    struct Node *head;
    struct Node *tail;
    struct Node *current;
} List;

void addNode(List *list, int num);

int getCurrentNodeNum(List *list);

int nextNode(List *list);


#endif //CMPT300ASSIGNMENT4_LIST_H
