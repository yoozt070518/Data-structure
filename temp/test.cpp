#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main(){
    vector<int> v = {3,1 ,3,4,5,32,24,0};
    sort(v.begin(), v.end(),[](int a, int b){ return a > b;});
    for(int i : v){
        cout << i << " ";
    }
    
}


