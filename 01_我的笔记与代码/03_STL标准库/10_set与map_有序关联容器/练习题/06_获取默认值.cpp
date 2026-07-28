#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

int getOrDefault(const map<string, int>& m, const string& key, int defaultVal){
    auto it = m.find(key);
    if(it != m.end()){
        return it->second;
    }
    return defaultVal;
}





int main(){



    return 0;
}