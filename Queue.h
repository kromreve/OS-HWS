#include <iostream>
#include "Process.h"
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

// data structure that represents a node in the tree
// struct QueueNode {
// 	int pri; // holds the key
// 	QueueNode *parent; // pointer to the parent
// 	QueueNode *left; // pointer to left child
// 	QueueNode *right; // pointer to right child
// 	int color; // 1 -> Red, 0 -> Black
// };

class QueueList {
    PPtr head;
    PPtr tail;

  
public:

    int priority;
    QueueList *parent; // pointer to the parent
    QueueList *left; // pointer to left child
    QueueList *right; // pointer to right child
    int color; // 1 -> Red, 0 -> Black

    // Default constructor
    QueueList() {
        head = NULL;
        tail = NULL;
    }

    // Paremeterized constructor
    QueueList(int pri) {
        head = NULL;
        tail = NULL;
        priority = pri;
    }
    // Function to delete the node at given position
    PPtr popProcess();
    // Insert process to end of queue
    void insertProcess(PPtr process);
    // Get promotionTick on head
    int getHeadPTick();
    // Check for empty list.
    bool isEmpty();
    // Print processes in queue
    void printList();
};

typedef QueueList *QueuePtr;

#endif