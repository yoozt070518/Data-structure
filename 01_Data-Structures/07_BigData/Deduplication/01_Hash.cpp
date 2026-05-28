// 大数据查重
// 哈希表实现
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(){
    // 模拟问题， vector中放原始的数据
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0;i<10000;++i){
        vec.push_back(rand() % 10000);
    }
    // 找第一个重复的数字
    unordered_set<int> s;
    for(const auto& i : vec){
        if(s.count(i)){
            cout << i << endl;
            break;
        }else{
            s.insert(i);
        }
    }
    // 统计重复数字以及出现的次数
    unordered_map<int, int> freq;
    for(int key : vec){
        freq[key]++;
    }

    // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
    unordered_set<int> s1;
    for(int key : vec){
        s1.emplace(key);
    }
    
}