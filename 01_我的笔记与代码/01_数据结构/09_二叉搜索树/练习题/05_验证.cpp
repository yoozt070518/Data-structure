#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
using namespace std;
struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): data(x), left(nullptr), right(nullptr){}
};



TreeNode* buildTree(const vector<int>& vec){
    if(vec.empty() || vec[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(vec[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while(!q.empty() && i < (int)vec.size()){
        TreeNode* node = q.front();
        q.pop();

        if(i < (int)vec.size()){
            if(vec[i] != -1){
                node->left = new TreeNode(vec[i]);
                q.push(node->left);
            }
            i++;
        }

        if(i < (int)vec.size()){
            if(vec[i] != -1){
                node->right = new TreeNode(vec[i]);
                q.push(node->right);
            }
            i++;
        }
    }
    return root;
}


bool helper(TreeNode* node, long long lower, long long upper){
    if(!node) return true;
    if(node->data <= lower || node->data >= upper) return false;
    return helper(node->left, lower, node->data)
        && helper(node->right, node->data, upper);
}


bool verifyBST1(TreeNode* root){
    return helper(root, LLONG_MIN, LLONG_MAX);    
}

bool inorder(TreeNode*node, TreeNode*& prev){
    if(!node) return true;

    if(!inorder(node->left, prev))return false;

    if(prev && prev->data >= node->data) return false;
    prev = node;
    return inorder(node->right, prev);

}

bool verifyBST2(TreeNode* root){
    TreeNode* prev = nullptr;
    return inorder(root, prev);    
}



int main(){
    string tokens;
    getline(cin, tokens);
    istringstream iss(tokens);
    vector<int> vec;
    int number;
    while(iss >> number){
        vec.push_back(number);
    }
    TreeNode* root = buildTree(vec);


    return 0;
}