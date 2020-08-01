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

typedef struct Node
{
    void *item;
    struct Node *next;
} Node;

void addNode(List *list, void *item);

void *getCurrentNodeItem(List *list);

void swap(Node *node1, Node *node2);

void setCurrentToFront(List *list);

void setCurrent(List *list, Node *setTo);

void *getCurrentNode(List *list);

int listSize(List *list);

void *nextNode(List *list);

typedef void (*FREE_FN)(void* pItem);
void listFree(List* pList, FREE_FN pItemFreeFn);




#endif //CMPT300ASSIGNMENT4_LIST_H
