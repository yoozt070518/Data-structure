#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
// ① 添加或更新某人的分数（已存在则覆盖，不存在则新增）
void setScore(map<string,int>& m, const string& name, int score){
    m[name] = score;
}
// ② 查询某人分数；不存在返回 -1。注意 m 是 const，不能污染它
int getScore(const map<string,int>& m, const string& name){
    auto it = m.find(name);
    if(it != m.end()){
        return it->second;        
    }else{
        return -1;
    }
}
// ③ 统计分数 >= threshold 的人数
int countAbove(const map<string,int>& m, int threshold){
    int cnt = 0;
    for (const auto& kv : m) {
        if (kv.second >= threshold) {
            ++cnt;
        }
    }
    return cnt;
}
// ④ 按名字字典序，每行输出 "name: score"
void printSorted(const map<string,int>& m){
    for (const auto& [name, score] : m) {
        cout << name << ": " << score << "\n";
    }
}


int main(){
    return 0;
}