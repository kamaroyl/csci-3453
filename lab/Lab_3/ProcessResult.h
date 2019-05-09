#ifndef _PROCESS_RESULT_H
#define _PROCESS_RESULT_H
#include "Process.h"
struct ProcessResult {
    unsigned int pid;
    unsigned int arrival;
    unsigned int cpu_burst;
    unsigned int finish;
    unsigned int waiting_time; //(finish - arrival) - burst
    unsigned int turn_around_time; //(finish - arrival)
    unsigned int context_switch_count;
};

struct ProcessResult* createProcessResult(unsigned int pid, unsigned int arrival, unsigned int cpu_burst);
struct ProcessResult* createProcessResultFromProcess(struct Process* process);
void incrementContextSwitchCount(struct ProcessResult* processResult);
void setFinish(struct ProcessResult* processResult, unsigned int time);
void printProcessResult(struct ProcessResult* processResult);
void printResultHeader();

#endif
