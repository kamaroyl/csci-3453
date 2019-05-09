#include <stdlib.h>
#include <stdio.h>
#include "Process.h"
#include "ProcessDynamicArray.h"
#include "ProcessLinkedList.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
#include "ContextSwitch.h"

void roundRobin(struct Process** currentProcess, struct LinkedList* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time, int quanta) {
    if( *currentProcess == NULL ) {

        *currentProcess = popLinkedListNode(arrivalQueue);
        if( *currentProcess == NULL) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, (*currentProcess), time);

    } else if( (*currentProcess)->process_time == (*currentProcess)->cpu_burst_time ) {

        processToResult((*currentProcess), results, time);
        (*currentProcess) = popLinkedListNode(arrivalQueue);
        if(*currentProcess == NULL) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, (*currentProcess), time);

    } else if( (*currentProcess)->process_time % quanta == 0 ) {

        ++((*currentProcess)->context_switch_count);
        addLinkedListNode(arrivalQueue, (*currentProcess));
        (*currentProcess) = popLinkedListNode(arrivalQueue);
        if( (*currentProcess) == NULL ) return;
        addContextSwitchToDynamicArrayFromProcess(timeline, (*currentProcess), time);

    } else {
        //NO OP
    }

    ++((*currentProcess)->process_time);

}
