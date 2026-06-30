#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNext(const string& p){
    int m = p.size();
    vector<int> next(m+1);
    next[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m){
        if(k == -1 || p[j] == p[k]){
            j++;k++;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return next;
}

void getAllPos(const string& t, const string& p){
    int n = t.size(), m = p.size();
    if(m == 0) return;
    vector<int> next = getNext(p);
    int i = 0;
    int j = 0;
    bool found = false;
    while(i < n){
        if(j == -1 || t[i] == p[j]){
            i++;
            j++;
            if(j == m){
            cout << i-j << " ";
            found = true;
            j = next[j];
        }
        }else{
            j = next[j];
        }
    }
    if(!found) cout << -1;
    cout << "\n";
}




int main(){
    string t, p;
    getline(cin, t);
    getline(cin, p);
    getAllPos(t, p);
    return 0;
}