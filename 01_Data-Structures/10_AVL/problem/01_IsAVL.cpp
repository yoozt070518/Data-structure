// 判断是否为AVL树
// 题目描述：
// 给定 T 棵二叉树，逐棵判断它是否为 AVL 树。
// 一棵树是 AVL 树当且仅当它同时满足两个条件：
// 它是一棵二叉搜索树（BST，所有结点的值严格满足左子树 < 根 < 右子树
// ，不允许重复值）；并且每个结点的
// 平衡因子 BF = height(left) − height(right) 的绝对值不超过 1。
// 空树视为合法的 AVL 树。

#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

struct TreeNode
{
    int val;
    int left;
    int right;
};

int checkAVL(const vector<TreeNode>& tree,int curr, long long& prev, bool& isAVL){
    if(curr == -1) return -1;// 空节点高度为-1

    int lh = checkAVL(tree, tree[curr].left, prev, isAVL);

    if(tree[curr].val <= prev){
        isAVL = false;
    }
    prev = tree[curr].val;

    int rh = checkAVL(tree, tree[curr].right, prev, isAVL);

    int bf = lh - rh;
    if(bf < -1 || bf > 1){
        isAVL = false;
    }

    return max(lh, rh) + 1;
}





int main(){
    int T;
    cin >> T;
    while(T--){
        int n, r;
        cin >> n >> r;
        if(n == 0){
            cout << "YES" << endl;
            continue;
        }

        vector<TreeNode> tree(n);
        for(int i = 0;i<n;++i){
            cin >> tree[i].val >> tree[i].left >> tree[i].right;
        }
        bool isAVL = true;
        long long prev = LLONG_MIN;
        checkAVL(tree, r, prev, isAVL);

        cout << (isAVL ? "YES" : "NO") << endl;
    }
    

    return 0;
}
