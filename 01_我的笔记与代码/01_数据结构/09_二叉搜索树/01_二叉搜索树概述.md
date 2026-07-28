# 二叉树
## 1.核心性质与数学性质
### 1.1BST树的严格定义
对于树中的任意一个节点X：
1. 它的**左子树中的所有节点**的值，都必须严格小于X的值
2. 它的**右子树中的所有节点**的值，都必须严格大于X的值
3. 它的左右子树也必须各自是一棵二叉搜索树


### 1.2中序遍历的“天然后续性”
中序遍历：左子树 -> 根节点 -> 右子树
代入BST的定义：因为左子树 < 根节点的值 < 右子树的值
所以当你用中序遍历去扫描一颗标准的BST时，计算机吐出来的序列必然是一个严格单调递增的有序数组

在工程中，如果你手写一棵BST，想肉眼检测它的逻辑对不对，最快的银弹就是直接调一次它的inOrder()。如果输出的数据哪怕有一个数顺序颠倒了，说明你的树结构已经写塌了


### 1.3时间复杂度
在理想形态下(树长得比较匀称，左右平衡)，BST的查找和插入效率是极其优雅的O(logn)
因为你每往下走一步，通过和当前节点data做一次大小比对，就能直接砍掉一整棵左子树或者右子树。

- **树的退化**
但是，BST没有自我约束平衡的能力
如果数据比较偏执，就会退化成单链表，时间复杂度退化成O(n)

## 2.查找和插入的底层实现
### 2.1递归实现
1. 查找
```cpp
bool find(TreeNode<T>* node, const T& target){
    if(node == nullptr) return false;
    if(node->data == target) return true;
    if(target < node->data) {
        return find(node->left, target);
    }else{
        return find(node->right, target);
    }
}
```

2. 插入
```cpp
TreeNode<T>* insert(TreeNode<T>* node, const T& val){
    if(node == nullptr) return new TreeNode<T>(val);
    if(val < node->data) node->left = insert(node->left,val);
    if(val > node->data) node->right = insert(node->right,val);
    return node;
}
```

### 2.2迭代实现
1. 查找
```cpp
bool find(TreeNode<T>* root, const T& target){
    TreeNode<T>* curr = root;
    while(curr != nullptr){
        if(target < curr->data){
            curr = curr->left;
        }
        else if(target == curr->data){
            return true;
        }
        else{
            curr = curr->right;
        }
    }
    return false;
}
```
2. 插入
```cpp
void insert(TreeNode<T>*& root, const T& val){
    if(root == nullptr) root = new TreeNode<T>(val);
    TreeNode<T>* curr = root;
    TreeNode<T>* prev = nullptr;
    while(curr != nullptr){
        prev = curr;
        if(val == curr->data) return;
        else if(val < curr->data){   
            curr = curr->left;
        }else{
            curr = curr->right;
        }
    }
    if(val < prev->data){
        prev->left = new TreeNode<T>(val);
    }else{
        prev->right = new TreeNode<T>(val);
    }
}
```
## 3.节点删除
方法可以由节点类型分为三种
1. 被删节点是叶子节点
- 1. 找到这个节点
- 2. 看一眼它的父亲，如果是父亲的左孩子，就把父亲的left置为nullptr
- 3. delete掉这个节点
- 特殊边界：如果整棵树就它一个根节点，删除完之后直接把root_置为nullptr

2. 被删节点只有一个孩子
- 让它的父亲(爷爷)越过它，直接越级牵住它的独生子(孙子)
- 1. 如果被删节点是父亲的左孩子，那就把它的独生子过继给父亲的left
- 2. 如果被删节点是父亲的右孩子，那就把它的独生子过继给父亲的right
- 3. 过继完毕后，delete当前节点
- 特殊边界：如果要删除的是根节点，且根节点只有一个孩子，那么直接让这个唯一的孩子登基成为新的root_即可

3. 被删节点有两个孩子
核心思想：我们不真正去销毁这个度为2的节点。我们去树里找一个完美替罪羊，把替罪羊身上的data复制到当前节点上，覆盖掉那个原本要被删除的值。随后，我们专区把那只可怜的替罪羊给删掉

**谁有资格当这个替罪羊**
要替代当前节点，替换之后还必须满足左小右大的顺序。能在整棵树里无缝顶替它的，只有两个人
1. 左子树的最大值
2. 右子树的最小值

**为什么这样能破局**
以右子树的最小值为例
1. **怎么找？** 
    - 先向右迈一步(进入右子树curr = curr->right)
    - 然后一路向左狂奔到底(while(curr->left != nullptr) curr = curr->left)
    - 撞墙时的那个节点，就是右子树的最小值

2. **它的物理形态是怎么样的？**
    - 既然它已经是那个最小值了，说明它绝对不会再有左孩子了，它要么是个叶子，要么只有一个右孩子

3. **乾坤大挪移**
    - 我们把这个替罪羊的data复制给那个原本要被删的度为2的节点
    - 此时，删除的目标就转移成了“删除那只替罪羊”
    - 此时删除就退化成了情况一或者情况二

### 递归删除
```cpp
template<typename T>
TreeNode<T>* remove(TreeNode<T>* node, const T& val){
    if(node == nullptr) return nullptr;
    if(val < node->data){
        node->left = remove(node->left, val);
    }else if(val > node->data){
        node->right = remove(node->right, val);
    }else{
        if(node->right == nullptr){
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }else if(node->left == nullptr){
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        }else{
            TreeNode<T>* minNode = node->right;
            while(minNode->left != nullptr){
                minNode = minNode->left;
            }
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }
    }
    return node;
}
```

### 迭代删除
```cpp
template<typename T>
void remove(TreeNode<T>* node, int val){
    TreeNode<T>* curr = root;
    TreeNode<T>* prarent = nullptr;
    // 1. 双指针确定目标
    while(curr != nullptr && curr->data != val){
        parent = curr;
        if(val < curr->data){
            curr = curr->left;
        }else{
            curr = curr->right;
        }
    }
    // 没找到 返回
    if(curr == nullptr) return;

    // 2.处理双孩子形态
    if(curr->left != nullptr && curr->right != nullptr){
        // 寻找右子树最小值
        TreeNode<T>* minParent = curr;
        TreeNode<T>* min = curr->right;
        while(min->left != nullptr){
            minParent = min;
            min = min->left;
        }

        // 覆盖原值
        curr->data = min->data;

        // 把要删除的指针直接移向替罪羊
        parent = minParent;
        curr = min;
    }

    // 3. 统一处理单孩子或者叶子
    // 记录唯一的孩子(没有的话就直接记录为nullptr)
    TreeNode<T>* child = (curr->left != nullptr) ? curr->left : curr->right;

    // 爷爷和孙子牵线
    if(parent == nullptr){
        root == child;// 删的是根节点，孩子直接继承大业
    }else if(parent->left == curr){
        parent->left = child;
    }else{
        parent->right = child;
    }

    delete curr;
}
```
