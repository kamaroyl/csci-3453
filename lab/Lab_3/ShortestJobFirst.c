/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#include "ShortestJobFirst.h"
#include "Process.h"
#include "ProcessMinHeap.h"
#include <stdlib.h>
#include <stdio.h>

void shortestJobFirst(struct Process** currentProcess, struct ProcessMinHeap* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time) {

    if( *currentProcess == NULL ) {

        *currentProcess = popMin(arrivalQueue);
        if( *currentProcess == NULL ) return;
        printf("currentProcess: { pid: %d, arrival_time: %d, burst_time: %d }\n", (*currentProcess)->pid, (*currentProcess)->arrival_time, (*currentProcess)->cpu_burst_time);
        addContextSwitchToDynamicArrayFromProcess(timeline, *currentProcess, time);

    } else if( (*currentProcess)->process_time == (*currentProcess)->cpu_burst_time ) {

        processToResult(*currentProcess, results, time);
        *currentProcess = popMin(arrivalQueue);
        if( *currentProcess == NULL ) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, *currentProcess, time);

    } else if( ((struct Process*) peekMin(arrivalQueue)) != NULL && (*currentProcess)->cpu_burst_time > ((struct Process*) peekMin(arrivalQueue))->cpu_burst_time ) {

        ++((*currentProcess)->context_switch_count);
        insertValue(arrivalQueue, *currentProcess);
        *currentProcess = popMin(arrivalQueue);
        if( *currentProcess == NULL ) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, *currentProcess, time);
 
    } else {
        //NOOP
    }

    ++((*currentProcess)->process_time);
}
