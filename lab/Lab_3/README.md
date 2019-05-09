# Lab 3 - CPU Scheduling

The goal of this lab was to demonstrate the behaviors for 3 different scheduling algorithms:
 * First Come First Serve
 * Shortest Job First
 * Round Robin

to run - 
  make
  ./Lab3 input_file Algorithm (RR only Quanta)

## Provided Example:

1   0   10
2   1    2
3   2    9
4   3    5

### FCFS:
P1                            P2    P3                         P4
*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

### SJF:
P1 P2    P4             P3                         P1
*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

### RR: 2
P1    P2    P3    P1    P4    P3    P1    P4    P3    P1    P4 P3    P1    P3
*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

## Basic Algorithm:
ContextSwitchArray[] 
ContextSwitch{"Pid":1, "time":1}

SimulateCpu(ArrayOfProcesses, ArrivalQueue)
    integer i = 0
    integer t = 0
    CurrentProcess
    done = false

    while(not done)
        checkArrayAtCurrentIndexForwardForArrivingProcesses(ArrayOfProcesses, ArrivalQueue,i, t)
	    process(CurrentProcess)
	    t = t + 1
	    check(done)
	
checkArrayAtCurrentIndexForwardForArrivingProcesses(arrayOfProcesses, ArrivalQueue, integer i, integer t)
    while(i < arrayOfProcesses.length && arrayOfProcesses[i].arrivalTime <= t)
	    if( arrayOfProcesses[i].arrivalTime == t ) ArrivalQueue.add(arrayOfProcesses[i])
	    i = i + 1

process()
    switch(type)
	
	    case "FCFS:
	
	    case "SJF":
	
	    case "RR":
		
		default:
		    print "No such algorithm"
			exit
		
processToResult(CurrentProcess, t)
	Result.pid = CurrentProcess.pid
    Result.arrivalTime = CurrentProcess.arrivalTime
	Result.burstTime = CurrentProcess.burstTime
	Result.finishTime = t
	Result.waitTime = CurrentProcess.finishTime - (CurrentProcess.arrivalTime + CurrentProcess.burstTime)
	Result.turnAroundTime = CurrentProcess.finishTime = CurrentProcess.arrivalTime
	Result.contextSwitchCount = CurrentProcess.contextSwitchCount
	
FCFS(CurrentProcess, ArrivalQueue) 
    if( CurrentProcess.processTime == CurrentProcess.burstTime )
		processToResult(CurrentProcess)
		CurrentProcess = ArrivalQueue.pop()
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	else
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	
SJF(CurrentProcess, ArrivalQueue)
    if( CurrentProcess.processTime == CurrentProcess.burstTime )
	    processToResult(CurrentProcess)
		CurrentProcess = ArrivalQueue.pop()
		CurrentProcess.processTime = CurrentProcess.processTime + 1
    else if( CurrentProcess.burstTime > ArrivalQueue.peek().burstTime )
		ArrivalQueue.push(CurrentProcess)
		CurrentProcess = ArrivalQueue.pop()
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	else 
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	    
	
RR(CurrentProcess, ArrivalQueue, allowedTime)
	if( CurrentProcess.processTime == CurrentProcess.burstTime )
		processToResult(CurrentProcess)
		CurrentProcess = ArrivalQueue.pop()
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	else if (CurrentProcess.processTime % allowedTime == 0)
	    ArrivalQueue.push(CurrentProcess)
		CurrentProcess = ArrivalQueue.pop()
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	else 
		CurrentProcess.processTime = CurrentProcess.processTime + 1
	
checkDone( )
    if( Results.length == ArrayOfProcesses.length ) 
	    done = true
