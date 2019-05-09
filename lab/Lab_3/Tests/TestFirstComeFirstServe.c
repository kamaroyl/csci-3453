#include <stdio.h>
#include <stdlib.h>
#include "FirstComeFirstServe.h"


void testFirstArrive() {
    printf("=========================================================================================================================================\n");
    printf("\ntestFirstArrive()\n");
    struct Process* currentProcess = createProcess(1,1,1);
    struct LinkedList* arrivalQueue = initLinkedList();
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 1;

    printf("\nBefore First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    


    firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);
    


    printf("\nAfter First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    

   printf("\n\n"); 
}

void testProcessDone() {
    printf("=========================================================================================================================================\n");
    printf("\ntestProcessDone()\n");
    struct Process* currentProcess = createProcess(1,1,1);
    currentProcess->process_time = 1;
    struct Process* nextProcess = createProcess(2,2,2);
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 1;

    printf("\nBefore First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    


    firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);
    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);    

    printf("\nAfter First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    
    if(contextSwitch != NULL ) {
        printf("ContextSwitch: { pid: %d, time: %d }\n", contextSwitch->pid, contextSwitch->time);
    } else {
        printf("Context Switch was NULL\n");
    }
    
    if( result != NULL ) {
        printf("Result: { pid: %d, arrival: %d, cpu_burst: %d, finish: %d, waiting_time: %d, turn_around_time: %d, context_switch_count: %d}\n", result->pid, result->arrival, result->cpu_burst, result->finish, result->waiting_time, result->turn_around_time, result->context_switch_count);
    } else {
        printf("Result is NULL!\n");
    }

    printf("\n\n");

}

void testProcessDoneAndArrivalQueueEmpty() {
    printf("=========================================================================================================================================\n");
    printf("\ntestProcessDoneAndArrivalQueueEmpty()\n");
    struct Process* currentProcess = createProcess(1,1,1);
    currentProcess->process_time = 1;
    struct LinkedList* arrivalQueue = initLinkedList();
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 1;

    printf("\nBefore First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    


    firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter First Come First Serve\n");
    if( currentProcess == NULL ) {
        printf("Current Process is NULL as expected\n");
    } else {
        printf("Current Process is NOT NULL. ERROR!\n");
    }
    printf("\n\n");

}

void testCurrentProcessNull() {
    printf("=========================================================================================================================================\n");
    printf("\ntestCurrentProcessNull()\n");
    struct Process* currentProcess = NULL;
    struct Process* nextProcess = createProcess(2,2,2);
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 1;

    printf("\nBefore First Come First Serve\n");
    printf("Current Process is NULL\n");

    firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter First Come First Serve\n");
    printf("CurrentProcess: {pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);    

    printf("\n\n");

}

void testCurrentProcessNullAndNextNull() {
    printf("=========================================================================================================================================\n");
    printf("\ntestCurrentProcessNullAndNextNull()\n");
    struct Process* currentProcess = NULL;
    struct LinkedList* arrivalQueue = initLinkedList();
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 1;

    printf("\nBefore First Come First Serve\n");
    printf("Current Process is NULL\n");

    firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter First Come First Serve\n");
    if(currentProcess == NULL) {
        printf("current process is NULL as expected\n");
    }

    printf("\n\n");

}


int main() {
    testFirstArrive();
    testProcessDone();
    testProcessDoneAndArrivalQueueEmpty();
    testCurrentProcessNull();
    testCurrentProcessNullAndNextNull();
    return 0;
}
