#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):data(x), left(nullptr), right(nullptr){}
};

TreeNode* buildTree(vector<int> vec){
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



bool isMirror(TreeNode* t1, TreeNode* t2){
    if(t1 == nullptr && t2 == nullptr) return true;
    if(t1 == nullptr || t2 == nullptr) return false;
    if(t1->data != t2->data) return false;
    return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

bool isSymmetric(TreeNode* root){
    return isMirror(root, root);
}





int main(){
    string inputline;
    getline(cin, inputline);
    istringstream iss(inputline);
    vector<int> vec;
    int number;
    while(iss >> number){
        vec.push_back(number);
    }
    TreeNode* root = buildTree(vec);
    if(isSymmetric(root)){
        cout << "true" << endl;
    }else{
        cout << "false" << endl;
    }


    return 0;
}