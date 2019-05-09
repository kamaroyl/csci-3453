#include <stdlib.h>
#include <stdio.h>
#include "ContextSwitch.h"
#include "Process.h"

struct ContextSwitch* createContextSwitch(unsigned int pid, int time) {
    struct ContextSwitch* newSwitch = (struct ContextSwitch*) malloc(sizeof(struct ContextSwitch));
    newSwitch->pid = pid;
    newSwitch->time = time;

    return newSwitch;
}

struct ContextSwitchDynamicArray* createContextSwitchDynamicArray(unsigned int initialCapacity) {
    struct ContextSwitchDynamicArray* array = (struct ContextSwitchDynamicArray*) malloc(sizeof(struct ContextSwitchDynamicArray));
    array->size = 0;
    array->capacity = initialCapacity;
    array->contextSwitches = (struct ContextSwitch**) malloc(initialCapacity * sizeof(struct ContextSwitch*));
    return array;
}

void increaseContextSwitchDynamicArrayCapacity(struct ContextSwitchDynamicArray* arr) {
    struct ContextSwitch** oldArray = arr->contextSwitches;
    struct ContextSwitch** newArray = (struct ContextSwitch**) malloc((1.5 * arr->capacity) * sizeof(struct ContextSwitch*));

    for(int i = 0; i < arr->size; ++i) {
        newArray[i] = oldArray[i];
        oldArray[i] = NULL;
    }

    arr->contextSwitches = newArray;
    arr->capacity = arr->capacity * 1.5;
    free(oldArray);
}

void addContextSwitchToDynamicArray(struct ContextSwitchDynamicArray* array, struct ContextSwitch* contextSwitch) {
    if(array->size >= array->capacity) increaseContextSwitchDynamicArrayCapacity(array);
    array->contextSwitches[array->size] = contextSwitch;
    ++(array->size);
}

void addContextSwitchToDynamicArrayFromProcess(struct ContextSwitchDynamicArray* array, struct Process* process, int time) {
    struct ContextSwitch* contextSwitch = createContextSwitch(process->pid, time);
    addContextSwitchToDynamicArray(array, contextSwitch);
}

struct ContextSwitch* getContextSwitchAtIndex(struct ContextSwitchDynamicArray* array, unsigned int index) {
    if( array->size < index ) return NULL;
    return array->contextSwitches[index];
}

void freeContextSwitchDynamicArray(struct ContextSwitchDynamicArray* switches) {
    for( int i = 0; i < switches->size; ++i) {
        struct ContextSwitch* contextSwitch = switches->contextSwitches[i];
        switches->contextSwitches[i] = NULL;
        free(contextSwitch);
    }

    free(switches->contextSwitches);
    free(switches);
}

void printGanttChart(struct ContextSwitchDynamicArray* array, int endTime) {
    int j = 0;
    struct ContextSwitch* contextSwitch = array->contextSwitches[0];
    for(int i = 0; i < endTime; ++i) {
        if(contextSwitch != NULL && contextSwitch->time == i) {
            
            printf("P%.2d", contextSwitch->pid);
            ++j;
            contextSwitch = array->contextSwitches[j];
        } else {
            printf("   ");
        }
    }
    printf("\n");
    for(int i = 0; i < endTime - 1; ++i) {
        printf("*  ");
    }
    printf("\n");
}
