struct Process {
    int pid,
    burst,
    arrival,
    priority,
    ogPriority,
    ioTime,
    waitTotal;

    Process* next;
    Process* prev;

    Process(int id, int bst, int pri, int arvl, int io) {
        pid = id;
        burst = bst;
        priority = ogPriority = pri;
        arrival = arvl;
        ioTime = io;

        waitTotal = 0;

    }
};

typedef Process* PPtr;

class QueueList {
    public:
    PPtr last;
    PPtr current;
    int totalNum; //number of Nodes in QueueList
    int priority; //priority number of QueueList

    QueueList(int pri)
    {
        current = last;
        last = nullptr;
        totalNum = 0;
        priority = pri;
    }

    //add new process/node
    void insert(PPtr node, int clockTick);
    void move(PPtr node, QueueList q[], int newPri);
};

void QueueList::insert(PPtr process, int clockTick) {
    if (totalNum = 0) { //set current of LinkedList to the new process if list is empty
        current = last = process;
    } else { //
        process->next = last;
        last->prev = process;
        last = process;
    }
    totalNum++;
    current->prev == nullptr;
}