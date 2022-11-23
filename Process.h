#ifndef PROC_H
#define PROC_H

struct Process {
    int pid, 
    burst, 
    arrival, 
    priority, 
    lastRun,
    lastMove, 
    io, 
    waitTime, 
    completionTime, 
    waitTot,
    promoteTick;

    //is used in a linked list
    Process* next; 

    //Default Contstructor
    // Process()
    // {
    //     pid = 0;
    //     burst = 0;
    //     arrival = 0;
    //     priority = 0;
    //     lastRun = 0;
    //     lastMove = 0;
    //     io = 0;
    //     completionTime = 0;
    //     waitTot = 0;
    //     promoteTick = 0;
    //     const int basePriority = 0;

    //     next = nullptr;
    // }
    
    //Constructor
    Process(int id, int bst, int arvl, int pri, int ioTime)
    {
        pid = id;
        burst = bst;
        arrival = lastRun = arvl;
        priority = pri;
        io = ioTime;
        lastRun = 0;
        lastMove = 0;
        waitTime = 0;
        completionTime = 0;
        waitTot = 0;
        promoteTick = arrival + 100;
        const int basePriority = priority;

        next = nullptr;
    }
};

typedef Process* PPtr;

#endif