/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#ifndef _PROCESS_RESULTS_DYNAMIC_ARRAY_H
#define _PROCESS_RESULTS_DYNAMIC_ARRAY_H
#include "Process.h"
struct ProcessResultsDynamicArray {
    unsigned int size;
    unsigned int capacity;
    struct ProcessResult** results;
};
struct ProcessResultsDynamicArray* createProcessResultsDynamicArray(unsigned int initialSize);
void addResultToDynamicArray(struct ProcessResultsDynamicArray* resultsArray, struct ProcessResult* result);
struct ProcessResult* getProcessResultFromDynamicArray(struct ProcessResultsDynamicArray* array, unsigned int index);
void processToResult(struct Process* process, struct ProcessResultsDynamicArray* array, int time);
void printResults(struct ProcessResultsDynamicArray* array);
void freeProcessResultDynamicArray(struct ProcessResultsDynamicArray* array);
#endif
