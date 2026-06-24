#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNext(const string& pattern){




    
}

int kmp(const string& text, const string& pattern){
    int n = text.size();
    int m = pattern.size();
    if(m == 0) return 0; // 空模式约定匹配在位置0
    vector<int> next = getNext(pattern);
    int i = 0;
    int j = 0;
    while(i < n && j < m){
        if(text[i] == pattern[j]){
            i++;
            j++;
        }else if( j > 0 ){
            j = next[j];
        }else{
            ++i;
        }
    }
    if(j == m) return i - j;
    return -1;
}





int main(){
    return 0;
}