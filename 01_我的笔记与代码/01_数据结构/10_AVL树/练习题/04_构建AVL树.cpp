#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val):data(val), left(nullptr), right(nullptr), height(0){}
};

int getHeight(Node* node){
    if(!node) return -1;
    return node->height;
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



Node* insert(Node* root, int val){
    if(!root) return new Node(val);
    if(val < root->data)
        root->left = insert(root->left, val);
    else if(val > root->data)
        root->right = insert(root->right, val);
    else
        return root;
    
    updateHeight(root);

    int bf = getBF(root);

    // LL
    if(bf > 1 && val < root->left->data)
        return rotateRight(root);
    // RR
    if(bf < -1 && val > root->right->data)
        return rotateLeft(root);
    
    // LR
    if(bf > 1 && val > root->left->data){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if(bf < -1 && val < root->right->data){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;  
}

void preOrder(Node* node, bool& first){
    if(!node) return;
    if(!first) cout << " ";
    cout << node->data;
    first = false;
    preOrder(node->left, first);
    preOrder(node->right, first);
}

void freeTree(Node* node){
    if(!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}



int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        Node* root = nullptr;
        for(int i = 0;i<n;++i){
            int key;
            cin >> key;
            root = insert(root, key);
        }
        bool first = true;
        preOrder(root, first);
        cout << endl;

        freeTree(root);
    }

    return 0;
}