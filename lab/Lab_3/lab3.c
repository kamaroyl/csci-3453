#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "ProcessDynamicArray.h"
#include "ProcessLinkedList.h"
#include "ShortestJobFirst.h"
#include "FirstComeFirstServe.h"
#include "RoundRobin.h"
#include "FileParser.h"
#include "ContextSwitch.h"
#include "ProcessResult.h"
#include "ProcessResultsDynamicArray.h"
#include "ProcessMinHeap.h"

char getAlgorithm(char* input) {
    char* sjf = "SJF";
    char* fcfs = "FCFS";
    int i = 0;
    
    //check sjf
    if( input[0] == sjf[0] && input[1] == sjf[1] && input[2] == sjf[2] ) return 0;
    if( input[0] == fcfs[0] && input[1] == fcfs[1] && input[2] == fcfs[2] && input[3] == fcfs[3] ) return 1;
    return -1;
}

char isRR(char* input) {
    return (input[0] == 'R' && input[1] == 'R' && input[2] == '\0');
}

void checkArrayAtCurrentIndexForwardForArrivingProcesses(struct ProcessDynamicArray* arrayOfProcesses, struct LinkedList* arrivalQueue, int* i, int time) {
    while( *i < arrayOfProcesses->size && (getProcessFromDynamicArray(arrayOfProcesses, *i))->arrival_time <= time ) {
        struct Process* process = getProcessFromDynamicArray(arrayOfProcesses, *i);
        if( process->arrival_time == time ) addLinkedListNode(arrivalQueue, process);
        ++(*i);
    }
}

void checkArrayAtCurrentIndexForwardForArrivingProcessesMin(struct ProcessDynamicArray* arrayOfProcesses, struct ProcessMinHeap* arrivalQueue, int* i, int time) {
    while( *i < arrayOfProcesses->size && (getProcessFromDynamicArray(arrayOfProcesses, *i))->arrival_time <= time ) {
        struct Process* process = getProcessFromDynamicArray(arrayOfProcesses, *i);
        if( process->arrival_time == time ) insertValue(arrivalQueue, process);
        ++(*i);
    }
}

int main(int argc, char* argv[]) {
    char SJF = 0;
    char FCFS = 1;
    char RR = 2; 

    char* input_file;
    char algorithm = -1;
    int quanta = 0;
    int time = 0;
    int i = 0;

    struct Process* currentProcess = NULL;
    struct ProcessDynamicArray* arrayOfProcesses = NULL;
    
    struct ProcessResultsDynamicArray* results = createProcessResultsDynamicArray(30); 
    struct ContextSwitchDynamicArray* timeline = createContextSwitchDynamicArray(30);
    


    if(argc == 3 ) {

        input_file = argv[1];
        
        if( access(input_file, F_OK ) == -1) {
            printf("%s does not exist, exiting\n", input_file);
        }

        algorithm = getAlgorithm(argv[2]);

        if(algorithm == -1 ) {
            printf("no matching algorithm!\nMust be SJF, FCFS or RR with a Quanta\n");
            return -1;
        }
        
    } else if(argc == 4){
        input_file = argv[1];

        if( access(input_file, F_OK ) == -1) {
            printf("%s does not exist, exiting\n", input_file);
        }

        algorithm = isRR(argv[2]);

        if(algorithm == 0) {
            printf("Algorithm is not round robin but there are three arguments.\nExiting\n");
            return -1;
        } else {
            algorithm = RR;
        }

        quanta = atoi(argv[3]);

    } else {
        printf("Wrong number of arguments!\nUsage:\nexecutable input_file algorithm (quantum if rr)\n");
        return -1;
    }

    //pull in Processes from file
    arrayOfProcesses = parseFile(input_file);

    /* DEBUG
    printf("Parsed Processes:\n");
    for(int k = 0; k < arrayOfProcesses->size; ++k) {
        struct Process * tmp = arrayOfProcesses->processes[k];
        printf("Process: { pid: %d, arrival_time: %d, burst_time: %d } \n", tmp->pid, tmp->arrival_time, tmp->cpu_burst_time);
    }*/
    
    if(algorithm == SJF) {
        struct ProcessMinHeap* arrivalQueue = createMinHeap(30);
        while( results->size < arrayOfProcesses->size ) {
            checkArrayAtCurrentIndexForwardForArrivingProcessesMin(arrayOfProcesses, arrivalQueue, &i, time);
            shortestJobFirst(&currentProcess, arrivalQueue, results, timeline, time);
            ++time;
        }
        freeProcessMinHeap(arrivalQueue);
    } else if(algorithm == FCFS) {
        struct LinkedList* arrivalQueue = initLinkedList();
        while( results->size < arrayOfProcesses->size ) {
            checkArrayAtCurrentIndexForwardForArrivingProcesses(arrayOfProcesses, arrivalQueue, &i, time);
            firstComeFirstServe(&currentProcess, arrivalQueue, results, timeline, time);
            ++time;
        }
        freeProcessLinkedList(arrivalQueue);
    } else if(algorithm == RR) {
        struct LinkedList* arrivalQueue = initLinkedList();
        while( results->size < arrayOfProcesses->size ) {
            checkArrayAtCurrentIndexForwardForArrivingProcesses(arrayOfProcesses, arrivalQueue, &i, time);
            roundRobin(&currentProcess, arrivalQueue, results, timeline, time, quanta);
            ++time;
        }
        freeProcessLinkedList(arrivalQueue);
    }

    printGanttChart(timeline, time);
    printResults(results);
    
    //FREE THE OBJECTS 
    currentProcess = NULL;
    freeProcessDynamicArrayAndEntries(arrayOfProcesses);
    freeProcessResultDynamicArray(results);
    freeContextSwitchDynamicArray(timeline);
    return 0;
}
