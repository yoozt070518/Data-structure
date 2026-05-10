#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::vector<int> v = {1, 2, 2, 3, 4};
    for(auto it = v.begin();it != v.end();++it){
        if(*it % 2 == 0){
            it = v.erase(it);
        }
    }
    cout << v.size(); 
    for(auto it = v.begin();it != v.end();++it){
        cout << *it << endl;
    }
    return 0;
}