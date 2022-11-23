#include <string>
using std::string;

#ifndef TREE_H
#define TREE_H

struct Node;
typedef Node* NodePtr;

class RBTree {

private:

    NodePtr root;
    
    bool found = false;
    

    void createEmptyNode(NodePtr node, NodePtr parent);
    void preOrderRec(NodePtr node);
    void inOrderRec(NodePtr node);
    void postOrderRec(NodePtr node);
    NodePtr priorityOrderRec(NodePtr node);
    NodePtr searchTreeRec(NodePtr node, int id);
    NodePtr getLeftmostRec(NodePtr node);
    void delUpdate(NodePtr x);
    void redBlackTransplant(NodePtr u, NodePtr v);
    void deleteNodeRec(NodePtr node);
    void fixInsert(NodePtr k);
    void printRec(NodePtr root, string indent, bool last);

public:

    NodePtr queriedNode = nullptr;
    NodePtr TNULL;

    RBTree();
    void preOrder();
    void inOrder();
    void postOrder();
    NodePtr priorityOrder();
    NodePtr searchTree(int k);
    NodePtr minimum(NodePtr node);
    NodePtr maximum(NodePtr node);
    NodePtr successor(NodePtr x);
    NodePtr predecessor(NodePtr x);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);
    int returnPid(NodePtr node);
    int returnBurst(NodePtr node);
    int returnArrival(NodePtr node);
    int returnPriority(NodePtr node);
    int returnBasePriority(NodePtr node);
    int returnDeadline(NodePtr node);
    int returnIo(NodePtr node);
    int * exportProcess(NodePtr node);
    void insert(int id, int bst, int avl, int pri, int dln, int io);
    void printProcess(NodePtr node);
    NodePtr getRoot();
    void deleteNode(NodePtr node);
    void formatPrint();
};
#endif
