#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Color{ RED, BLACK };



struct Node{
    int key;
    Color color;
    Node *left, *right, *parent;
};

Node nil_node = {0, BLACK, nullptr, nullptr, nullptr};
Node* NIL = &nil_node;

void rotateLeft(Node*& root, Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NIL) root = y;
    else if(x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node*& root, Node* x){
    Node* y = x->left;
    x->left = y->right;
    if(y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == NIL) root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(Node*& root, Node* z){
    while(z->parent->color == RED){
        Node* g = z->parent->parent;
        if(z->parent == g->left){
            // 叔叔在右
            Node* u = g->right;
            if(u->color == RED){
                // 叔为红
                z->parent->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }else{
                // 叔为黑
                if(z == z->parent->right){
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                g->color = RED;
                rotateRight(root, g);
            }
        }else{
            // 叔叔在左
            Node* u = g->left;
            if(u->color == RED){
                z->parent->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                g->color  = RED;
                rotateLeft(root, g);
            }
        }
    }
    root->color = BLACK;
}


void insert(Node*& root, int key){
    Node* parent = NIL;
    Node* cur = root;
    while(cur != NIL){
        parent = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    Node* z = new Node{key, RED, NIL,NIL, parent};
    if(parent == NIL) root = z;
    else if(key < parent->key) parent->left = z;
    else parent->right = z;
    insertFixup(root, z);
}
