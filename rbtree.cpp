//Red Black Tree
//Jacob Weber
#include <iostream>
using namespace std;


struct Node {
    int value; // holds key
    Node *parent; // parent pointer
    Node *left; // left child pointer
    Node *right; // right child pointer
    int color; // will be set to red (1) or black (0)
};

typedef Node *NodePtr;

class RedBlackTree {
    private:
        NodePtr root;
        NodePtr TNULL;

        void createEmptyNode(NodePtr node, NodePtr parent) {
            node->value = 0;
            node->parent = parent;
            node->left = nullptr;
            node->right = nullptr;
            node->color = 0;
        }

        void preOrderRec(NodePtr node) {
            if (node != TNULL) {
                cout << node->value << " ";
                preOrderRec(node->left);
                preOrderRec(node->right);
            }
        }

        void inOrderRec(NodePtr node) {
            if (node != TNULL) {
                inOrderRec(node->left);
                cout << node->value << " ";
                inOrderRec(node->right);
            }
        }

        void postOrderRec(NodePtr node) {
            if (node != TNULL) {
                postOrderRec(node->left);
                postOrderRec(node->right);
                cout << node->value << " ";
            }
        }

        NodePtr searchTreeRec(NodePtr node, int key) {
            if (node == TNULL || key == node->value) {
                return node;
            }

            if (key < node->value) {
                return searchTreeRec(node->left, key);
            }
            return searchTreeRec(node->right, key);
        }

    void delUpdate(NodePtr x) {
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

    void redBlackTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeRec(NodePtr node, int key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->value == key) {
                z = node;
            }

            if (node->value <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

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

    void fixInsert(NodePtr k) {
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

    void printRec(NodePtr root, string indent, bool last) {
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
            cout<<root->value<<"("<<sColor<<")"<<endl;
            printRec(root->left, indent, false);
            printRec(root->right, indent, true);
        }
        
    }

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preOrder() {
        preOrderRec(this->root);
    }

    void inOrder() {
        inOrderRec(this->root);
    }

    void postOrder() {
        postOrderRec(this->root);
    }

    NodePtr searchTree(int k) {
        return searchTreeRec(this->root, k);
    }

    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x) {
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

    NodePtr predecessor(NodePtr x) {
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

    void leftRotate(NodePtr x) {
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

    void rightRotate(NodePtr x) {
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

    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->value = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; //new node will be red

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->value < x->value) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->value < y->value) {
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

    NodePtr getRoot() {
        return this->root;
    }

    void deleteNode(int value) {
        deleteNodeRec(this->root, value);
    }

    void formatPrint() {
        cout<<"RBTree:"<<endl;
        if (root) {
            printRec(this->root, "", true);
        }
    }



};

int main() {
    RedBlackTree bt;
    bt.insert(8);
	bt.insert(18);
	bt.insert(5);
	bt.insert(15);
	bt.insert(17);
	bt.insert(25);
	bt.insert(40);
	bt.insert(80);
	bt.deleteNode(25);
    bt.formatPrint();
    bt.preOrder();
    return 0;
}