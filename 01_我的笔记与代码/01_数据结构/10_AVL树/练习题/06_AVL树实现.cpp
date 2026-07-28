#include <iostream>
using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
    int height;

    Node(int x): val(x), left(nullptr), right(nullptr), height(0){}
};

int getHeight(Node* node){
    return node ? node->height : -1;
}

int getBF(Node* node){
    if(!node) return 0;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    return lh - rh;
}

void updateHeight(Node* node){
    if(!node) return;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    node->height = max(lh, rh) + 1;
}

Node* rotateRight(Node* z){
    Node* y = z->left;
    Node* T3 = y->right;

    y->right = z;
    z->left = T3;

    updateHeight(z);
    updateHeight(y);

    return y;
}

Node* rotateLeft(Node* z){
    Node* y = z->right;
    Node* T2 = y->left;

    y->left = z;
    z->right = T2;

    updateHeight(z);
    updateHeight(y);

    return y;
}

Node* insert(Node* node, int val){
    if(!node) return new Node(val);
    if(val < node->val){
        node->left = insert(node->left, val);
    }else if(val > node->val){
        node->right = insert(node->right,val);
    }else{
        return node;
    }

    updateHeight(node);
    int bf = getBF(node);
    if(bf > 1 && val < node->left->val){
        return rotateRight(node);
    }
    if(bf > 1 && val > node->left->val){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if(bf < -1 && val > node->right->val){
        return rotateLeft(node);
    }
    if(bf < -1 && val < node->right->val){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* deleteNode(Node* node, int val){
    if(!node) return nullptr;
    if(val < node->val){
        node->left = deleteNode(node->left,val);
    }else if(val > node->val){
        node->right = deleteNode(node->right, val);
    }else{
        if(!node->left || !node->right){
            Node* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }else{
            Node* succ = node->right;
            while(succ->left){
                succ = succ->left;
            }
            node->val = succ->val;
            node->right = deleteNode(node->right, succ->val);
        }
    }

    updateHeight(node);
    int bf = getBF(node);
    if(bf > 1){
        if(getBF(node->left) >= 0){
            return rotateRight(node);
        }else{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(bf < -1){
        if(getBF(node->right) <= 0){
            return rotateLeft(node);
        }else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}

void lower_bound(Node* node , Node*& prev ,int val){
    while(node){
        if(val > node->val){
            prev = node;
            node = node->right;
        }else{
            node = node->left;
        }
    }
}

void upper_bound(Node* node, Node*& upper, int val){
    while(node){
        if(val < node->val){
            upper = node;
            node = node->left;
        }else{
            node = node->right;
        }
    }
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    Node* root = nullptr;
    while(q--){
        int op, x;
        cin >> op >> x;
        if(op == 1){
            root = insert(root, x);
        }else if(op == 2){
            root = deleteNode(root, x);
        }else if(op == 3){
            Node* prev = nullptr;
            lower_bound(root,prev,x);
            if(prev){
                cout << prev->val << "\n";
            }else{
                cout << "none" << "\n";
            }
        }else{
            Node* upper = nullptr;
            upper_bound(root, upper, x);
            if(upper){
                cout << upper->val << "\n";
            }else{
                cout << "none" << "\n";
            }
        }
    }




    return 0;
}