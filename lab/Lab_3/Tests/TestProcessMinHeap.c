#include <stdio.h>
#include <stdlib.h>

#include "Process.h"
#include "ProcessMinHeap.h"

int main() {
    struct ProcessMinHeap* minHeap = createMinHeap(5);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    struct Process* p1 = createProcess(1,1,1);
    insertValue(minHeap, p1);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    struct Process* p2 = createProcess(2,2,2);
    insertValue(minHeap, p2);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    struct Process* p3 = createProcess(0,0,0);
    insertValue(minHeap, p3);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    struct Process* result = popMin(minHeap);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d }\n", result->pid, result->arrival_time, result->cpu_burst_time);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    result = popMin(minHeap);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d }\n", result->pid, result->arrival_time, result->cpu_burst_time);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    result = popMin(minHeap);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d }\n", result->pid, result->arrival_time, result->cpu_burst_time);
    printf("ProcessMinHeap { size: %d, capacity: %d }\n", minHeap->size, minHeap->capacity);
    result = NULL;
    freeProcessMinHeap(minHeap);
    free(p1);
    free(p2);
    free(p3);
    return 0;
}
