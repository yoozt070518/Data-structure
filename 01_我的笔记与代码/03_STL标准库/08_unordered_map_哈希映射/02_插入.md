# 插入
## 场景一：统计单词频率
```cpp
vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
unorded_map<string, int> freq;
for(const auto& w : words)
    freq[w]++;
```
## 场景二：只记录第一次出现的位置
假如有一串日志，想记录每个事件第一次出现在第几个位置：
```cpp
vector<string> log = {"login", "click","login","logout"};
unorded_map<string,int> first_seen;
for(int i = 0;i < log.size();++i){
    first_seen.insert({log[i],i});
}
```

## 场景三：判断插入有没有成功
insert其实有返回值，它返回一个pair：
```cpp
auto result = score.insert({"Alice", 95});
```
这里result是一个pair：
- result.first是迭代器，指向那个元素
- result.second是bool，true表示成功，false表示键已存在
实际用法：
```cpp
auto result = score.insert({"Alice",95});

if(result.second){
    cout << "插入成功";
}else{
    cout << "已存在，当前值是：" << result.first->second;
}
```
result.first是迭代器，所以用->second取值
用结构化绑定可以写得更清楚：
```cpp
auto [it,ok] = score.insert({"Alice",95});

if(ok){
    cout << "插入成功";
}else{
    cout << "已存在，当前值是：" << it->second; 
}
```

## 场景四：值是容器时分组
比如有一批学生和分数，想按分数分组：
```cpp
vector<pair<string,int>> data = {
    {"Alice",95},
    {"Bob", 60},
    {"Carol",95},
    {"Dava", 60}
};

unorded_map<int,vector<string>> groups;

for(const auto& [name, score] : data)
    group[score].push_back(name);
```

