#include <stdio.h>
#include <stdlib.h>
#include "ShortestJobFirst.h"

void testNullProcessAndEmptyArrivalQueue() {
    printf("\n====================================== Test Null Process And Empty ArrivalQueue ===================================================\n");
    struct Process* currentProcess = NULL;
    struct ProcessMinHeap* arrivalQueue = createMinHeap(5);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(1);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(1);
    int time = 1;

    
    printf("\nBefore Shortest Job First:\n");

    shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter Shortest Job First:\n");
    if( currentProcess == NULL ) {
        printf("current Process is null as expected\n");
    } else {
        printf("Current Process is not null!\n");
    }
    freeProcessMinHeap(arrivalQueue);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
}

void testNullProcess() {
    printf("\n====================================== Test Null Process ===================================================\n");
    struct Process* currentProcess = NULL;
    struct Process* nextProcess = createProcess(2,1,19);
    struct ProcessMinHeap* arrivalQueue = createMinHeap(5);
    insertValue(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(1);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(1);
    int time = 1;

    
    printf("\nBefore Shortest Job First:\n");
    printf("arrivalQueue size is: %d\n", arrivalQueue->size);
    shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter Shortest Job First:\n");
    if( currentProcess->pid == 2 ) {
        printf("current Process pid is 2 as expected\n");
    } else {
        printf("Current Process is not 2!\n");
    }

    if( arrivalQueue->size != 0 ) {
        printf("Process in arrival queue when there is not supposed to be\n");
    }
    freeProcessMinHeap(arrivalQueue);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    free(currentProcess);

    printf("\n\n");
}

void testProcessBurstTimeUpEmptyQueue() {
    printf("\n====================================== Test Process Burst Time Up Empty Queue ===================================================\n");
    struct Process* currentProcess = createProcess(2, 1, 1);
    struct Process* backup = currentProcess;
    currentProcess->process_time = 1;
    struct ProcessMinHeap* arrivalQueue = createMinHeap(5);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(1);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(1);
    int time = 2;
    
    printf("\nBefore Shortest Job First:\n");
    printf("Current Process pid: %d\n", currentProcess->pid);

    shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter Shortest Job First:\n");
    if( currentProcess == NULL ) {
        printf("current Process pid is NULL as expected\n");
    } else {
        printf("Current Process is not NULL!\n");
    }

    if( results->size == 1 ) {
        printf("Result in array\n");
    }

    freeProcessMinHeap(arrivalQueue);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    free(backup);

    printf("\n\n");

}

void testProcessBurstTimeUpAndNextProcessLowerPriority() {
    printf("\n====================================== Test Process Burst Time Up And Next Process Lower Priority ===================================================\n");
    struct Process* currentProcess = createProcess(2, 1, 1);
    struct Process* backup = currentProcess;
    struct Process* nextProcess = createProcess(4, 5, 5);
    currentProcess->process_time = 1;
    struct ProcessMinHeap* arrivalQueue = createMinHeap(5);
    insertValue(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(1);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(1);
    int time = 2;
    
    printf("\nBefore Shortest Job First:\n");
    printf("Current Process pid: %d\n", currentProcess->pid);

    shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter Shortest Job First:\n");
    if( currentProcess->pid == 4 ) {
        printf("current Process pid is 4 as expected\n");
    } else {
        printf("Current Process is not NULL!\n");
    }

    if( results->size == 1 ) {
        printf("Result in array\n");
    }
    
    if( timeline->size == 1 ) {
        printf("ContextSwitch added\n");
    }

    freeProcessMinHeap(arrivalQueue);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    free(nextProcess);
    free(backup);

    printf("\n\n");

}

void testProcessBurstTimeUpAndNextProcessHigherPriority() {
    printf("\n====================================== Test Process Burst Time Up And Next Process Higher Priority ===================================================\n");
    struct Process* currentProcess = createProcess(2, 5, 5);
    struct Process* backup = currentProcess;
    struct Process* nextProcess = createProcess(4, 1, 1);
    currentProcess->process_time = 5;
    struct ProcessMinHeap* arrivalQueue = createMinHeap(5);
    insertValue(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(1);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(1);
    int time = 10;
    
    printf("\nBefore Shortest Job First:\n");
    printf("Current Process pid: %d\n", currentProcess->pid);

    shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);

    printf("\nAfter Shortest Job First:\n");
    if( currentProcess->pid == 4 ) {
        printf("current Process pid is 4 as expected\n");
    } else {
        printf("Current Process is not NULL!\n");
    }

    if( results->size == 1 ) {
        printf("Result in array\n");
    }
    
    if( timeline->size == 1 ) {
        printf("ContextSwitch added\n");
    }

    freeProcessMinHeap(arrivalQueue);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    free(nextProcess);
    free(backup);

    printf("\n\n");

}

void testHigherPriority() {

}

void default() {

}


int main() {
    testNullProcessAndEmptyArrivalQueue();
    testNullProcess();
    testProcessBurstTimeUpEmptyQueue();
    testProcessBurstTimeUpAndNextProcessLowerPriority();
    testProcessBurstTimeUpAndNextProcessHigherPriority();
    testHigherPriority();
    defaultAction();
    return 0;
}
