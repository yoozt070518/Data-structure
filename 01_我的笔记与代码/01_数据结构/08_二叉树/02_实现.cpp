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
    TreeNode(T val): data(val), left(nullptr), right(nullptr){}
};

template<typename T>
class BinaryTree{
private:
    TreeNode<T>* root_;

    void clear(TreeNode<T>* node){

        if(node == nullptr) return;
        if(node->left != nullptr){
            clear(node->left);
        }
        if(node->right != nullptr){
            clear(node->right);
        }
        delete node;
    }

    void preOrder(TreeNode<T>* root){
        if(root == nullptr) return;
        stack<TreeNode<T>*> myStack;
        myStack.push(root);
        while(!myStack.empty()){
            TreeNode<T>* curr = myStack.top();
            myStack.pop();
            cout << curr->data << " ";
            
            if(curr->right != nullptr){
                myStack.push(curr->right);
            }
            if(curr->left != nullptr){
                myStack.push(curr->left);
            }
        }
    }

    void inOrder(TreeNode<T>* root){
        if(root == nullptr) return;
        stack<TreeNode<T>*> myStack;
        TreeNode<T>* curr = root;
        while(curr != nullptr || !myStack.empty()){
            if(curr != nullptr){
                myStack.push(curr);
                curr = curr->left;
            }else{
                TreeNode<T>* topNode = myStack.top();
                cout << topNode->data << " ";
                myStack.pop();
                curr = topNode->right;
            }
        }
    }

    void postOrder1(TreeNode<T>* root){
        if(root == nullptr) return;
        stack<TreeNode<T>*> myStack1;
        stack<TreeNode<T>*> myStack2;
        myStack1.push(root);
        while(!myStack1.empty()){
            TreeNode<T>* curr = myStack1.top();
            myStack2.push(curr);
            myStack1.pop();
            

            if(curr->left != nullptr){
                myStack1.push(curr->left);
            }
            if(curr->right != nullptr){
                myStack1.push(curr->right);
            }
        }
        while(!myStack2.empty()){
            cout << myStack2.top()->data << " ";
            myStack2.pop();
        }
    }

    void postOrder2(TreeNode<T>* root){
        if(root == nullptr) return;
        TreeNode<T>* curr = root;
        TreeNode<T>* prev = nullptr;
        stack<TreeNode<T>*> myStack;
        while(curr != nullptr || !myStack.empty()){
            if(curr != nullptr){
                myStack.push(curr);
                curr = curr->left;
            }else{
                TreeNode<T>* topNode = myStack.top();
                if(topNode->right != nullptr && topNode->right != prev){
                    curr = topNode->right;
                }else{
                    cout << topNode->data << " ";
                    myStack.pop();
                    prev = topNode;
                    curr = nullptr;
                }
            }
        }
    }

    void levelOrder(TreeNode<T>* root){
        if(root == nullptr) return;
        queue<TreeNode<T>*> myQueue;
        myQueue.push(root);
        while(!myQueue.empty()){
            TreeNode<T>* curr = myQueue.front();
            cout << curr->data << " ";
            myQueue.pop();
            if(curr->left != nullptr){
                myQueue.push(curr->left);
            }
            if(curr->right != nullptr){
                myQueue.push(curr->right);
            }
        }
    }
public:
    BinaryTree():root_(nullptr){}
    ~BinaryTree(){
        clear(root_);
        root_ = nullptr;
    }
    void preOrder(){
        preOrder(root_);
    }
    void inOrder(){
        inOrder(root_);
    }
    void postOrder1(){
        postOrder1(root_);
    }
    void postOrder2(){
        postOrder2(root_);
    }
    void levelOrder(){
        levelOrder(root_);
    }
};


int main(){
    return 0;
}