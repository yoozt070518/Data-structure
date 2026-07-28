#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNext(const string& s){
    int m = s.size();
    vector<int> next(m-1);
    next[0] == -1;
    int j = 0, k = -1;
    while(j < m){
        if(k == -1 || s[j] == s[k]){
            ++j; ++k;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return next;
}

int main(){
    string s;
    getline(cin, s);
    int n = s.size();
    vector<int> next = getNext(s);

    vector<int> ans;
    int k = n;
    while(k > 0){
        ans.push_back(k);
        k = next[k];
    }

    for(int i = (int)ans.size()-1;i >= 0;--i){
        cout << ans[i];
        if(i > 0) cout << " ";
    }
    cout << "\n";
    return 0;
}