/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#ifndef _PROCESS_LINKED_LIST_H
#define _PROCESS_LINKED_LIST_H
#include "Process.h"

struct LinkedListNode {
    struct Process *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
};

struct LinkedList {
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
    unsigned char size;  
};

struct LinkedList* initLinkedList();

struct LinkedListNode* initLinkedListNode(struct Process* data);

void addLinkedListNode(struct LinkedList* currentLinkedList, struct Process* processToAdd);

struct Process* popLinkedListNode(struct LinkedList* currentLinkedList);
void freeProcessLinkedList(struct LinkedList* linkedList);
#endif
