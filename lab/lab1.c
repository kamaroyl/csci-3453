#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>

void getUnameInfo() {
    printf("Part A\n");
    struct utsname unameData;
    uname(&unameData);
    printf("System Name: %s\n", unameData.sysname );
    printf("Node Name: %s \n",  unameData.nodename);
    printf("Release: %s \n",    unameData.release );
    printf("Version: %s \n",    unameData.version );
    printf("Machine: %s \n",    unameData.machine );
    printf("\n");
}

void epochToDateTime( long value) {
    char buf[80];
    struct tm ts;
    ts = *localtime(&value);
    //time_t rawTime = (time_t) value;
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    printf("Date last booted: %s\n", buf);
}

void getProcStatInfo() {
    char result[64];
    char tmp[256];
    char *btimeSearchString = "btime";
    char *cpuSearchString   = "cpu  ";
    char end = '\n';
    char delim = ' ';
    FILE *fp;
    fp = fopen("/proc/stat", "r");

    //Go through file until you find the cpu line
    char cpuLine[2][64]; //array from cpu line

    while(fgets(tmp, sizeof tmp, fp)) {
        char found = 1;
        for(int i = 0; i < 5; i++) {
            if(tmp[i] != cpuSearchString[i]) {
                found = 0;
                break;
            }
        }
        
        if( found == 1 ) {
            int i = 5;           
                         
            //space delimited list
            
            //get time in user mode
            while(tmp[i] != delim) {
                cpuLine[0][i - 5] = tmp[i];
                i++;
            }
            
            i++; //skip over space
             
            //skip over nice value
            while(tmp[i] != delim) {
                i++;
            }
    
            i++; //skip over space
            int rezero = i;            

            while(tmp[i] != delim) {
                cpuLine[1][i - rezero] = tmp[i];
                i++;
            }

            break;
        }
    }
    
    printf("Time in User Mode: %s jiffies\n", cpuLine[0]);
    printf("Time in System Mode: %s jiffies\n", cpuLine[1]);
    
    //reset the file pointer
    rewind(fp);
    
    //Go through file until you find the character sequence "btime"
    while(fgets(tmp, sizeof tmp, fp)) {
        char found = 1;
        for(int i = 0; i < 5; i++) {
           if(tmp[i] != btimeSearchString[i]) {
               found = 0;
               break;
           }
        }

        if( found == 1 ) {
            char end = '\n';
            int i = 6;
            while(tmp[i] != end) {
                result[i-6] = tmp[i];
                i++;
            }
            break;
        }
    }
    fclose(fp); 
    long timeStamp = atol(result);
    epochToDateTime(timeStamp);

}

void getProcUptimeInfo() {
    FILE *fp;
    fp = fopen("/proc/uptime", "r");
    char delim = ' ';
    char tmp[256];
    char result[64];

    while(fgets(tmp, sizeof tmp, fp)) {
        int i = 0;
        while(tmp[i] != delim) {
            result[i] = tmp[i];
            i++;
        }
        break;
    }
    fclose(fp); 

    long resultLong = atol(result);
    int secondsInAMinute = 60;
    int secondsInAnHour = 3600; 
    int secondsInADay = 24 * secondsInAnHour;   
    int days = resultLong / secondsInADay;
    resultLong %= secondsInADay;
    int hours = resultLong / secondsInAnHour;
    resultLong %= secondsInAnHour;
    int mins = resultLong / secondsInAMinute;
    resultLong %= secondsInAMinute;
    int seconds = resultLong;
    
    printf("Total Uptime: %.2d:%.2d:%.2d:%.2d\n", days, hours, mins, seconds);

}

void getProcMemInfo() {
    FILE *fp;
    char tmp[256];
    char space = ' ';
    fp = fopen("/proc/meminfo", "r");
    char *memTotalSearchString = "MemTotal:";
    char *memAvailableSearchString = "MemAvailable:";
    
    char totalMemResult[16];
    char availableMemResult[16];    


    while(fgets(tmp, sizeof tmp, fp)) {
        char found = 1;
        for(int i = 0; i < 9 ; i++) {
            if(tmp[i] != memTotalSearchString[i]) {
                found = 0;
                break;
            }
        }
            
        if( found == 1 ) {
            int i = 9;
               
            //skip all spaces
            while(tmp[i] == space) {
                i++;
            }
            int reZero = i;    
            while(tmp[i] != space) {
                totalMemResult[i - reZero] = tmp[i];
                i++;
            }
                     
            long totalMemResultLong = atol(totalMemResult); 
            printf("Total Memory: %ld kb\n", totalMemResultLong);
            break;
        }
    }
    
    rewind(fp);

    while(fgets(tmp, sizeof tmp, fp)) {
        char found = 1;
        for(int i = 0; i < 13 ; i++) {
            if(tmp[i] != memAvailableSearchString[i]) {
                found = 0;
                break;
            }
        }
            
        if( found == 1 ) {
            int i = 13;
               
            //skip all spaces
            while(tmp[i] == space) {
                i++;
            }
            
            int reZero = i;
    
            while(tmp[i] != space) {
                availableMemResult[i - reZero] = tmp[i];
                i++;
            }
        
            printf("Available Memory: %ld kb\n", atol(availableMemResult));
            break;
        }
    }
 
    fclose(fp); 
}

void getProcInfo() {
    printf("Part B\n");
    getProcStatInfo();
    getProcUptimeInfo();
    getProcMemInfo();
}


int main() {
    getUnameInfo();
    getProcInfo();
    return 0;
}

