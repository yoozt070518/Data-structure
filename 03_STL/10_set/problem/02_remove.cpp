#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool tryRemove(set<int>& s, int x){
    auto it = s.find(x);
    if(it != s.end()){
        s.erase(it);
        return true;
    }
    return false;
}



int main(){




    return 0;
}