#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "ProcessLinkedList.h"

int main() {
    struct LinkedList* ll = initLinkedList();
    struct Process* p = createProcess(1,1,1);
    addLinkedListNode(ll, p);
    printf("LinkedList: { size: %d }\n", ll->size);
    p = createProcess(2,2,2);
    addLinkedListNode(ll, p);
    printf("LinkedList: { size: %d }\n", ll->size);
    p = popLinkedListNode(ll);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d, process_time: %d }\n", p->pid, p->arrival_time, p->cpu_burst_time, p->process_time);
    free(p);
    printf("LinkedList: { size: %d }\n", ll->size);

    p = popLinkedListNode(ll);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d, process_time: %d }\n", p->pid, p->arrival_time, p->cpu_burst_time, p->process_time);
    printf("LinkedList: { size: %d }\n", ll->size);
    free(p);
    free(ll);
    return 0;
}
