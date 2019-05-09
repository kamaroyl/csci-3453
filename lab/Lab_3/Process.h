/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#ifndef _PROCESS_H
#define _PROCESS_H
struct Process {
    unsigned int pid;
    unsigned int arrival_time;
    unsigned int cpu_burst_time;
    unsigned int process_time;
    unsigned int context_switch_count;
};

struct Process* createProcess(unsigned int pid, unsigned int arrival_time, unsigned int cpu_burst_time); 
#endif


