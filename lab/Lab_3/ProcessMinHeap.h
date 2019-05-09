#ifndef PROCESS_MIN_HEAP_H
#define PROCESS_MIN_HEAP_H
#include "Process.h"
struct ProcessMinHeap {
    struct Process** heap;
    unsigned int capacity;
    unsigned int size;
};
int getLeft(int i);
int getRight(int i);
int getParent(int i);
struct ProcessMinHeap* createMinHeap(int initialCapacity);
void heapify(struct ProcessMinHeap* minHeap, int i);
void swap(struct ProcessMinHeap* minHeap, int indexA, int indexB);
void decreaseValue(struct ProcessMinHeap* minHeap, int i);
void insertValue(struct ProcessMinHeap* minHeap, struct Process* newProcess);
struct Process* popMin(struct ProcessMinHeap* minHeap);
struct Process* peekMin(struct ProcessMinHeap* minHeap);
void deleteValue(struct ProcessMinHeap* minHeap, int index);
void freeProcessMinHeap(struct ProcessMinHeap* minHeap);
#endif
