#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int val;
    int left;
    int right;
    bool is_red;
};

int checkBRT(const vector<Node>& tree, int curr, int&  prev_val, bool& is_first){
    if(curr == -1){
        return 0;
    }

    if(tree[curr].is_red){
        int l = tree[curr].left;
        int r = tree[curr].right;
        if((l != -1 && tree[l].is_red) || (r != -1 && tree[r].is_red)){
            return -1;
        }
    }

    int lbh = checkBRT(tree, tree[curr].left, prev_val, is_first);
    if(lbh == -1) return -1;

    if(is_first){
        is_first = false;
    }else{
        if(prev_val >= tree[curr].val) return -1;
    }
    prev_val = tree[curr].val;

    int rbh = checkBRT(tree, tree[curr].right, prev_val, is_first);
    if(rbh == -1) return -1;

    if(lbh != rbh) return -1;
    return tree[curr].is_red ? lbh : lbh + 1;
}


bool isBRT(const vector<Node>& tree, int r, int n){
    if(n == 0) return true;

    if(tree[r].is_red) return false;

    int prev_val = 0;
    bool is_first = true;

    if(checkBRT(tree, r, prev_val, is_first) == -1){
        return false;
    }
    return true;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        int n, r;
        cin >> n >> r;
        vector<Node> tree(n);
        for(int i = 0;i<n;++i){
            cin >> tree[i].val >> tree[i].is_red >> tree[i].left >> tree[i].right; 
        }
        cout << (isBRT(tree, r, n) ? "Yes\n" : "No\n");
    }
    return 0;
}