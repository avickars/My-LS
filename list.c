#include <stdlib.h> // For malloc()
#include "list.h"

typedef struct Node
{
    void *item;
    struct Node *next;
} Node;

void addNode(List *list, void *item) {
    if (list->size == 0) {
        list->head = (Node *) malloc(sizeof(struct Node));
        list->head->item = item;
        list->head->next = NULL;
        list->size++;
        list->tail = list->head;
        list->current = list->head;
    } else {
        list->tail->next = (Node *) malloc(sizeof(struct Node));
        list->tail = list->tail->next;
        list->tail->next = NULL;
        list->tail->item = item;
    }
}

void *getCurrentNodeItem(List *list) {
    return list->current->item;
}

int nextNode(List *list) {
    if (list->current->next == NULL) {
        return -1;
    } else {
        list->current = list->current->next;
        return 0;
    }
}

void setCurrent(List *list, Node *setTo) {
    list->current = setTo;
}

void listFree(List *list, FREE_FN freeItemFunction) {
    Node *temp = list->head;
    list->current = list->head;
    while (temp != NULL) {
        temp = list->current->next;
        freeItemFunction(list->current->item);
        free(list->current);
        list->current = temp;
    }
}



