#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Color{ RED, BLACK };

struct Node{
    int key;
    Color color;
    Node* left, *right, *parent;
};

Node nil_node = { 0 , BLACK, nullptr, nullptr, nullptr };
Node* NIL = &nil_node;

void transplant(Node*& root, Node* u, Node* v){
    v->parent = u->parent;
    if(u->parent == NIL) root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
}

void rotateRight(Node*& root, Node* z){
    Node* y = z->left;
    z->left = y->right;
    if(y->right != NIL) y->right->parent = z;
    transplant(root, z, y);
    y->right = z;
    z->parent = y;
}

void rotateLeft(Node*& root, Node* z){
    Node* y = z->right;
    z->right  = y->left;
    if(y->left != NIL) y->left->parent = z;
    transplant(root, z, y);
    y->left = z;
    z->parent = y;
}

Node* minimum(Node* x){
    while(x->left != NIL){
        x = x->left;
    }
    return x;
}

void deleteFixup(Node*& root, Node* x){
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            Node* w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = root;
            }
        }else{
            Node* w = x->parent->left;
            if(w->color == RED){
                x->parent->color = RED;
                w->color = BLACK;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if(w->left->color == BLACK){
                    w->color  = RED;
                    w->right->color = BLACK;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                w->left->color = BLACK;
                x->parent->color = BLACK;
                rotateRight(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}





void deleteNode(Node*& root, int key){
    Node* z = root;
    while(z != NIL && z->key != key){
        z = (key < z->key) ? z->left : z->right;
    }
    if(z == NIL) return;

    Node* y = z;
    Color yOringinalColor = y->color;
    Node* x;

    if(z->left == NIL){
        x = z->right;
        transplant(root, z, z->right);
    }else if(z->right == NIL){
        x = z->left;
        transplant(root, z, z->left);
    }else{
        y = minimum(z->right);
        yOringinalColor = y->color;
        x = y->right;
        if(z == y->parent){
            x->parent = y;
        }else{
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOringinalColor == BLACK) deleteFixup(root, x);
}

int checkRBT(Node* node, Node*& prev){
    if(node == NIL) return 1;

    if(node->color == RED){
        if(node->left->color == RED || node->right->color == RED){
            return -1;
        }
    }

    int lh = checkRBT(node->left, prev);
    if(lh == -1) return -1;

    if(prev != NIL && prev->key >= node->key){
        return -1;
    }
    prev = node;

    int rh = checkRBT(node->right, prev);
    if(rh == -1) return -1;
    if(lh != rh){
        return -1;
    }
    return (node->color == RED) ? lh : lh+1;
}

bool isRBT(Node* root){
    if(root == NIL) return true;
    if(root->color == RED) return false;
    Node* prev = NIL;
    if(checkRBT(root, prev) == -1){
        return false;
    }else{
        return true;
    }
}
int main(){
    return 0;
}