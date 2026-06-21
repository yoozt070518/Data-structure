#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, int> countWords(const vector<string>& words){
    map<string, int> fq;
    for(auto k : words){
        fq[k]++;
    }
    return fq;
}



int main(){
    return 0;
}