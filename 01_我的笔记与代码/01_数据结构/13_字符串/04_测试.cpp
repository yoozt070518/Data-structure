#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> buildNext(const string& p){
    int m = p.size();
    vector<int> nextval(m + 1);
    nextval[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m){
        if(k == -1 || p[j] == p[k]){
            j++; k++;
            if(p[k] != p[j]) nextval[j] = k;
            else nextval[j] = nextval[k];
        }else{
            k = nextval[k];
        }
    }
    return nextval;
}


void kmp(const string& t, const string& p, int& cnt ){
    int n = t.size();
    int m = p.size();
    vector<int> next = buildNext(p);
    int i = 0;
    int j = 0;
    while(i < n && j < m){
        if(j == -1 || t[i] == p[j]){
            i++;
            j++;
            if(j == m){
                cnt++;
                j = next[j];
            }
        }else{
            j = next[j];
        }
    } 
}

int main(){
    string T, P;
    getline(cin, T);
    getline(cin, P);
    int cnt = 0;kmp(T, P, cnt);
    cout << cnt << "\n";   
    return 0;
}