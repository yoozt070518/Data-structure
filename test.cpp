#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <functional>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {}
};

void preorder(TreeNode* root){
    if(!root){
        return;
    }
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root){
    if(!root){
        return;
    }
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(TreeNode* root){
    if(!root){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

TreeNode* search(TreeNode* root, int target){
    if(!root) return nullptr;
    if(root->val == target) return root;
    if(target < root->val)
        return search(root->right, target);
    else
        return search(root->right,target);
}

TreeNode* insert(TreeNode* root, int val){
    if(!root) return new TreeNode(val);

    if(val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    
    return root;
}


int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);
}