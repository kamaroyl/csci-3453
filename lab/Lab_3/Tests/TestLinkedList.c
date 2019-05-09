#include "Process.h"
#include "ProcessLinkedList.h"

#include <stdio.h>

int main() {
    struct Process* p1 = createProcess(2, 0, 10);
    struct Process* p2 = createProcess(3, 5, 4);
    struct LinkedList* myLinkedList = initLinkedList();
    struct LinkedListNode* p1Node = initLinkedListNode(p1);
    struct LinkedListNode* p2Node = initLinkedListNode(p2);
    addLinkedListNode(myLinkedList, p1Node);
    addLinkedListNode(myLinkedList, p2Node);
    printf("headPid: %d, head arrival Time: %d, head burst time: %d\n",myLinkedList->head->data->pid, myLinkedList->head->data->arrival_time, myLinkedList->head->data->cpu_burst_time);
    struct Process* next = myLinkedList->head->next->data;
    printf("nextPid: %d, next arrival Time: %d, next burst time: %d\n", next->pid, next->arrival_time, next->cpu_burst_time);
    
    return 0;
}
