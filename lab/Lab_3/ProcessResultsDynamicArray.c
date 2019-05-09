#include <stdlib.h>
#include <stdio.h>
#include "ProcessResultsDynamicArray.h"
#include "ProcessResult.h"

struct ProcessResultsDynamicArray* createProcessResultsDynamicArray(unsigned int initialSize) {
    struct ProcessResultsDynamicArray* array = (struct ProcessResultsDynamicArray*) (struct ProcessResultsDynamicArray*) malloc(sizeof(struct ProcessResultsDynamicArray));
    array->size = 0;
    array->capacity = initialSize;
    array->results = (struct ProcessResult**) malloc(initialSize* sizeof(struct ProcessResult*));
    return array;
}

void increaseProcessResultsDynamicArrayCapacity(struct ProcessResultsDynamicArray* array) {
    struct ProcessResult** oldArray = array->results;
    struct ProcessResult** newArray = (struct ProcessResult**) malloc((1.5 * array->capacity) * sizeof(struct ProcessResult*));

    for(int i = 0; i < array->size; ++i) { 
        newArray[i] = array->results[i];
        oldArray[i] = NULL;
    }

    array->results = newArray;
    array->capacity = array->capacity * 1.5;
    free(oldArray);
}

void addResultToDynamicArray(struct ProcessResultsDynamicArray* array, struct ProcessResult* result) {
    if(array->size >= array->capacity) increaseProcessResultsDynamicArrayCapacity(array);
    array->results[array->size] = result;
    ++(array->size);
}

struct ProcessResult* getProcessResultFromDynamicArray(struct ProcessResultsDynamicArray* array, unsigned int index) {
    if(array->size < index) return NULL;
    return array->results[index];
}

void processToResult(struct Process* process, struct ProcessResultsDynamicArray* array, int time) {
    struct ProcessResult* result = createProcessResultFromProcess(process);
    setFinish(result, time);
    addResultToDynamicArray(array, result);
}

void printResults(struct ProcessResultsDynamicArray* array) {
    printResultHeader();
    double averageBurstTime = 0;
    double averageWaitTime = 0;
    double averageTurnAroundTime = 0;
    int totalContextSwitchCount = 0;
    for(int i = 0; i < array->size; ++i) {
        struct ProcessResult* result = getProcessResultFromDynamicArray(array, i);
        printProcessResult(result);
        averageBurstTime += result->cpu_burst;
        averageWaitTime += result->waiting_time;
        averageTurnAroundTime += result->turn_around_time;
        totalContextSwitchCount += result->context_switch_count;
    }
    averageBurstTime /= array->size;
    averageWaitTime /= array->size;
    averageTurnAroundTime /= array->size;
    printf("Average CPU burst time = %lf ms\n", averageBurstTime);
    printf("Average waiting time = %lf ms\n", averageWaitTime);
    printf("Average turn around time = %lf ms\n", averageTurnAroundTime);
    printf("Total No. of Context Switching Performed = %d\n", totalContextSwitchCount);
}

void freeProcessResultDynamicArray(struct ProcessResultsDynamicArray* array) {
    for(int i = 0; i < array->size; ++i) {
        struct ProcessResult* result = array->results[i];
        array->results[i] = NULL;
        free(result);
    }
    free(array->results);
    free(array);
}
