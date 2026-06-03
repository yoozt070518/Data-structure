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

template<typename T>
void postOrder(TreeNode<T>* root){
    stack<TreeNode<T>*> myStack1;
    stack<TreeNode<T>*> myStack2;
    myStack1.push(root);
    while(!myStack1.empty()){
        TreeNode<T>* curr = myStack1.top();
        myStack2.push(curr);
        myStack1.pop();
        if(curr->right != nullptr){
            myStack1.push(curr->right);
        }

        if(curr->left != nullptr){
            myStack1.push(curr->left);
        }
    }
    while(!s2.empty()){
        cout << myStack2.top()->data << " ";
        myStack2.pop()
    }
}

template<typename T>
void postOrder2(TreeNode<T>* root){
    stack<TreeNode<T>*> myStack;
    TreeNode<T>* curr = root;
    TreeNode<T>* prev = nullptr;
    while(curr != nullptr || !myStack.empty()){
        if(curr != nullptr){
            myStack.push(curr);
            curr = curr->left;
        }else{
            TreeNode<T>* topNode = myStack.top();
            if(topNode->right != nullptr && topNode->right != prev){
                curr = topNode->right;
            }else{
                myStack.pop();
                cout << topNode->data << " ";
                prev = topNode;
                curr = nullptr;
            }
        }
    }
}