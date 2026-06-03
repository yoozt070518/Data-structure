#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

int main(){
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i<10000;i++){
        vec.push_back(rand()%1000);
    }

    // 统计重复次数最小的前三个数字
    int n = 3;
    unordered_map<int, int> freq;
    for(const auto& i : vec){
        freq[i]++;
    }
    using Type = pair<int, int>;
    auto cmp = [](Type a, Type b){return a.second < b.second;};
    priority_queue<Type,vector<Type>,decltype(cmp)> maxheap(cmp);
    for(const auto& [k, v] : freq){
        if((int)maxheap.size() < n){
            maxheap.push({k,v});
        }else{
            if(v < maxheap.top().second){
                maxheap.pop();
                maxheap.push({k, v});
            }
        }
    }
    while(!maxheap.empty()){
        cout << maxheap.top().first << ": " << maxheap.top().second << ";";
        maxheap.pop();
    }
    return 0;
}