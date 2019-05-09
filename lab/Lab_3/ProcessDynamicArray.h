#ifndef _PROCESS_DYNAMIC_ARRAY_H
#define _PROCESS_DYNAMIC_ARRAY_H
struct ProcessDynamicArray {
    unsigned int size;
    unsigned int capacity;
    struct Process** processes;
     
};
struct ProcessDynamicArray* createProcessDynamicArray(unsigned int initialSize); 
void addProcessToDynamicArray(struct ProcessDynamicArray* dynamicArray, struct Process* process);
struct Process* getProcessFromDynamicArray(struct ProcessDynamicArray* array, int index);
void freeProcessDynamicArrayAndEntries(struct ProcessDynamicArray* array);
void insertionSort(struct ProcessDynamicArray* array);
#endif
