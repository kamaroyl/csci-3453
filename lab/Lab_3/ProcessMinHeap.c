/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#include "ProcessMinHeap.h"
#include <stdlib.h>
#include <stdio.h>
int getLeft(int i) {
    return (2 * i + 1);
}

int getRight(int i) {
    return (2 * i + 2);
}

int getParent(int i) {
    return ((i - 1) / 2);
}

struct ProcessMinHeap* createMinHeap(int initialCapacity) {
    struct ProcessMinHeap* minHeap = (struct ProcessMinHeap*) malloc(sizeof(struct ProcessMinHeap));
    minHeap->heap = (struct Process**) malloc(initialCapacity * sizeof(struct Process*));
    for(int i = 0; i < initialCapacity; ++i) {
        minHeap->heap[i] = NULL;
    }
    minHeap->size = 0;
    minHeap->capacity = initialCapacity;
    return minHeap;
}

void heapify(struct ProcessMinHeap* minHeap, int index) {

    int l = getLeft(index);
    int r = getRight(index);
    int smallest = index;

    if( l < minHeap->size ) {
        if( minHeap->heap[l]->cpu_burst_time < minHeap->heap[index]->cpu_burst_time ) {
            smallest = l;
        }
    }

    if( r < minHeap->size ) {
        if( minHeap->heap[r]->cpu_burst_time < minHeap->heap[smallest]->cpu_burst_time ) {
            smallest = r;
        }
    }

    if( smallest != index ) {
        swap(minHeap, index, smallest);
        heapify(minHeap, smallest);
    }
}

void swap(struct ProcessMinHeap* minHeap, int indexA, int indexB) {
    struct Process* tmp = minHeap->heap[indexA];
    minHeap->heap[indexA] = minHeap->heap[indexB];
    minHeap->heap[indexB] = tmp;
}

void decreaseValue(struct ProcessMinHeap* minHeap, int i) {

    int parent = getParent(i);

    while( i > 0 && minHeap->heap[parent]->cpu_burst_time > minHeap->heap[i]->cpu_burst_time ) {
        swap(minHeap, parent, i);
        i = parent;
        parent = getParent(i);
    }
}

void insertValue(struct ProcessMinHeap* minHeap, struct Process* newProcess) {
    if( minHeap->size == minHeap->capacity) return;
    int i = minHeap->size;
    int parent = getParent(i);

    minHeap->heap[i] = newProcess;
    ++(minHeap->size);
    while( i > 0 && minHeap->heap[parent]->cpu_burst_time > minHeap->heap[i]->cpu_burst_time ) {
        swap(minHeap, i, parent);
        i = parent;
        parent = getParent(i);
    }
}

struct Process* peekMin(struct ProcessMinHeap* minHeap) {
    struct Process* minProcess = NULL;

    if( minHeap->size > 0 ) {
        minProcess = minHeap->heap[0];
    }

    return minProcess;
}

struct Process* popMin(struct ProcessMinHeap* minHeap) {
    struct Process* minProcess = NULL;

    if( minHeap->size <= 0 ) {
        //NO-OP
    } else if( minHeap->size == 1 ) {
        --(minHeap->size);
        minProcess = minHeap->heap[0];
        minHeap->heap[0] = NULL;
        return minProcess;
    } else {
        
        minProcess = minHeap->heap[0];

        for(int i = 1; i < minHeap->size; ++i) {
            minHeap->heap[i - 1] = minHeap->heap[i];
        }
        minHeap->heap[--(minHeap->size)] = NULL;
        heapify(minHeap, 0);
    }
    
    return minProcess;
}

void deleteValue(struct ProcessMinHeap* minHeap, int index) {
    struct Process* processToRemove = minHeap->heap[index];
    if( processToRemove == NULL ) return;
    processToRemove->cpu_burst_time = 0;
    decreaseValue(minHeap, index);
    popMin(minHeap);
}

void freeProcessMinHeap(struct ProcessMinHeap* minHeap) {
    for( int i = 0; i < minHeap->size; ++i) {
        minHeap->heap[i] = NULL;
    }
    free(minHeap->heap);
    free(minHeap);
}
