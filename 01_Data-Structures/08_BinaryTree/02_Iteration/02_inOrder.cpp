#include <stack>
#include <iostream>
using namespace std;

template<typename T>
struct TreeNode
{
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val):data(val), left(nullptr), right(nullptr){}
};

template <typename T>
void inOrder(TreeNode<T>* root){
    stack<TreeNode<T>*> myStack;
    TreeNode<T>* curr = node;
    while(curr != nullptr || !myStack.empty()){
        if(curr->left != nullptr){
            myStack.push(curr->left);
            curr = curr->left;
        }else{
            curr = myStack.top();
            myStack.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
}
