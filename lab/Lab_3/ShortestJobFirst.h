#ifndef _SHORTEST_JOB_FIRST_H
#define _SHORTEST_JOB_FIRST_H
#include "Process.h"
#include "ProcessResult.h"
#include "ProcessMinHeap.h"
#include "ProcessResultsDynamicArray.h"
#include "ProcessDynamicArray.h"
#include "ContextSwitch.h"
void shortestJobFirst(struct Process** currentProcess, struct ProcessMinHeap* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time);
#endif
