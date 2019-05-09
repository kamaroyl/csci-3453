#include <stdio.h>
#include <stdlib.h>
#include "ContextSwitch.h"
#include "Process.h"
#include "ProcessDynamicArray.h"
#include "ProcessLinkedList.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
/*
 *  First come first server Q implementation for CPU
 */

void firstComeFirstServe(struct Process** currentProcess, struct LinkedList* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time) {
    if( (*currentProcess) == NULL ) {

        *currentProcess = popLinkedListNode(arrivalQueue);
        if(*currentProcess == NULL) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, *currentProcess, time);

    } else if( (*currentProcess)->process_time == (*currentProcess)->cpu_burst_time ) {

        processToResult(*currentProcess, results, time);
        *currentProcess = popLinkedListNode(arrivalQueue);
        if(*currentProcess == NULL) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, *currentProcess, time);

    } else {
        //NO OP
    }

    ++((*currentProcess)->process_time);
}
