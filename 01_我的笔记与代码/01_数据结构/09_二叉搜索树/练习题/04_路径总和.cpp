#include <sstream>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr){}
};

TreeNode* buildTree(vector<int> vec){
    if(vec.empty() || vec[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(vec[0]);
    queue<TreeNode*> q;
    q.push(root);


    int i  = 1;
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

bool hasPathSum2(TreeNode* root, int targetSum){
    if(root == nullptr) return false;

   
    stack<TreeNode*> nodeStack;
    stack<int> sumStack;
    
    nodeStack.push(root);
    sumStack.push(root->data);
    
    while(!nodeStack.empty()){
        TreeNode* curr = nodeStack.top();
        int currSum = sumStack.top();
        nodeStack.pop();
        sumStack.pop();

        if(curr->left ==nullptr && curr->right == nullptr){
            if(currSum == targetSum) return true;
        }
        
        if(curr->right !=nullptr){
            nodeStack.push(curr->right);
            sumStack.push(currSum + curr->right->data);
        }
        if(curr->left != nullptr){
            nodeStack.push(curr->left);
            sumStack.push(currSum + curr->left->data);
        }    
    }
    
    return false;
}

bool hasPathSum1(TreeNode* root, int targetSum){

    if(root == nullptr) return false;

    if(root->left == nullptr && root->right == nullptr) return root->data == targetSum;

    return hasPathSum1(root->left, targetSum - root->data)

        || hasPathSum1(root->right, targetSum - root->data);

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
    int targetSum;
    cin >> targetSum;
    if(hasPathSum1(root, targetSum)){
        cout << "true" << endl;
    }else{
        cout << "false" << endl;
    }








    return 0;
}