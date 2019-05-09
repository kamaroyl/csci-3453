#include <stdio.h>
#include "Process.h"
#include "ProcessDynamicArray.h"

int main() {
    struct ProcessDynamicArray* array = createProcessDynamicArray(2);
    printf("ProcessDynamicArray: { size: %d, capacity: %d}\n", array->size, array->capacity);
    struct Process* process = createProcess(1, 5, 5);
    addProcessToDynamicArray(array, process);
    process = createProcess(2,2,2);
    addProcessToDynamicArray(array, process);
    printf("ProcessDynamicArray: { size: %d, capacity: %d}\n", array->size, array->capacity);
    process = createProcess(3,1,1);
    addProcessToDynamicArray(array, process);
    printf("ProcessDynamicArray: { size: %d, capacity: %d}\n", array->size, array->capacity);

    struct Process* retrieve = getProcessFromDynamicArray(array, 0);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d}\n", retrieve->pid, retrieve->arrival_time, retrieve->cpu_burst_time);
    insertionSort(array);
    retrieve = getProcessFromDynamicArray(array, 0);
    printf("Process: { pid: %d, arrival_time: %d, cpu_burst_time: %d}\n", retrieve->pid, retrieve->arrival_time, retrieve->cpu_burst_time);
    freeProcessDynamicArrayAndEntries(array);
    return 0;
}
