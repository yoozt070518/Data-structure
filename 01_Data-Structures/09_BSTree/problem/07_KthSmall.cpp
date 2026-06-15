// 题目要求：给一颗BST树和一个整数K，返回第k小的元素值(k从1开始计)
// 约束：节点数n范围[1, 10^4], 1 <= k <= n, 保证合法

#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    int size;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const vector<string>& nodes){
    if(nodes.empty() || nodes[0] == "null"){
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)nodes.size())
    {
        TreeNode* curr = q.front();
        q.pop();

        if(i < (int)nodes.size()){
            if(nodes[i] != "null"){
                curr->left = new TreeNode(stoi(nodes[i]));
                q.push(curr->left);
            }
            i++;
        }

        if(i < (int)nodes.size()){
            if(nodes[i] != "null"){
                curr->right = new TreeNode(stoi(nodes[i]));
                q.push(curr->right);
            }
            i++;
        }
    }
    return root;
}

void inorder(TreeNode* node, int k, int& count, int& result){
    if(node == nullptr) return;
    inorder(node->left, k, count, result);
    count++;
    if(count == k){
        result = node->val;
        return;
    }
    inorder(node->right, k, count, result);
}






int getKthsmall(TreeNode* root, int k){
    TreeNode* curr = root;
    while(curr != nullptr){
        int L = (curr->left != nullptr) ? curr->left->size : 0;
    

        if(k == L+1){
            return curr->val;
        }else if(k <= L){
            curr =  curr->left;
        }else{
            k -= (L+1);
            curr = curr->right;
        }
    }
    return -1;
}


int main(){
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> vec;
    string token;
    while(iss >> token){
        vec.push_back(token);
    }
    TreeNode* root = buildTree(vec);

}