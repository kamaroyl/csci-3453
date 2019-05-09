/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#ifndef _ROUND_ROBIN_H
#define _ROUND_ROBIN_H
#include "Process.h"
#include "ProcessLinkedList.h"
#include "ProcessDynamicArray.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
#include "ContextSwitch.h"
void roundRobin(struct Process** currentProcess, struct LinkedList* arrivalQueue, struct ProcessResultsDynamicArray* results, struct ContextSwitchDynamicArray* timeline, int time, int quanta);
#endif
