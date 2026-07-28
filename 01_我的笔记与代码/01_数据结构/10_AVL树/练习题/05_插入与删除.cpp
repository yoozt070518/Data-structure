#include <iostream>
using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int x): key(x), left(nullptr), right(nullptr), height(0){}
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
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
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






Node* insert(Node* node, int key){
    if(!node) return new Node(key);
    if(key < node->key)
        node->left = insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    
    updateHeight(node);

    int bf = getBF(node);

    // LL
    if(bf > 1 && key < node->left->key){
        return rotateRight(node);
    }
    // LR
    if(bf > 1 && key > node->left->key){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RR
    if(bf < -1 && key > node->right->key){
        return rotateLeft(node);
    }
    // RL
    if(bf < -1 && key < node->right->key){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* deleteNode(Node* node, int key){
    if(!node) return nullptr;
    if(key < node->key)
        node->left = deleteNode(node->left, key);
    else if(key > node->key)
        node->right = deleteNode(node->right, key);
    else{
        if(!node->left || !node->right){
            Node* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }else{
            Node* succ = node->right;
            while(succ->left){
                succ = succ->left;
            }
            node->key = succ->key;
            node->right = deleteNode(node->right, succ->key);
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

void preOrder(Node* node, bool& first){
    if(!node) return;
    if(!first) cout << " ";
    cout << node->key;
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
        Node* root = nullptr;
        int n;
        int m;
        cin >> n;
        for(int i = 0;i<n;++i){
            int key;
            cin >> key;
            root = insert(root, key);
        }
        cin >> m;
        for(int i = 0;i<m;++i){
            int key;
            cin >> key;
            root = deleteNode(root, key);
        }
        bool first = true;
        preOrder(root, first);
        cout << endl;
        freeTree(root);
    }
    return 0;
}