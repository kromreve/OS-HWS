#include <iostream>
#include "Process.h"
using namespace std;

// data structure that represents a node in the tree
struct QueueNode {
	int pri; // holds the key
	QueueNode *parent; // pointer to the parent
	QueueNode *left; // pointer to left child
	QueueNode *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef QueueList *QueuePtr;

// LinkedList class with a tracked priority number
class QueueList {
    PPtr head;
    PPtr tail;
    int priority;

  
public:
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
  
// Function to delete the node at given position
PPtr QueueList::popProcess() {
    if (isEmpty()) {
        cout << "List empty." << endl;
        return nullptr;
    }
    PPtr temp = head;
    head = head->next;
    temp->next = NULL;
    return temp;
}
  
// Insert process to end of queue
void QueueList::insertProcess(PPtr process) {
    if (isEmpty()) {
        head = tail = process;
        return;
    }
    // Traverse to end of queue
    while (tail->next != NULL) {
        tail = tail->next;
    }
    // Insert at end of queue
    tail->next = process;
}

// Get promotionTick on head
int QueueList::getHeadPTick() {
    int promoteTick = head->promoteTick;
    return promoteTick;    
}

// Check for empty list.
bool QueueList::isEmpty() {
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}

// print processes in queue
void QueueList::printList() {
    PPtr temp = head;
    // Check for empty list.
    if (this->isEmpty()) {
        cout << "List empty" << endl;
        return;
    }
    // Traverse the list.
    while (temp != NULL) {
        cout << "(id: " << temp->pid << " promoteTime:" << temp->promoteTick << ") " <<endl;
        temp = temp->next;
    }
    delete temp;
}