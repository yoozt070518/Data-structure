#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct TreeNode
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    
    TreeNode(const T& val): data(val), left(nullptr), right(nullptr){}
};

template <typename T>
class BinaryTree{
private:
    TreeNode<T>* root_;
    void clear(TreeNode<T>* node){
        if(node == nullptr){
            return;
        }
        if(node->left != nullptr) clear(node->left);
        if(node->right != nullptr) clear(node->right);
        delete node;
    }

    void preOrder1(TreeNode<T>* node){
        if(node == nullptr) return;
        cout << node->data << " ";
        if(node->left != nullptr) preOrder1(node->left);
        if(node->right != nullptr) preOrder1(node->right);
    }

    void inOrder1(TreeNode<T>* node){
        if(node == nullptr) return;
        if(node->left != nullptr) inOrder1(node->left);
        cout << node->data << " ";
        if(node->right != nullptr) inOrder1(node->right);
    }

    void postOrder1(TreeNode<T>* node){
        if(node == nullptr) return;
        if(node->left != nullptr) postOrder1(node->left);
        
        if(node->right != nullptr) postOrder1(node->right);
        cout << node->data << " ";
    }
public:
    BinaryTree(): root_(nullptr){}
    ~BinaryTree(){
        clear(root_);
    }

    void preOrder1(){
        preOrder1(root_);
    }

    void inOrder1(){
        inOrder1(root_);
    }

    void postOrder1(){
        postOrder1(root_);
    }

    void preOrder2(){
        if(root_ == nullptr) return;
        stack<TreeNode<T>*> myStack;
        myStack.push(root_);
        while(!myStack.empty()){
            TreeNode<T>* node = myStack.top();
            cout << node->data << " ";
            myStack.pop();
            if(node->right != nullptr){
                myStack.push(node->right);
            }
            if(node->left != nullptr){
                myStack.push(node->left);
            }
        }
    }


    void inOrder2(){
        if(root_ == nullptr) return;
        stack<TreeNode<T>*> myStack;
        TreeNode<T>* curr = root_;
        while(curr != nullptr || !myStack.empty()){
            if(curr != nullptr){
                myStack.push(curr);
                curr = curr->left;
            }else{
                TreeNode<T>* node = myStack.top();
                myStack.pop();
                cout << node->data << " ";
                curr = node->right;
            }
        }
    }

    void postOrder2(){
        if(root_ == nullptr)return;
        stack<TreeNode<T>*> myStack1;
        stack<TreeNode<T>*> myStack2;

        myStack1.push(root_);
        while(!myStack1.empty()){
            TreeNode<T>* curr = myStack1.top();
            myStack2.push(curr);
            myStack1.pop();
            
            if(curr->left != nullptr) myStack1.push(curr->left);
            if(curr->right != nullptr) myStack1.push(curr->right);
        }
        while(!myStack2.empty()){
            cout << myStack2.top()->data << " ";
            myStack2.pop();
        }
    }

    void levelOrder(){
        if(root_ == nullptr) return;
        queue<TreeNode<T>*> myQueue;
        myQueue.push(root_);
        while(!myQueue.empty()){
            TreeNode<T>* curr = myQueue.front();
            cout << curr->data << " ";
            myQueue.pop();
            if(curr->left != nullptr) myQueue.push(curr->left);
            if(curr->right != nullptr) myQueue.push(curr->right);
        }
    }
};