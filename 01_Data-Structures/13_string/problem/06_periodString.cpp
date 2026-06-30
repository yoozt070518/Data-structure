#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNext(const string& s){
    int m = s.size();
    vector<int> next(m+1);
    next[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m){
        if(k == -1 || s[j] == s[k]){
            j++;
            k++;
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
    int L = s.size();
    vector<int> next = getNext(s);
    int p = L - next[L];
    if(L % p == 0) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}