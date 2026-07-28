#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val):data(val), left(nullptr), right(nullptr){}
};

TreeNode* buildTree(vector<string> vec){
    if(vec.empty() || vec[0] == "null") return nullptr;
    
    queue<TreeNode*> q;
    TreeNode* root = new TreeNode(stoi(vec[0]));
    q.push(root);

    int i = 1;
    while(!q.empty() && i < (int)vec.size()){
        TreeNode* curr = q.front();
        q.pop();

        if(i < (int)vec.size()){
            if(vec[i] != "null"){
                curr->left = new TreeNode(stoi(vec[i]));
                q.push(curr->left);
            }
            i++;
        }

        if(i < (int)vec.size()){
            if(vec[i] != "null"){
                curr->right = new TreeNode(stoi(vec[i]));
                q.push(curr->right);
            }
            i++;
        }
    }
    return root;
}

void inorder(TreeNode* node){
    if(node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

bool search(TreeNode* root, int val, TreeNode*& node){
    if(root == nullptr)return false;
    if(root->data == val){
        node = root;
        return true;
    }
    if(val < root->data){
        return search(root->left, val, node);
    }else{
        return search(root->right, val, node);
    }
}



int main(){
    string line;
    getline(cin , line);
    istringstream iss(line);
    vector<string> vec;
    string tokens;
    while(iss >> tokens){
        vec.push_back(tokens);
    }
    TreeNode* root = buildTree(vec);
    int val;
    cin >> val;
    TreeNode* node = nullptr;
    if(search(root, val, node)){
        inorder(node);
    }else{
        cout << "null" << endl;
    }

    return 0;
}