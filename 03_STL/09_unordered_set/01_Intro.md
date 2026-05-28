# unordered_set
unordered_map 存的是键值对
unordered_set 只存键
用于回答一个问题：这个东西在不在？
1. 声明方式：
unordered_set<string> s;

2. 插入：
s.insert("Alice");
s.insert("Bob");
s.insert("Alice"); // 已存在，忽略

unordered_set自动去重 同一个值插两次也只存一份

## 基本操作
1. 查找：
```cpp
unordered_set<string> s = {"Alice", "Bob", "Carol"};

auto it = s.find("Alice");
if(it != s.end())
    cout << "存在";
else
    cout << "不存在";
```
或者用count
if (s.count("Alice"))
    cout << "存在";

删除：
s.erase("Bob");

遍历：
for(const auto& x : s){
    cout << x << " ";
}