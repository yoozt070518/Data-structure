// 给定 T 组测试数据。
// 每组给出 n 个互不相同的整数，按给定顺序
// 依次插入一棵初始为空的二叉搜索树（标准 BST 插入，不做任何平衡操作）。
// 插入完成后，树中恰好有一个结点的 |BF| = 2（输入保证如此）。
// 请找到该失衡结点，判断它属于哪种失衡情形，
// 执行对应的旋转修复，
//输出旋转类型和修复后整棵树的先序遍历。

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int val): data(val), left(nullptr), right(nullptr), height(0){}
};

TreeNode* buildTree(const vector<string>& vec){
    if(vec.empty() || vec[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(vec[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while(i < (int)vec.size() && !q.empty()){
        TreeNode* node = q.front();
        q.pop();
        if(i < (int)vec.size()){
            if(vec[i] != "null"){
                node->left = new TreeNode(stoi(vec[i]));
                q.push(node->left);
            }
            i++;
        }
        if(i < (int)vec.size()){
            if(vec[i] != "null"){
                node->right = new TreeNode(stoi(vec[i]));
                q.push(node->right);
            }
            i++;
        }
    }
    return root;
}
int getHeight(TreeNode* node){
    if(node == nullptr) return -1;
    return node->height;
}

void updateHeight(TreeNode* node){
    if(node == nullptr) return;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    node->height = max(lh, rh) + 1;
}

int updateTreeHeight(TreeNode* root){
    if(root == nullptr) return -1;

    int lh = updateTreeHeight(root->left);
    int rh = updateTreeHeight(root->right);

    root->height = max(lh, rh) + 1;
    return root->height;
}

TreeNode* rotateRight(TreeNode* z){
    TreeNode* y = z->left;
    TreeNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    updateHeight(z);// 先算孩子
    updateHeight(y);

    return y;
}

TreeNode* rotateLeft(TreeNode* z){
    TreeNode* y = z->right;
    TreeNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    updateHeight(z);
    updateHeight(y);

    return y;
}

int getBF(TreeNode* node){
    if(node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void freeTree(TreeNode* root){
    if(root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void rotate(TreeNode*& root){
    if(root == nullptr) return;
    rotate(root->left);
    rotate(root->right);
    if(getBF(root) > 1 || getBF(root) < -1){
        if(getBF(root) == 2){
            if(getBF(root->left) >= 1){
                cout << "LL" << endl;
                root = rotateRight(root);
            }else{
                cout << "LR" << endl;
                root->left = rotateLeft(root->left);
                root = rotateRight(root);
            }
        }else{
            if(getBF(root->right) <= -1){
                cout << "RR" << endl;
                root = rotateLeft(root);
            }else{
                cout << "RL" << endl;
                root->right = rotateRight(root->right);
                root = rotateLeft(root);
            }
        }
    } 
    updateHeight(root);
}
void getPreOrder(TreeNode* root, vector<int>& res) {
    if (root == nullptr) return;
    res.push_back(root->data);
    getPreOrder(root->left, res);
    getPreOrder(root->right, res);
}


int main(){
    int T;
    cin >> T;
    cin.ignore();
    while(T--){
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<string> vec;
        string tokens;
        while(iss >> tokens){
            vec.push_back(tokens);
        }
        TreeNode* root = buildTree(vec);
        updateTreeHeight(root);

        rotate(root);
        vector<int> preOrderRes;
        getPreOrder(root, preOrderRes);
        for (size_t i = 0; i < preOrderRes.size(); ++i) {
            cout << preOrderRes[i] << (i + 1 == preOrderRes.size() ? "" : " ");
        }
        cout << "\n";

        freeTree(root);
    }
    return 0;
}
