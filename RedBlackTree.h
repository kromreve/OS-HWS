#include <string>
#include "Queue.h"
using std::string;

#ifndef TREE_H
#define TREE_H


class RBTree {
    
private:

    QueuePtr root;
    QueuePtr TNULL;

    void initializeNULLNode(QueuePtr node, QueuePtr parent);
    void preOrderHelper(QueuePtr node);
    void inOrderHelper(QueuePtr node);
    void postOrderHelper(QueuePtr node);
    QueuePtr searchTreeHelper(QueuePtr node, int key);
    void fixDelete(QueuePtr x);
    void rbTransplant(QueuePtr u, QueuePtr v);
    void deleteNodeHelper(QueuePtr node, int key);
    void fixInsert(QueuePtr k);
    void printRec(QueuePtr root, string indent, bool last);

public:
   
    RBTree();
    void preOrder();
    void inOrder();
    void postOrder();
    void priorityOrder();
    QueuePtr searchTree(int pri);
    QueuePtr minimum(QueuePtr node);
    QueuePtr maximum(QueuePtr node);
    QueuePtr successor(QueuePtr x);
    QueuePtr predecessor(QueuePtr x);
    void leftRotate(QueuePtr x);
    void rightRotate(QueuePtr x);
    void insert(int pri);
    QueuePtr getRoot();
    void deleteNode(int value);
    void formatPrint();
};
#endif