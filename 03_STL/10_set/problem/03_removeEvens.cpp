#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

void removeEvens(set<int>& s){
    for(auto it = s.begin(); it != s.end();){
        if(*it % 2 == 0){
            it = s.erase(it);
        }else{
            ++it;
        }
    }
}









int main(){
















    return 0;
}