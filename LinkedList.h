#include <iostream>
using namespace std;
  
// Node class to represent
// a node of the linked list.
class Node {
public:
    int pid;
    int bst;
    int arrival;
    int priority;
    int basePriority;
    int io;
    int promotionClockTick;
    Node* next;
  
    // Default constructor
    Node()
    {
        pid, bst, arrival, priority, io = 0;
        promotionClockTick = 0;
        next = NULL;
    }
  
    // Parameterised Constructor
    Node(int a, int b, int c, int d, int e, int promotionClockTick)
    //a pid, b burst, c arrival, d priority, e io
    {
        this->pid = a;
        this->bst = b;
        this->arrival = c;
        this->priority = d;
        this->io = e;
        this->promotionClockTick = promotionClockTick;
        this->next = NULL;
    }
};
  
// Linked list class to
// implement a linked list.
class Linkedlist {
    Node* head;
    
  
public:
    int priority;
    // Default constructor
    Linkedlist() { 
        head = NULL; 
    }

    Linkedlist(int p) { 
        head = NULL; 
        priority = p;
    }
  
    // Function to insert a
    // node at the end of the
    // linked list.
    void insertNode(int, int, int, int, int, int);
  
    // Function to print the
    // linked list.
    void printList();

    //Gets the clock tick promotion value of the last node in the list
    int getLastClockTick();

    //Gets the PID of the last node that needs to be promoted
    int getLastPID();

    Node getLastNode();

    //check to see if the list is empty
    bool isEmpty();
  
    // Function to delete the
    // node at given position
    void deleteNode(int);

};
  
// Function to delete the
// node at given position
void Linkedlist::deleteNode(int nodeOffset)
{
    Node *temp1 = head, *temp2 = NULL;
    int ListLen = 0;
  
    if (head == NULL) {
        cout << "List empty." << endl;
        return;
    }
  
    // Find length of the linked-list.
    while (temp1 != NULL) {
        temp1 = temp1->next;
        ListLen++;
    }
  
    // Check if the position to be
    // deleted is less than the length
    // of the linked list.
    if (ListLen < nodeOffset) {
        cout << "Index out of range"
             << endl;
        return;
    }
  
    // Declare temp1
    temp1 = head;
  
    // Deleting the head.
    if (nodeOffset == 1) {
  
        // Update head
        head = head->next;
        delete temp1;
        return;
    }
  
    // Traverse the list to
    // find the node to be deleted.
    while (nodeOffset-- > 1) {
  
        // Update temp2
        temp2 = temp1;
  
        // Update temp1
        temp1 = temp1->next;
    }
  
    // Change the next pointer
    // of the previous node.
    temp2->next = temp1->next;
  
    // Delete the node
    delete temp1;
}
  
// Function to insert a new node.
void Linkedlist::insertNode(int a, int b, int c, int d, int e, int promotionClockTick)
{
    // Create the new Node.
    Node* newNode = new Node(a, b, c, d, e, promotionClockTick);
  
    // Assign to head
    if (head == NULL) {
        head = newNode;
        return;
    }
  
    // Traverse till end of list
    Node* temp = head;
    while (temp->next != NULL) {
  
        // Update temp
        temp = temp->next;
    }
  
    // Insert at the last.
    temp->next = newNode;
}

int Linkedlist::getLastClockTick(){
    Node* temp = head;
    int promotionTick = temp->promotionClockTick;

    // while (temp != NULL) {
    //     //cout << temp->PID << " ";
    //     promotionTick = temp->promotionClockTick;
    //     temp = temp->next;
    // }
    
    return promotionTick;
}

int Linkedlist::getLastPID(){
    Node* temp = head;
    int id = temp->pid;

    // while (temp != NULL) {
    //     //cout << temp->PID << " ";
    //     id = temp->PID;
    //     temp = temp->next;
    // }
    
    return id;
}

Node Linkedlist::getLastNode(){
    Node* temp = head;

    while (temp != NULL) {
        //cout << temp->PID << " ";
        temp = temp->next;
    }
    return *temp;
}

bool Linkedlist::isEmpty(){
    Node* temp = head;
  
    // Check for empty list.
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}
  
// Function to print the
// nodes of the linked list.
void Linkedlist::printList()
{
    Node* temp = head;
  
    // Check for empty list.
    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }
  
    // Traverse the list.
    while (temp != NULL) {
        cout << temp->pid << " " << temp->arrival << '\n';
        temp = temp->next;
    }
}