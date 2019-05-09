#include "Process.h"
#include <stdlib.h>
struct Process* createProcess(unsigned int pid, unsigned int arrival_time, unsigned int cpu_burst_time) {
    struct Process* process = (struct Process*) malloc(sizeof(struct Process));
    process->pid = pid;
    process->arrival_time = arrival_time;
    process->cpu_burst_time = cpu_burst_time;
    process->process_time = 0;

    return process;
}
