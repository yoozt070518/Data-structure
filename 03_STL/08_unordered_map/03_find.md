# 查找
## 场景一：安全读取，键不存在时给默认值
```cpp
unordered_map<string, int> score;
score["Alice"] = 95;
score["Bob"] = 82;

auto it = score.find("Zoe");

int val = (it != score.end()) ? it->second : 0;
cout << val;
```

对比用[]读取：
```cpp
in val = score["Zoe"];
```
find 不会修改表，[]会。所以不确定键存不存在时，永远用find

## 场景二：两数之和
有一个数组和一个目标值，找出两个数相加等于目标值，返回它们的下标。
```cpp
vector<int> nums = {2, 7, 11 ,15};
int target = 9;
```
思路：
- 遍历每个数nums[i]
- 计算还差多少need = target - nums[i]
- 用find查找表里有没有need
- 有就找到了，没有就把nums[i]存进表

```cpp
unordered_map<int,int> seen;
for(int i = 0;i<nums.size();++i){
    int need = target - nums[i];
    auto it = seen.find(need);
    if(it != seen.end()){
        cout << it->second << ", " << i;
        break;
    }
    seen[nums[i]] = i;
}
```

## 场景三：at()
at() 和 [] 一样能读取值：
```cpp
unordered_map<string, int> score;
score["Alice"] = 95;

cout << score["Alice"];
cout << score.at("Alice");
```
但区别在于键不存在时
```cpp
cout << score["Zoe"]; // 悄悄插入Zoe，返回0
cout << score.at("Zoe");   // 直接抛出异常out_of_range
```
什么时候用at？
当你确定键一定存在， 不存在就是程序出了bug，希望立刻暴露问题
```cpp
// 比如你之前已经确认过Alice在表里
// 用at()读取，万一哪天代码改错了键不存在，马上报错，不会悄悄返回0造成难以发现的bug
cout << score.at("Alice");
```


