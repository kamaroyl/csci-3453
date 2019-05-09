/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#include "ProcessLinkedList.h"


#include <stdio.h>
#include <stdlib.h>

struct LinkedList* initLinkedList() {
    struct LinkedList* ll = (struct LinkedList*) malloc( sizeof(struct LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

struct LinkedListNode* initLinkedListNode(struct Process* data) {
    struct LinkedListNode* node = (struct LinkedListNode*) malloc(sizeof(struct LinkedListNode));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void addLinkedListNode(struct LinkedList* currentLinkedList, struct Process* processToAdd) {
    struct LinkedListNode* nodeToAdd = initLinkedListNode(processToAdd);

    if(currentLinkedList->head == NULL) {

        currentLinkedList->head = nodeToAdd;
        currentLinkedList->tail = nodeToAdd;

    } else {

        struct LinkedListNode* oldTail = currentLinkedList->tail;
        
        oldTail->next = nodeToAdd;

        nodeToAdd->prev = oldTail;
        currentLinkedList->tail = nodeToAdd;

    }
    ++(currentLinkedList->size);
}

struct Process* popLinkedListNode(struct LinkedList* currentLinkedList) {
    if(currentLinkedList->head == NULL) {
        return NULL;
    }

    struct LinkedListNode* oldHead = currentLinkedList->head;
    currentLinkedList->head = oldHead->next;
    if( currentLinkedList->head == NULL ) {
        currentLinkedList->tail = NULL;
    } else {
        currentLinkedList->head->prev = NULL;
    }

    oldHead->next = NULL;
    --(currentLinkedList->size);
    struct Process* poppedProcess = oldHead->data;
    oldHead->data = NULL;
    free(oldHead);
    return poppedProcess;
}

void freeProcessLinkedList(struct LinkedList* linkedList) {
    while( linkedList->size > 0 ) {
        struct Process* process = popLinkedListNode(linkedList);
        printf("Pid: %d still in list\n", process->pid);
    }
    free(linkedList);
}
