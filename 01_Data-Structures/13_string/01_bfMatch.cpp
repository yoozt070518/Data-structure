#include <iostream>
#include <string>
using namespace std;

int bfMatch(const string& s, const string& p){
    int n = s.size(),m = p.size();
    int i = 0, j = 0;
    while(i < n && j < m){
        if(s[i] == p[j]){
            i++;
            j++;
        }else{
            i = i-j+1;
            j = 0;
        }
    }
    return (j == m) ? (i-j) : -1;
}






int main(){
    


    return 0;
}