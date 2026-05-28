# 删除
## 场景一：删除指定键
最简单的删除：
```cpp
unordered_map<stirng, int> score;
score["Alice"] = 95;
score["Bob"] = 82;
score["Carol"] = 78;
score.erase("Bob");
```
结果：
score：{"Alice" : 95, "Carol": 78};
键不存在也没关系，不会报错 只是什么都不做

## 场景二：遍历时删除
比如你想删除所有分数低于80的学生
```cpp
unordered_map<string, int> score;
score["Alice"] = 95;
score["Bob"] = 60;
score["Carol"] = 78;
score["Dave"] = 45;
for(auto it = score.begin();it != score.end();){
    if(it->second < 80){
        it = score.erase(it);
    }else{
        ++it;
    }
}
```
结果：
score:{"Alice": 95};

为什么不用范围for删除：
```cpp
for (const auto& [k, v] : score) {
    if (v < 80)
        score.erase(k);  // 危险！删除后迭代器失效，程序可能崩溃

}
```
删除一个元素后，当前迭代器就失效了，继续用它会出问题。用迭代器写法，erase返回下一个有效迭代器，接住它就安全了