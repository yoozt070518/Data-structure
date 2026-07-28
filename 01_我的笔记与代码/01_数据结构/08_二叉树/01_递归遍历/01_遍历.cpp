#include <iostream>
using namespace std;
template <typename T>
struct TreeNode {
    T data;                 // 数据域
    TreeNode<T>* left;      // 左孩子指针
    TreeNode<T>* right;     // 右孩子指针

    // 严谨的构造函数：现代 C++ 必须显式初始化指针为 nullptr，防范野指针
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root; // 树的根节点

    // 私有递归辅助函数：用于销毁以 node 为根的子树
    void clear(TreeNode<T>* node) {
        if (node == nullptr) {
            return; // 递归基（Base Case）：空节点不需要释放
        }

        // 1. 递归释放左子树
        clear(node->left);
        
        // 2. 递归释放右子树
        clear(node->right);

        // 3. 左右子树都安全释放了，此时释放当前节点
        // std::cout << "Debug: 正在释放节点 " << node->data << std::endl; // 方便你 Debug 观察
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    // 析构函数：对外接口，内部调用递归销毁
    ~BinaryTree() {
        clear(root);
        root = nullptr; // 彻底置空，防止二次析构
    }

    // 临时提供一个手动构建树的方法，供后续测试遍历使用
    void setRoot(TreeNode<T>* node) {
        root = node;
    }
};

template <typename T>
// 1. 前序遍历（根 -> 左 -> 右）
void preOrder(TreeNode<T>* node) {
    if (node == nullptr) return; // 递归基

    std::cout << node->data << " "; // 【位置 ①】刚到达节点，先处理
    preOrder(node->left);           // 深入左子树
    preOrder(node->right);          // 深入右子树
}

template <typename T>
// 2. 中序遍历（左 -> 根 -> 右）
void inOrder(TreeNode<T>* node) {
    if (node == nullptr) return;

    inOrder(node->left);            // 先把左边全部处理完
    std::cout << node->data << " "; // 【位置 ②】从左边回来，处理当前节点
    inOrder(node->right);           // 再去处理右边
}

template <typename T>
// 3. 后序遍历（左 -> 右 -> 根）
void postOrder(TreeNode<T>* node) {
    if (node == nullptr) return;

    postOrder(node->left);          // 先把左边搞定
    postOrder(node->right);         // 再把右边搞定
    std::cout << node->data << " "; // 【位置 ③】左右都安全了，最后处理自己
}