#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getNext(const string& pattern){
    int m = pattern.size();
    if(m == 0) return {};
    vector<int> next(m + 1);
    next[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m){
        if(k == -1 || pattern[j] == pattern[k]){
            j++;
            k++;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return next;
}

vector<int> kmp(const string& text, const string& pattern, int& cnt){
    int n = text.size();
    int m = pattern.size();
    vector<int> next = getNext(pattern);
    int i = 0;
    int j = 0;
    vector<int> ans;
    while(i < n){
        
        if(j == -1 || text[i] == pattern[j]){
            i++;
            j++;
            if(j == m){
                ans.push_back(i-m);
                cnt++;
                j = next[j];
            }
        }else{
            j = next[j];
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    int cnt = 0;
    vector<int> ans = kmp(text, pattern, cnt);
    cout << cnt << "\n";
    bool first = true;
    for(int i : ans){
        if(first){
            first = false;
        }else{
            cout << " ";
        }
        cout << i;
    }
    cout << "\n";
    return 0;
}