#include <stdlib.h>
#include <stdio.h>

#include "ProcessDynamicArray.h"
#include "Process.h"

struct ProcessDynamicArray* parseFile(char* fileName) {
    FILE *fp;
    char tmp[256];
    char space = ' ';
    fp = fopen(fileName, "r");

    struct ProcessDynamicArray* processArray = createProcessDynamicArray(100);

    while(fgets(tmp, sizeof tmp, fp)) {
        int i = 0;
        int j = 0;
        char lineTmp[85];
        unsigned int pid = -1;
        unsigned int arrivalTime = -1;
        unsigned int burstTime = -1;
        char done = 0;
        while(!done){
            if(tmp[i] == '\n') done = 1;
            if(tmp[i] == space || tmp[i] == '\n') {
                j = 0;

                if( pid == -1 ) {
                    pid = atoi(lineTmp);
                } else if( arrivalTime == -1) {
                    arrivalTime = atoi(lineTmp);
                } else if( burstTime == -1 ) {
                    burstTime = atoi(lineTmp);
                }

                for(int k = 0; k < 85; k++) {
                    lineTmp[k] = space;
                }

            } else {
                lineTmp[j] = tmp[i];
            }
            ++i;
            ++j;
        }

        struct Process* newProcess = createProcess(pid, arrivalTime, burstTime);
        addProcessToDynamicArray(processArray, newProcess);
    }
    fclose(fp);
    insertionSort(processArray);
    return processArray;
}
