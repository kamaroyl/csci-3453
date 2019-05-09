#ifndef _FIRST_COME_FIRST_SERVE_H
#define _FIRST_COME_FIRST_SERVE_H
#include "Process.h"
#include "ProcessLinkedList.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
#include "ContextSwitch.h"
void firstComeFirstServe(struct Process** currentProcess, struct LinkedList* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time);
#endif
