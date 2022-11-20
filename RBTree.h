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

    void createEmptyNode(NodePtr node, NodePtr parent);
    void preOrderRec(NodePtr node);
    void inOrderRec(NodePtr node);
    void postOrderRec(NodePtr node);
    NodePtr priorityOrderRec(NodePtr node);
    NodePtr searchTreeRec(NodePtr node, int id);
    void delUpdate(NodePtr x);
    void redBlackTransplant(NodePtr u, NodePtr v);
    void deleteNodeRec(NodePtr node, int id);
    void fixInsert(NodePtr k);
    void printRec(NodePtr root, string indent, bool last);

public:

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
    NodePtr getTopNode();
    int * exportProcess(NodePtr node);
    void insert(int id, int bst, int avl, int pri, int dln, int io);
    NodePtr getRoot();
    void deleteNode(int id);
    void formatPrint();
};
#endif
