#include <string>
using std::string;

#ifndef TREE_H
#define TREE_H

struct Node;
typedef Node *NodePtr;
class RBTree {
    
private:

    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent);
    void preOrderHelper(NodePtr node);
    void inOrderHelper(NodePtr node);
    void postOrderHelper(NodePtr node);
    NodePtr searchTreeHelper(NodePtr node, int key);
    void fixDelete(NodePtr x);
    void rbTransplant(NodePtr u, NodePtr v);
    void deleteNodeHelper(NodePtr node, int key);
    void fixInsert(NodePtr k);
    void printRec(NodePtr root, string indent, bool last);

public:
   
    RBTree();
    void preOrder();
    void inOrder();
    void postOrder();
    void priorityOrder();
    NodePtr searchTree(int pri);
    NodePtr minimum(NodePtr node);
    NodePtr maximum(NodePtr node);
    NodePtr successor(NodePtr x);
    NodePtr predecessor(NodePtr x);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);
    void insert(int pri);
    NodePtr getRoot();
    void deleteNode(int value);
    void formatPrint();
};
#endif