struct Process {
    int pid, 
    burst, 
    arrival, 
    priority,
    basePriority, 
    lastRun,
    lastMove, 
    io, 
    waitTime, 
    completionTime, 
    waitTot; //track waitTime
    //bool kernel;

    //is used in a doubly-linked list
    Process* next; 
    Process* prev;

    //Default Contstructor
    Process()
    {
        pid = 0;
        burst = 0;
        arrival = 0;
        priority = 0;
        basePriority = 0;
        lastRun = 0;
        lastMove = 0;
        io = 0;
        completionTime = 0;
        waitTot = 0;
        waitTot = 0;
        next = prev = nullptr;
        //kernel = false;
    }
    
    //Paremeterized Constructor
    Process(int id, int bst, int arvl, int pri, int ioTime)
    {
        pid = id;
        burst = bst;
        arrival = lastRun = arvl;
        priority = basePriority = pri;
        io = ioTime;
        lastRun = 0;
        lastMove = 0;
        waitTime = 0;
        completionTime = 0;
        waitTot = 0;
        next = nullptr;
        prev = nullptr;
    }
};

typedef Process* PPtr;