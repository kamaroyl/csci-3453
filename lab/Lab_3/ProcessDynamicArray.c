/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#include <stdlib.h>
#include "ProcessDynamicArray.h"
#include "Process.h"

struct ProcessDynamicArray* createProcessDynamicArray(unsigned int initialSize) {
    struct ProcessDynamicArray* array = (struct ProcessDynamicArray*) malloc(sizeof(struct ProcessDynamicArray));
    array->size = 0;
    array->capacity = initialSize;
    array->processes = (struct Process**) malloc(initialSize * sizeof(struct Process*));
    return array;
}

void increaseProcessDynamicArrayCapacity(struct ProcessDynamicArray* array) {
    struct Process** oldArray = array->processes;
    struct Process** newArray = (struct Process**) malloc((1.5 * array->capacity) * sizeof(struct Process*));

    for(int i = 0; i < array->size; ++i) {
        newArray[i] = array->processes[i];
        oldArray[i] = NULL;
    }
    
    array->processes = newArray;
    array->capacity = array->capacity * 1.5;
    free(oldArray);
}

void addProcessToDynamicArray(struct ProcessDynamicArray* array, struct Process* process) {
    if(array->size >= array->capacity) increaseProcessDynamicArrayCapacity(array);
    array->processes[array->size] = process;
    ++(array->size);
}

struct Process* getProcessFromDynamicArray(struct ProcessDynamicArray* array, int index) {
    if(array->size < index) return NULL;
    return array->processes[index];
}

void freeProcessDynamicArrayAndEntries(struct ProcessDynamicArray* array) {
    for(int i = 0; i < array->size; ++i) {
        struct Process* process = array->processes[i];
        array->processes[i] = NULL;
        free(process);
    }
    free(array->processes);
    free(array);
}

void insertionSort(struct ProcessDynamicArray* array) {
    int i, j;
    struct Process* key;
    for( i = 1; i < array->size; ++i ) {
        key = array->processes[i];
        j = i - 1;

        while(j >= 0 && ((struct Process*) array->processes[j])->arrival_time > key->arrival_time) {
            array->processes[j + 1] = array->processes[j];
            --j;
        }
        array->processes[j + 1] = key;
    }
}
