#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

struct  TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): data(x), left(nullptr), right(nullptr){}
};

TreeNode* buildTree(vector<int> vals){
    if(vals.empty() || vals[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1; 
    while(!q.empty() && i < (int)vals.size()){
        TreeNode* node = q.front();
        q.pop();

        if(i < (int)vals.size()){
            if(vals[i] != -1){
                node->left = new TreeNode(vals[i]);
                q.push(node->left);
            }
            i++;
        }

        if(i < (int)vals.size()){
            if(vals[i] != -1){
                node->right = new TreeNode(vals[i]);
                q.push(node->right);
            }
            i++;
        }
    }
    return root;
}






int main(){
    string tokens;
    getline(cin, tokens);
    istringstream iss(tokens);

    vector<int> vals;
    int number;

    while(iss >> number){
        vals.push_back(number);
    }
    TreeNode* root =  buildTree(vals);


    

    return 0;
}