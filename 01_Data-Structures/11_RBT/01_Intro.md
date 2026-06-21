# 红黑树
## 1. 五条性质与黑高
红黑树的每个节点额外染上红或黑一种颜色，并且整棵树始终满足以下五条性质

1. 每个节点要么是红色，要么是黑色
2. 根节点是黑色
3. 每个叶子节点(NIL, 即空节点)视为黑色
4. 如果一个节点是红色，那么它的两个孩子必须是黑色
5. 从任意一个节点出发，到它子树中所有叶子(NIL)的每一条路径，经过的黑色节点数目都相同

“叶子”：红黑树在分析时，把所有空指针位置统一看成一个个黑色的NIL节点，它们是树的真正叶子。这个约定让性质5表述变得干净

红节点不能出现两个相邻的，红节点之间必须夹着黑节点

因为黑节点数相同，所以我们叫它“黑高”，记作bh(x),定义为
从节点x出发(不含x本身)到任意叶子NIL的路径上黑色节点的个数。性质5保证了这个定义是良定的--所有路径都数出同一个值，所以bh(x)不依赖你选哪条路径

设根的黑高是bh。考虑从跟到叶子的任意一条路径：
- 最短的可能路径是全部都由黑节点组成的，长度是bh
- 最长的可能路径是红黑交替的。这条路径上黑节点bh个，红节点至多bh个，总长度至多2bh

于是就有：最长路径 <= 2*最短路径。红黑树允许左右两侧不像AVL那样严丝合缝, 它松弛到"最长不超过最短的两倍" 

## 2.平衡的保证：为什么高度是O(logn)
一棵有n个内部节点的红黑树，高度h <= 2log_2(n+1)

## 3.两种调整手段：旋转与变色
```cpp
enum Color{RED, BLACK};

struct Node{
    int key;
    Color color;
    Node* left, *right, *parent;
    Node(int k): key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
};
```

### 旋转
```cpp
void rotateLeft(Node*& root, Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left) y->left->parent = x;
    y->parent = x->parent;
    if(!x->parent) root = y;
    else if(x == x->parent->left)  x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}
```
核心：
1. y接管x
2. x的右边接过继子树
3. y继承x的父亲
4. x挂到y下面
**注意：旋转过程不碰任何节点的color**
节点带着自己的颜色一起移动，颜色的调整是另一件独立的事，也就是变色

### 变色：改颜色，不改结构
变色就是把一个节点的color在RED和BLACK之间旋转，比如node->color = BLACK;
它不动任何指针，不改变树的形状，只改变一个标记
这是它和旋转最本质的区别

## 4.插入与修复
1. 插入的节点颜色必然是红，因为如果是黑的话就会出现全局的黑高问题
2. 如果插入后父亲是黑，则结束
3. 如果插入后是根节点，则染黑
4. 如果插入后父亲是红，则需要修复

修复：
1. 看叔叔是什么颜色
2. 若为红，则启动变色修复
3. 若为黑，则需要旋转加变色修复

### 4.1叔叔为红
启动变色
1. 把p改成黑
2. 把u改成黑
3. 把g改成红

### 4.2叔叔为黑
看g->p, p->z决定旋转方式
LL：
1. 直接右旋
2. 把p改成黑
3. 把g改成红

LR：
1. 对p左旋，让z替代p
2. 右旋
3. 把z改成黑
4. 把g改成红

RR:
1. 直接左旋
2. 把p改成黑
3. 把g改成红

RL：
1. 对p右旋
2. 左旋
3. 把z改成黑
4. 把g改成红

### 4.3代码实现
节点：
```cpp
enum Color{ RED, BLACK };

struct Node{
    int key;
    Color color;
    Node* left, *right, *parent;
};
```
   
在红黑树中，我们不用nullptr来代表空，而是用NIL哨兵
因为要用到空节点的color，而一直判断node != nullptr有些麻烦
因此设置nil_node节点
```cpp
Node nil_node = {0, BLACK, nullptr, nullptr, nullptr};
Node* NIL = &nil_node;
```


```cpp
void insertFixup(Node*& root, Node* z){
    while(z->parent == RED){
        Node* g = z->parent->parent;
        if(z->parent == g->left){
            Node* u = g->right;
            if(u->color == RED){
                z->parent->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                g->color = RED;
                rotateRight(root, g);
            }
        }else{
            Node* u = g->left;
            if(u->color == RED){
                z->parent->color = BLACK;
                u->color = BLACk;
                g->color = RED;
                z = g;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                g->color = RED;
                rotateLeft(root, g);
            }
        }
    }
    root->color = BLACK;
}


void insert(Node*& root, int key) {
    Node* parent = NIL;
    Node* cur    = root;
    while (cur != NIL) {
        parent = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    Node* z = new Node{ key, RED, NIL, NIL, parent };
    if      (parent == NIL)     root = z;
    else if (key < parent->key) parent->left  = z;
    else                        parent->right = z;
    insertFixup(root, z);
}
```

## 5.删除
BST删除
如果一个孩子或者没有孩子：直接让孩子顶替
如果两个孩子：要从右子树找一个最小值来顶替，然后删除那个右子树最小值

BRT删除
在BST删除的基础上加一个修复环节
由于最多只用删一个孩子的节点，因此只用盯着它的颜色就行，那个节点我们叫y

1. y是红色，那它的父亲p和孩子x都是黑，接上p和x之后不会有任何问题，直接成立
2. y如果是黑的，就会触发黑高失衡，出现亏空
3. 关键一招：y蒸发掉的那个黑，我们不让其凭空消失，而是记到顶替者x头上
   1. 如果x本来就是红，则只需要将红改为黑就能吸收掉这个额外的黑
   2. 如果x是黑，就会出现双黑的现象
        1. 如果兄弟**w和两个孩子都是黑**，此时w的手下没有富足的红，无能为力，只能靠自己也染红来做到同时减一缓解这个黑高压力，又因为此时的黑高还是不平衡，所以需要父亲加一份黑
           1. 如果父亲为红，直接染黑结束
           2. 如果父亲是黑，继续上述操作
        2. 如果**w黑，而且远侄是红的**(近侄是红是黑都不影响这招)。w手下有富裕的红，可以直接借给x，只需通过对p左旋一次(x在左)。左旋之后要经过变色
           1. 将p染黑，填补双黑的空缺，使其正常
           2. 让w继承p的颜色，使整体的颜色，黑高不变
           3. 将远侄从红染黑，填补原来的黑高
        3. 兄弟**w是红**。w红，那它的**孩子必然是黑**，它的**父亲必然是黑**。此时只需要对p进行一次左旋，就能将近侄转接成x的黑兄弟。此时情形就变成了双黑加黑兄弟了
        4. **w黑但是红的是近侄，远侄是黑**--之前需要远侄去填洞，这里远侄偏偏是黑的，红跑到近侄那边，不好处理。解决办法就是对w右旋(注意这次转的是w不是p)，并交换w和近侄的颜色：近侄染黑，w染红

总结：
- 情形一(w红)：旋转+变色，归约成"w黑"的局面(顺带把p染红)，同一轮接着往下走
- 情形二(双侄黑)->染色，双黑上移给p
- 情形三(近侄红)->旋转+变色，规约成情形四
- 情形四(远侄红)->旋转+变色，终止

### 5.1代码实现
删除 = BST删除 + 必要时修复
```cpp
void deleteNode(Node*& root, int key){
    Node* z = root;
    while(z != NIL){
        z = (z->key < key) ? z->left : z->right;
    }
    if(z == NIL) return;
}
```
```cpp
// 让v去顶替u的位置
void transplant(Node*& root, Node* u, Node* v){
    if(u->parent == NIL) root = v;
    if(u == u->parent->left) u->parent->left = v;
    else  u->parent->right = v;
    v->parent = u->parent;
}
```
```cpp
    if(z->left == NIL) transplant(root, z, z->right);
    else if(z->right == NIL) transplant(root, z, z->left);
    else{
        // 有两个孩子，单独考虑
    }
```
```cpp
Node* minimum(Node* x){
    while(x->left != NIL) x=x->left;
    return x;
}
```
```cpp
else{
    // 两个孩子
    Node* y =  minimum(z->right);
    Node* x = y->right;
    if(y->parent == z){
        x->parent = y;
    }else{
        transplant(root, y, y->right);
        y->right = z->right;
        y->right->parent = y;
    }   
    transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
}
```
特例：y恰好就是z的直接右孩子。
