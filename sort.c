#include <string.h>
#include <stdio.h>

#include "list.h"


void selectionSort(List *list) {
    int result;
    setCurrentToFront(list);
    Node *current = list->head;
    Node *temp;
    Node *swapNode = NULL;
    do {
        temp = current->next;
        while (temp != NULL) {
            if (swapNode != NULL) {
                result = strcmp((char *) swapNode->item, (char *) temp->item);
            } else {
                result = strcmp((char *) current->item, (char *) temp->item);
            }
            if (result > 0) {
                swapNode = temp;
            }

            temp = temp->next;
        }

        if (swapNode != NULL) {
            swap(current, swapNode);
        }
        swapNode = NULL;
        current = current->next;
    } while (current != NULL);
}
