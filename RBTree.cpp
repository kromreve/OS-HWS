//Red Black Tree
//Jacob Weber
#include "RBTree.h"
#include <iostream>
#include <string>
using namespace std;


struct Node {
    int pid; //id of process
    int burst; //burst
    int arrivalValue;
    int priority; // priority: used as key
    int deadlineValue; // deadline
    int ioValue; //io
    int age; 
    int basePriority;
    Node *parent; // parent pointer
    Node *left; // left child pointer
    Node *right; // right child pointer
    int color; // will be set to red (1) or black (0)
};

    void RBTree::createEmptyNode(NodePtr node, NodePtr parent) {
        node->priority = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void RBTree::preOrderRec(NodePtr node) {
        if (node != TNULL) {
            cout << node->priority << " ";
            preOrderRec(node->left);
            preOrderRec(node->right);
        }
    }

    void RBTree::inOrderRec(NodePtr node) {
        if (node != TNULL) {
            inOrderRec(node->left);
            cout << node->priority << " ";
            inOrderRec(node->right);
        }
    }

    void RBTree::postOrderRec(NodePtr node) {
        if (node != TNULL) {
            postOrderRec(node->left);
            postOrderRec(node->right);
            cout << node->priority << " ";
        }
    }

    NodePtr RBTree::priorityOrderRec(NodePtr node) {
        if (node != TNULL) {
            priorityOrderRec(node->right);
            return node;
            priorityOrderRec(node->left);
        }
        return NULL;
    }

    NodePtr RBTree::searchTreeRec(NodePtr node, int id) {
        
        //cout << "Node: " << node << endl;
        //cout << "TNULL: " << TNULL << endl;
        if (node != TNULL && !found) {
            //cout << "node pid: " << node->pid << endl;
            //cout << "inputted id: " << id << endl;
            if (node->pid == id) {
                found = true;
                //cout << "found " << id << endl;
                queriedNode = node;
                return node;
            }
            searchTreeRec(node->left, id);
            searchTreeRec(node->right, id);
        } else {
            // cout << "going up.." << endl;
            // cout << "node pid (searchTreeRec): " << queriedNode->pid << endl;
            return queriedNode;
        }
        return NULL;
    }

    // NotePtr RBTree::getLeftmostRec(NodePtr node) {
    //     if (node != TNULL) {
    //         getLeftmostRec(node->left);
    //     }
    // }

    void RBTree::delUpdate(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if  (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void RBTree::redBlackTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void RBTree::deleteNodeRec(NodePtr node) {
        //NodePtr z = TNULL;
        cout << "pid is: " << node->pid << endl;
        NodePtr z = node;
        NodePtr x, y;

        int count = 0;
        // while (node != TNULL) {
        //     if (node->priority == pri && node->pid == id) {
        //         z = node;
        //     }

        //     if (node->priority <= pri) {
        //         node = node->right;
        //     } else {
        //         node = node->left;
        //     }
        // }
        count++;
        cout << "z is: " << z << ". iterated " << count << " times." << endl;
        cout << "TNULL: " << TNULL << endl;
        if (z == TNULL) {
            cout<<"No key found"<<endl;
            return;
        }

        y = z;
        int y_og_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            redBlackTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            redBlackTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_og_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                redBlackTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            redBlackTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_og_color == 0){
            delUpdate(x);
        }
    }

    void RBTree::fixInsert(NodePtr k) {
        NodePtr u; //uncle node
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }

                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; //uncle node

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }

                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void RBTree::printRec(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout<<indent;
            if (last) {
                cout<<"R----";
                indent += "     ";
            } else {
                cout<<"L----";
                indent += "|    ";
            }

            string sColor = root->color?"RED":"BLACK";
            cout<<root->priority<<"("<<sColor<<")"<<root->pid<<endl;
            printRec(root->left, indent, false);
            printRec(root->right, indent, true);
        }

    }

    RBTree::RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        cout << "TNULL (constructor): " << TNULL << endl;
    }

    void RBTree::preOrder() {
        preOrderRec(this->root);
    }

    void RBTree::inOrder() {
        inOrderRec(this->root);
    }

    void RBTree::postOrder() {
        postOrderRec(this->root);
    }

    NodePtr RBTree::priorityOrder() {
        return priorityOrderRec(this->root);
    }

    NodePtr RBTree::searchTree(int id) {
        found = false;
        return searchTreeRec(this->root, id);
    }

    NodePtr RBTree::minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr RBTree::maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr RBTree::successor(NodePtr x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr RBTree::predecessor(NodePtr x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void RBTree::leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void RBTree::rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    int * RBTree::exportProcess(NodePtr node) {
        static int pList[6] = {
            node->pid, 
            node->burst,
            node->arrivalValue,
            node->priority,
            node->deadlineValue,
            node->ioValue
        };
        return pList;
    }

    void RBTree::insert(int id, int bst, int avl, int pri, int dln, int io) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->pid = id;
        node->burst = bst;
        node->arrivalValue = avl;
        node->priority = pri;
        node->deadlineValue = dln;
        node->ioValue = io;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; //new node will be red

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->priority < x->priority) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->priority < y->priority) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    NodePtr RBTree::getRoot() {
        return this->root;
    }

    void RBTree::deleteNode(NodePtr node) {
        deleteNodeRec(node);
    }

    void RBTree::formatPrint() {
        cout<<"RBTree:"<<endl;
        if (root) {
            printRec(this->root, "", true);
        }
    }