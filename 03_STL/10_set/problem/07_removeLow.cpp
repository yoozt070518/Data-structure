#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
void removeLowScores(map<string, int>& m, int threshold){
    for(auto it = m.begin(); it != m.end();){
        if(it->second < threshold){
            it = m.erase(it);
        }else{
            ++it;
        }
    }
}

int main(){
    return 0;
}