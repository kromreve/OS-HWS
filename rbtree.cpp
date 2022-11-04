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
                cout << node->value << " ";
                inOrderRec(node->left);
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

        NodePtr returnNode(NodePtr node, int key) {
            if (node == TNULL || key == node->value) {
                return node;
            }

            if (key < node->value) {
                return returnNode(node->left, key);
            }
            return returnNode(node->right, key);
        }


        
};