/*
 * Ben Straub
 * csci 3453
 * 12/5/2019
 */
#include <stdlib.h>
#include <stdio.h>
#include "ProcessResult.h"
#include "Process.h"

struct ProcessResult* createProcessResult(unsigned int pid, unsigned int arrival, unsigned int cpu_burst) {
    struct ProcessResult* processResult = (struct ProcessResult*) malloc(sizeof(struct ProcessResult));
    processResult->pid = pid;
    processResult->arrival = arrival;
    processResult->cpu_burst = cpu_burst;
    processResult->context_switch_count = 0;
    processResult->finish = 0;
    processResult->waiting_time = 0;
    processResult->turn_around_time = 0;
    return processResult;
}

struct ProcessResult* createProcessResultFromProcess(struct Process* process) {
    struct ProcessResult* processResult = (struct ProcessResult*) malloc(sizeof(struct ProcessResult));
    processResult->pid = process->pid;
    processResult->arrival = process->arrival_time;
    processResult->cpu_burst = process->cpu_burst_time;
    processResult->context_switch_count =  process->context_switch_count;
    processResult->finish = 0;
    processResult->waiting_time = 0;
    processResult->turn_around_time = 0;
    return processResult;
}

void incrementContextSwitchCount(struct ProcessResult* processResult) {
    ++(processResult->context_switch_count);
}

void setFinish(struct ProcessResult* processResult, unsigned int time) {
    processResult->finish = time;
    processResult->waiting_time = (processResult->finish - processResult->arrival) - processResult->cpu_burst;
    processResult->turn_around_time = (processResult->finish - processResult->arrival);
}

void printResultHeader() {
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("|  pid   |   arrival  |  CPU-Burst |  finish  |  waiting time  |  turn around  |   No. of Context   |\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
}

void printProcessResult(struct ProcessResult* pr) {
    //      |   pid  |   arrival  |  CPU-Burst |  finish  |  waiting time  |  turn around  |   No. of Context   |
    //      -----------------------------------------------------------------------------------------------------
    printf("|  %.4d  |    %.4d    |    %.4d    |   %.4d   |      %.4d      |      %.4d     |       %.4d         |\n", pr->pid, pr->arrival, pr->cpu_burst, pr->finish, pr->waiting_time, pr->turn_around_time, pr->context_switch_count);
    printf("-----------------------------------------------------------------------------------------------------\n");
}
