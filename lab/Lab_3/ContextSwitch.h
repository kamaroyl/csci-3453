#ifndef _CONTEXT_SWITCH_H
#define _CONTEXT_SWITCH_H
#include "Process.h"
struct ContextSwitch {
    unsigned int pid;
    int time;
};

struct ContextSwitchDynamicArray {
    struct ContextSwitch ** contextSwitches;
    unsigned int size;
    unsigned int capacity;
};
struct ContextSwitch* createContextSwitch(unsigned int pid, int time);
struct ContextSwitchDynamicArray* createContextSwitchDynamicArray(unsigned int initialCapacity);
void increaseContextSwitchDynamicArrayCapacity(struct ContextSwitchDynamicArray* array);
void addContextSwitchToDynamicArray(struct ContextSwitchDynamicArray* array, struct ContextSwitch* contextSwitch);
void addContextSwitchToDynamicArrayFromProcess(struct ContextSwitchDynamicArray* array, struct Process* process, int time); 
struct ContextSwitch* getContextSwitchAtIndex(struct ContextSwitchDynamicArray* array, unsigned int index);
void freeContextSwitchDynamicArray(struct ContextSwitchDynamicArray* switches); 
void printGanttChart(struct ContextSwitchDynamicArray* array, int time);
#endif
