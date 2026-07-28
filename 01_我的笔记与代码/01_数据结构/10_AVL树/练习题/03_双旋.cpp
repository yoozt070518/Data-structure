#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr), height(0) {}
};

// ---------- 基础工具 ----------

int getHeight(TreeNode* node) {
    return node ? node->height : -1;
}

void updateHeight(TreeNode* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBF(TreeNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// ---------- 层序建树 ----------

// 从 tokens 数组构建二叉树
// 逻辑：层序遍历的逆过程——用队列按 BFS 顺序
// 给每个非 null 结点分配左右孩子
TreeNode* buildTree(const vector<string>& tokens) {
    if (tokens.empty() || tokens[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(tokens[0]));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)tokens.size()) {
        TreeNode* curr = q.front();
        q.pop();

        // 左孩子
        if (i < (int)tokens.size()) {
            if (tokens[i] != "null") {
                curr->left = new TreeNode(stoi(tokens[i]));
                q.push(curr->left);
            }
            i++;
        }
        // 右孩子
        if (i < (int)tokens.size()) {
            if (tokens[i] != "null") {
                curr->right = new TreeNode(stoi(tokens[i]));
                q.push(curr->right);
            }
            i++;
        }
    }
    return root;
}

// 建树后所有结点 height 为 0，需要后序遍历算一遍真实高度
void initHeights(TreeNode* node) {
    if (!node) return;
    initHeights(node->left);
    initHeights(node->right);
    updateHeight(node);
}

// ---------- 旋转 ----------

TreeNode* rotateRight(TreeNode* z) {
    TreeNode* y = z->left;

    z->left = y->right;   // T3 过继给 z
    y->right = z;          // z 降为 y 的右孩子

    updateHeight(z);       // 先孩子
    updateHeight(y);       // 再父亲

    return y;              // y 是新根
}

TreeNode* rotateLeft(TreeNode* z) {
    TreeNode* y = z->right;

    z->right = y->left;
    y->left = z;

    updateHeight(z);
    updateHeight(y);

    return y;
}

// ---------- 查找失衡点并修复 ----------

// 后序遍历找到唯一的 |BF|=2 结点，执行旋转，
// 旋转类型写入 rotType（逻辑与 I/O 分离）
TreeNode* fix(TreeNode* node, string& rotType) {
    if (!node) return nullptr;

    node->left  = fix(node->left, rotType);
    node->right = fix(node->right, rotType);
    updateHeight(node);

    int bf = getBF(node);

    if (bf == 2) {
        if (getBF(node->left) >= 1) {          // LL：直线，单旋
            rotType = "LL";
            return rotateRight(node);
        } else {                                // LR：折线，先拉直再单旋
            rotType = "LR";
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (bf == -2) {
        if (getBF(node->right) <= -1) {         // RR：直线，单旋
            rotType = "RR";
            return rotateLeft(node);
        } else {                                // RL：折线，先拉直再单旋
            rotType = "RL";
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

// ---------- 输出 ----------

void preorder(TreeNode* node, vector<int>& res) {
    if (!node) return;
    res.push_back(node->key);
    preorder(node->left, res);
    preorder(node->right, res);
}

void freeTree(TreeNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// ---------- 主流程 ----------

int main() {
    int T;
    cin >> T;
    cin.ignore();

    while (T--) {
        // 读取一整行，拆成 token
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<string> tokens;
        string tok;
        while (iss >> tok) tokens.push_back(tok);

        // 建树 + 算高度
        TreeNode* root = buildTree(tokens);
        initHeights(root);

        // 找失衡点并修复
        string rotType;
        root = fix(root, rotType);

        // 输出
        cout << rotType << "\n";
        vector<int> res;
        preorder(root, res);
        for (int i = 0; i < (int)res.size(); i++) {
            if (i > 0) cout << " ";
            cout << res[i];
        }
        cout << "\n";

        freeTree(root);
    }
    return 0;
}