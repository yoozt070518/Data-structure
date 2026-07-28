#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNext(string& p){
    int m = p.size();
    vector<int> next(m);
    next[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m - 1){
        if(k == -1 || p[j] == p[k]){
            j++; k++;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return next;
}

int maxNonOverlap(string& t, string& p){
    int n = t.size(), m = p.size();
    vector<int> next = getNext(p);
    int i = 0, j = 0, cnt = 0;
    while(i < n){
        if(j == -1 || t[i] == p[j]){
            i++; j++;
        }else{
            j = next[j];
        }
        if(j == m){
            cnt++;
            j = 0;
        }
    }
    return cnt;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string T, P;
    getline(cin, T);
    getline(cin, P);
    cout << maxNonOverlap(T, P) << "\n";
    return 0;
}
