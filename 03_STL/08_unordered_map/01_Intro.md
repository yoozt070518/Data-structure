# unordered_map
## 底层
底层原理是哈希表 查找极快的原因是不用一个个比较 直接算出位置。代价是：存进去的顺序是由哈希表决定的，跟插入顺序无关，所以是无序的

## 常用API
1. 容量
- size();       返回元素个数
- empty();      是否为空
- max_size();   理论上能容纳的最大元素数(很少用)

2. 插入
- m[key] = val;         有则覆盖，无则插入
- insert({key, val});   键已经存在则忽略，不覆盖。返回pair<iterator,bool>
- emplace(key,val);     同insert，但原为构造，效率更高
- insert_or_assign(key,val) 有则覆盖 无则插入(比[]更安全)
- try_emplace(key,val); 键不存在才构造值，避免不必要的构造开销

3. 查找
- find(key)         返回迭代器，找不到返回end()
- count(key)        存在返回1 不存在返回0
- contains(key)     返回bool，c++20，语义最清晰
- at(key)           返回值的引用，键不存在时抛异常out_of_range (比[]更安全)

4. 删除
- erase(key)        按键删除，返回删除的个数(0或1)
- erase(iterator)   按迭代器删除，返回下一个迭代器，遍历删除时用这个
- clear()           清空所有元素，桶数组保留
5. 哈希桶
- bucket_count()    当前桶的数量
- load_factor()     负载因子 = 元素数/桶数，越大越容易冲突
- max_load_factor(f)设置最大负载因子，超过后自动扩容(默认1.0)
- reserve(n)        提前告知要存n个元素，避免中途扩容，性能优化常用
- rehash(n)         强制设置桶数为n，手动控制扩容



6. 补充说明
- at()和[]: 两个都能读值，但[]键不存在时静默插入，at()键不存在时抛异常。只读不写时用at()更安全
- insert的返回值：返回的时一个pair<iterator, bool>，第二个 bool 就告诉你"有没有真的插进去"
- reserve是性能优化的常用手段



## 基本操作
1. 插入
```cpp
#include <unordered_map>
#include <string>
using namespace std;

unorered_map<string, int> score;

// 方式一：operator[] 若键不存在会自动创建
score["Alice"] = 95;
score["Bob"] = 82;

// 方式二：insert 键已存在时插入失效，不覆盖
score.insert({"Alice",100}); // 失效，Alice 已存在
score.insert({"Carol",78});  // 成功

// 方式三：emplace 原为构造，效率最高
score.emplace("Dave", 88);
```
> 1. 键是string 值是int 尖括号里填<键类型，值类型>
> 2. [] 是最常用的写法，键不存在 -> 自动插入并把值初始化为0 再赋值
> 3. insert保护已有数据：键重复时静默失败，不会覆盖旧值
> 4. emplace直接在桶里构造，省去一次拷贝，大对象时更快


2. 查找
```cpp
// 危险写法：键不存在时会插入一个0
int x = score["Zoe"];

// 安全写法：find返回迭代器
auto it = score.find("Alice");
if(it!=score.end()){
    // it->first = 键， it->second = 值
    cout << it->second; // 95
}

// 安全写法2：count 返回0或1
if(score.count("Bob")){
    cout << score["Bob"]; // 82
}

// c++20：contains 最直观
if(score.contains("Carol")){...};
```
> 1. []查不到键时会静默插入，size悄悄变大，最常见的bug来源
> 2. find返回迭代器：找到则只想元素，找不到则等于eng().if->first是键，it->second是值
> 3. count对unordered_map只返回0或1，用来判断存在性很简洁
> 4. c++20的contains语义最清晰，推荐新代码使用

3. 删除
```cpp
// 按键删除，返回删除的元素个数(0或1)
score.erase("Bob");

//  先find再erase————只想再确认存在后删除
auto it = score.find("Carol");
if(it != score.end()){
    score.erase(it);
}

// 清空整个表
score.clear();

score.size();   // 元素个数
score.empty();  // 是否为空
```
> 1. 传键名删除，若键不存在则什么都不做，不会报错
> 2. 先find拿到迭代器，再传迭代器给erase，省去第二次哈希计算，微小性能优化
> 3. clear后size变成0，但内存不一定释放，想彻底释放用swap技巧

4. 遍历
```cpp
// 范围for：最常用，顺序不定
for(auto& [key,val]: score){
    cout << key << ": " << val << endl;
}

// 等价的迭代器写法(C++11 之前风格)
for(auto it = score.begin(); it != score.end();++it){
    cout << it->first << ": " << it->second << "/n";
}

// 遍历时删除————必须用迭代器，不能用范围for
for(auto it = score.begin(); it!=end();){
    if(it->second < 80)
        it = score.erase(it);
    else
        ++it;
}
```
> 结构化绑定[key,val]是c++17语法，auto&避免拷贝。输出顺序由哈希值决定，每次运行可能不同
> it->first是键，it->second是值。这是理解迭代器的基础写法
> 遍历中删除的正确姿势：erase返回被删元素的下一个有效迭代器，用它继续循环，不能it++

###常见的坑
1. []会自动插入。写if(score["Zoe"] > 90)看起来无害，但如果Zoe不存在，它会悄悄在表里插入{"Zoe",0},导致size变大，逻辑出错。查找请用find或contains
2. 遍历时不能用范围for删除元素。删除会让当前迭代器失效，必须用it = erase(it)的写法接住返回值。
3. 输出顺序不固定。同样的代码 不同编译器 不同运行，遍历顺序可能不一样，不要依赖它