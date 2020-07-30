#include <stdlib.h> // For malloc()

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
    struct Node *current;
} List;

void addNode(List *list, int num) {
    if (list->size == 0) {
        list->head = (Node *) malloc(sizeof(struct Node));
        list->head->directoryNumber = num;
        list->head->next = NULL;
        list->size++;
        list->tail = list->head;
        list->current = list->head;
    } else {
        list->tail->next = (Node *) malloc(sizeof(struct Node));
        list->tail = list->tail->next;
        list->tail->next = NULL;
        list->tail->directoryNumber = num;
    }
}

int getCurrentNodeNum(List *list) {
    return list->current->directoryNumber;
}

int nextNode(List *list) {
    if (list->current->next == NULL) {
        return -1;
    } else {
        list->current = list->current->next;
        return 0;
    }
}



