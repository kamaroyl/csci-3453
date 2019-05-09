#include <stdio.h>
#include <stdlib.h>
#include "ContextSwitch.h"
#include "Process.h"
#include "ProcessLinkedList.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
#include "RoundRobin.h"

/*
 *    Current process done processing and arrival queue is not empty
 */
void testProcessEqualBurstTimeArrivalQueueNotEmpty() {
    
    printf("=====================================================================================================================\n");
    printf("testProcessEqualBurstTimeArrivalQueueNotEmpty()\n\n");
   
    struct Process* currentProcess = createProcess(1,1,1);
    currentProcess->process_time = 1;
    struct Process* backup = currentProcess;
    struct Process* nextProcess = createProcess(2,2,2);
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 3;
    int quanta = 4;

    printf("\nBefore Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);

    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);

    printf("\nAfter Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);

    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);

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
    printf("backup: pid = %d\n", backup->pid);

    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    free(currentProcess);
    free(backup);
    printf("\n\n");
}


/*
 *    Current Process processing done and the arrivalQueue is empty
 */
void testProcessEqualBurstTimeArrivalQueueEmpty() {

    printf("=====================================================================================================================\n");
    printf("testProcessEqualBurstTimeArrivalQueueEmpty()\n\n");
    
    int time = 5;
    int quanta = 4;

    struct Process* currentProcess = createProcess(1,1,1);
    currentProcess->process_time = 1;
    
    struct LinkedList* arrivalQueue = initLinkedList();

    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);

    printf("\nBefore Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);

    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);


    printf("\nAfter Round Robin:\n");

    if( currentProcess == NULL ) {
        printf("currentProcess is NULL as expected\n");
    } else {
        printf("current Process is not NULL!\n");
        printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    }

    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);

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

/*
 *    current process is not done processing, but has processed a time equal to allowed time. Arrival queue is not empty
 */
void testProcessTimeModQuantaEqualZeroArrivalQueueNotEmpty() {
    printf("=====================================================================================================================\n");

    printf("testProcessTimeModQuantaEqualZeroArrivalQueueNotEmpty()\n");

    int quanta = 2;
    int time = 8;
    struct Process* currentProcess = createProcess(1, 10, 10);
    currentProcess->process_time = 4;
    struct Process* nextProcess = createProcess(2, 2, 2); 
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);

    printf("\nBefore Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    
    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);
    
    printf("\nAfter Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);

    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);

    if(contextSwitch != NULL ) {
        printf("ContextSwitch: { pid: %d, time: %d }\n", contextSwitch->pid, contextSwitch->time);
    } else {
        printf("Context Switch was NULL\n");
    }
    
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);

    if(result == NULL) {
        printf("No result in array as expected (process still processing)\n"); 
    } else {
        printf("result is not null:\n");
        printf("Result: { pid: %d, arrival: %d, cpu_burst: %d, finish: %d, waiting_time: %d, turn_around_time: %d, context_switch_count: %d}\n", result->pid, result->arrival, result->cpu_burst, result->finish, result->waiting_time, result->turn_around_time, result->context_switch_count);

    }
    
    printf("\n\n");


}

/*
 *    Processing time for current process is divisible by quanta and arrival queue is empty
 */
void testProcessTimeModQuantaEqualZeroArrivalQueueEmpty() {

    printf("=====================================================================================================================\n");
    printf("testProcessTimeModQuantaEqualZeroArrivalQueueEmpty()\n");
   
    int quanta = 2;
    int time = 8;
    struct Process* currentProcess = createProcess(1, 10, 10);
    currentProcess->process_time = 4;
    struct LinkedList* arrivalQueue = initLinkedList();
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
 
    printf("\nBefore Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    
    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);
    
    printf("\nAfter Round Robin:\n");
    
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);
    
    if( result == NULL ) {
        printf("Result was NULL as expected\n");
    } else {
        printf("Result was not Null!\n");
    }

    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);

    if( contextSwitch != NULL ) {
         printf("ContextSwitch was NULL as expected\n");
         printf("ContextSwitch: { pid: %d, time: %d }\n", contextSwitch->pid, contextSwitch->time);
       
    } else {
        printf("Context swith was null!\n");
    }

    printf("\n\n");
}


void testDefault() {
    printf("=====================================================================================================================\n");
    printf("testDefault()\n");
    
    int quanta = 10;
    int time = 4;
    struct Process* currentProcess = createProcess(1,9,8);
    currentProcess->process_time = 1;
    struct Process* nextProcess = createProcess(2,2,2);
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);

    printf("\nBefore Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    
    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);
    
    printf("\nAfter Round Robin:\n");
    
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);
    struct ProcessResult* result = getProcessResultFromDynamicArray(results, 0);
    
    if( result == NULL ) {
        printf("Result was NULL as expected\n");
    } else {
        printf("Result was not Null!\n");
        printf("Result: { pid: %d, arrival: %d, cpu_burst: %d, finish: %d, waiting_time: %d, turn_around_time: %d, context_switch_count: %d}\n", result->pid, result->arrival, result->cpu_burst, result->finish, result->waiting_time, result->turn_around_time, result->context_switch_count);

    }

    struct ContextSwitch* contextSwitch = getContextSwitchAtIndex(timeline, 0);

    if( contextSwitch == NULL ) {
         printf("ContextSwitch was NULL as expected\n");
       
    } else {
        printf("Context swith was null!\n");
        printf("ContextSwitch: { pid: %d, time: %d }\n", contextSwitch->pid, contextSwitch->time);

    }
  
    
    printf("\n\n");
}

void testCurrentProcessNull() {
    printf("=====================================================================================================================\n");
    printf("testCurrentProcessNull()\n");

    struct Process* currentProcess = NULL;
    struct Process* nextProcess = createProcess(2,2,2);
    struct LinkedList* arrivalQueue = initLinkedList();
    addLinkedListNode(arrivalQueue, nextProcess);
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 3;
    int quanta = 4;

    printf("\nBefore Round Robin:\n");
    printf("current process NULL\n");

    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);

    printf("\nAfter Round Robin:\n");
    printf("CurrentProcess: { pid: %d, arrivalTime: %d, burstTime: %d, processTime: %d, contextSwitchCount: %d }\n", currentProcess->pid, currentProcess->arrival_time, currentProcess->cpu_burst_time, currentProcess->process_time, currentProcess->context_switch_count);

    printf("\n\n");
}

void testCurrentProcessNullNextProcessNull() {
    printf("=====================================================================================================================\n");
    printf("testCurrentProcessNullNextProcessNull()\n");

    struct Process* currentProcess = NULL;
    struct LinkedList* arrivalQueue = initLinkedList();
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(5);
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(5);
    int time = 3;
    int quanta = 4;

    printf("\nBefore Round Robin:\n");
    printf("current process NULL\n");

    roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);

    printf("\nAfter Round Robin:\n");
    if( currentProcess == NULL) {
        printf("Current Process is NULL as expected\n");
    }
    printf("\n\n");

}


int main() {
    testProcessEqualBurstTimeArrivalQueueNotEmpty();
    testProcessEqualBurstTimeArrivalQueueEmpty();
    testProcessTimeModQuantaEqualZeroArrivalQueueNotEmpty();
    testProcessTimeModQuantaEqualZeroArrivalQueueEmpty();
    testDefault();
    testCurrentProcessNull();
    testCurrentProcessNullNextProcessNull();
    return 0;
}
