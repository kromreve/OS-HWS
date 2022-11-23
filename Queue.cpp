#include "Queue.h"

// LinkedList class with a tracked priority number
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