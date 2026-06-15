// 题目:给一棵二叉搜索树的根节点 root,返回树中任意两个不同节点值之间的最小差值(差值为绝对值,是正数)。
// 约束:节点数 [2, 10^4];0 <= Node.val <= 10^5。注意两点:节点数至少 2,所以不用处理空树;节点值非负且最大 10^5,差值不会超过 int,也不会和负数哨兵撞车。

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

void inorder(TreeNode* node, TreeNode*& prev, int& minDiff){
    if(node == nullptr) return;

    inorder(node->left, prev, minDiff);

    if(prev != nullptr){
        minDiff = min(minDiff, node->val - prev->val);
    }
    prev = node;

    inorder(node->right, prev, minDiff);
}

int getMinDiff(TreeNode* root){
    TreeNode* prev = nullptr;
    int minDiff = INT_MAX;
    inorder(root, prev, minDiff);
    return minDiff;
}


int getMinDiff2(TreeNode* root){
    TreeNode* curr = root;
    stack<TreeNode*> s;
    TreeNode* prev = nullptr;
    int minDiff = INT_MAX;
    while(curr != nullptr || !s.empty()){
        while(curr != nullptr){
            curr = curr->left;
            s.push(curr);
        }
        curr = s.top(); s.pop();
        if(prev != nullptr){
            minDiff = min(minDiff, curr->val - prev->val);
        }
        prev = curr;
        curr = curr->right;
    }

    return minDiff;
}



int main(){
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> nodes;
    string tokens;
    while(iss >> tokens){
        nodes.push_back(tokens);
    }

    TreeNode* root = buildTree(nodes);
    cout << getMinDiff(root) << endl;
    return 0;
}