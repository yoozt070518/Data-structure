#include <iostream>
#include <stack>
using namespace std;

template<typename T>
struct TreeNode {
    T data;                 // 数据域
    TreeNode<T>* left;      // 左孩子指针
    TreeNode<T>* right;     // 右孩子指针

    // 严谨的构造函数：现代 C++ 必须显式初始化指针为 nullptr，防范野指针
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
void preOrderIteration(TreeNode<T>* root) {
    if (root == nullptr) return; // 空树直接返回

    // 1. 自己定义一个栈，用来代替系统的函数调用栈
    std::stack<TreeNode<T>*> myStack;
    
    // 先把根节点请进去
    myStack.push(root);

    // 2. 开启迭代循环
    while (!myStack.empty()) {
        // 弹出当前栈顶的节点
        TreeNode<T>* curr = myStack.top();
        myStack.pop();

        // 打印当前节点（前序：根）
        std::cout << curr->data << " ";

        // 3. 关键：先压右，再压左！
        if (curr->right != nullptr) {
            myStack.push(curr->right);
        }
        if (curr->left != nullptr) {
            myStack.push(curr->left);
        }
    }
}
int main(){
    return 0;
}