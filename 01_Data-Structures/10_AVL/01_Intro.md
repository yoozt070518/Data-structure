# AVL树
BST树最核心的卖点：查找，插入，删除，都沿着一条从根岛叶的路径，每一步比较之后砍掉一整颗子树，所以代价都是O(H),H是树的高度。
当树长得很匀称的时候，h才会约等于logn

## AVL的定义与平衡因子
节点的高度：从该节点出发，到它最远叶子节点的路径上的边数。叶子节点的高度是0，空节点的高度约定为-1。这个约定不是随意的--它让“叶子节点的高度 = max(左子树高度，右子树高度)+1 = max(-1,-1)+1 = 0”这个递推公式对所有节点统一成立，包括叶子

BF的定义**BF(node) = height(node->left) - height(node->right)**

左子树高度减去右子树高度。
AVL树的不变量：对树中每一个节点,BF的绝对值小于等于1
一旦超出就要立即修正

它不允许任何一个左右子树高度差超过1，所以不可能在任何一侧疯狂生长
严格地说，可以证明一棵高度为h的树至少包含F(h+3)-1个节点，F是斐波那契数列，反推出n个节点的AVL树高度不超过约1.44log_2(n+2)。
三大操作因此有了最坏O(logn)的硬保证。

AVL只需要做局部调整即可

## 旋转

```cpp
int rotateRight(vector<TreeNode>& tree, int k2) {
    // 1. 抓取左孩子 k1
    int k1 = tree[k2].left;
    
    // 2. 转接孩子
    tree[k2].left = tree[k1].right;  // 将 k1 的右子树 Y 挂到 k2 的左边
    // 3. 根节点换人
    tree[k1].right = k2;             // 将 k2 挂到 k1 的右边
    
    /* 3. 如果有高度属性，在这里更新高度 (先算低层的 k2，再算高层的 k1)
    tree[k2].height = max(getHeight(tree, tree[k2].left),
                     getHeight(tree, tree[k2].right)) + 1;
    tree[k1].height = max(getHeight(tree, tree[k1].left),
                     getHeight(tree, tree[k1].right)) + 1;
    */

    // 4. 返回新的根节点下标，让父节点去接住它
    return k1;
}
```

## 旋转四种情况
```cpp
struct Node{
    int key;
    Node* left;
    Node* right;
    int height;// 节点高度，叶子为0

    Node(int k) : key(k), left(nullptr), right(nullptr), height(0){}
};

// 取高度，处理空指针的情况
int getHeight(Node* node){
    if(node == nullptr) return -1;// 空节点高度 -1
    return node->height;
}


// 用左右孩子的高度重新计算自己的高度
void updateHeight(Node* node){
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    node->height = max(lh, rh)+1;
}

// 算平衡因子
int getBF(Node* node){
    if(node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

```

- getHeight:
把空指针返回-1这个约定封装起来，调用者不用每次都判空
- updateHeight：
是后面最容易漏调用的函数--旋转和插入都改变了树的结构，每次改完都必须更新受影响节点的高度，漏了就会导致后续BF算错，这是AVL实现中最常见的BUG

LL:
```cpp
Node* rotateRight(Node* z){
    Node* y = z->left;
    Node* T3 = y->right;

    y->right = z;
    z->left = T3;

    updateHeight(z);// 先算孩子
    updateHeight(y);

    return y;
}
```

RR:
```cpp
Node* rotateLeft(Node* z){
    Node* y = z->right;
    Node* T2 = y->left;

    y->left = z;
    z->right = T2;

    updateHeight(z);
    updateHeight(y);

    return y;
}
```

LR:
```cpp
z-left = rotateLeft(y);// 对y左旋 拉成LL
return rotateRight(z);// 对z右旋，恢复平衡
```
实际写插入函数时不需要单独写成这样
在回溯检查BF的逻辑里，发现getBF(z) == 2
就看做孩子的BF：
getBF(z->left >= 1): 走LL(直接右旋)
getBF(z->left == -1): 走LR(先左旋再右旋)

RL:
就是LR的镜像 先右旋变成RR,再左旋恢复
```cpp
z->right = rotateRight(y);
return rotateLeft(z);
```

## 插入与再平衡的完整实现
BST的插入：
```cpp
Node* insert(Node* root, int key){
    if(root == nullptr) return new Node(key);
    if(key < root->key)
        root->left = insert(root->left, key);
    else if(key > root->key)
        root->right = insert(root->right, key);
    return root;
}
```
而AVL树的插入刚好运用到了这个回溯的过程
```cpp
Node* insert(Node* root, int key){
    if(root == nullptr) return new Node(key);
    if(key < root->key)
        root->left = insert(root->left, key);
    else if(key > root->key)
        root->right = insert(root->right, key);
    else 
        return root;

    // 回溯过程，更新当前节点的高度
    updateHeight(root);

    // 检查平衡因子，必要时旋转
    int bf = getBF(root);

    // LL
    if(bf > 1 && key < root->left->key){
        return rotateRight(root);
    }

    // RR
    if(bf < -1 && key > root->right->key)
        return rotateLeft(root);

    // LR
    if(bf > 1 && key > root->left->key){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if(bf < -1 && key < root->right->key){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
```

## 删除
BST版本的删除
```cpp
Node* findMin(Node* node){
    while(node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key){
    if(!root) return nullptr;

    if(key < root->data)
        root->left = deleteNode(root->left, key);
    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else{
        if(!root->left || !root->right){
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }else{
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }
    return root;
}
```

AVL删除的再平衡部分
```cpp
int bf = getBF(root);

if(bf > 1){
    // LL
    if(getBF(root->left) >= 0){
        return rotateRight(root);
    }else{
    // LR
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
}

if(bf < -1){
    // RR
    if(getBF(root->right) <= 0){
        return rotateLeft(root);
    }else{
    // RL
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
}
```

完整删除
```cpp
Node* findMin(Node* root){
    while(!root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key){
    if(!root) return nullptr;
    if(key < root->data) 
        root->left = deleteNode(root->left, key);
    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else{
        if(!root->left || !root->right){
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }else{
            Node* succ = findMin(root);
            root->data = succ->data;
            root->right = deleteNode(roo->right, succ->data);
        }
    }
    updateHeight(root);

    int bf = getBF(root);
    if(bf > 1){
        // LL
        if(getBF(root->left) >= 0){
            return rotateRight(root);
        }else{
        // LR
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    if(bf < -1){
        if(getBF(root->right) <= 0){
            return rotateLeft(root);
        }else{
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}