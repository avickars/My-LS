#include <stdlib.h> // For malloc()
#include "list.h"

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
        list->size++;
    }
}

void *getCurrentNodeItem(List *list) {
    return list->current->item;
}

void *getCurrentNode(List *list) {
    return list->current;
}

void *nextNode(List *list) {
    list->current = list->current->next;
    return list->current;
}

void setCurrent(List *list, Node *setTo) {
    list->current = setTo;
}

void setCurrentToFront(List *list) {
    list->current = list->head;
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

void freeItem(void *item) {
    free(item);
}

void swap(Node *node1, Node *node2) {
    void *temp = node1->item;
    node1->item = node2->item;
    node2->item = temp;
}

int listSize(List *list) {
    return list->size;
}



