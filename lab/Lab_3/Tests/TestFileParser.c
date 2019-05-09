#include <stdio.h>

#include "Process.h"
#include "ProcessDynamicArray.h"
#include "FileParser.h"

int main() {
    struct ProcessDynamicArray* array = parseFile("input");
    for(int i = 0; i < array->size; i++) {
        struct Process* p = array->processes[i];
        printf("pid: %d, arrivalTime: %d, burstTime: %d\n", p->pid, p->arrival_time, p->cpu_burst_time);
    }
    return 0;
}
