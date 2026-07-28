# set&map
set是有序唯一集合，底层就是红黑树————有序，去重，增删查O(logn)
## 1.声明，插入，去重
### 1.1创建set的几种方式
```cpp
#include <set>

set<int> a;                       // 空集合
set<int> b = {3, 1, 4, 1, 5};     // 初始化列表 -> 内部自动变成{1, 3, 4, 5}
set<int> c(b);                    // 拷贝构造，c是b的副本
vector<int> v = {5, 2, 8, 2};     
set<int> d(v.begin(), v.end());   // 从迭代器范围构造->{2, 5, 8}
```
注：
- 初始化列表里就算有重复，无序，建出来也是**自动排序+去重的**
- 第四个是实战常用的方法：把vector去重并排序，直接喂给set的范围构造就行

### 1.2插入insert
最常用的是insert(value).返回值是一个pair<iterator, bool>
- .first:一个迭代器，指向集合里那个元素————不管这次新插进去的，还是原本就在的，都指向它
- .second:一个bool，true表示“这次成功插入了(原来没有)”，false表示“已经存在，没插”

```cpp
set<int> s;

pair<set<int>::iterator, bool> r = s.insert(10);
// 第一种写法，写完整的类型
auto r2 = s.insert(10);
// 第二种auto类型推导
auto[it, inserted] = s.insert(10);
// 用具体的括号类型推导
if(inserted){
    // 这是第一次见到这个元素，it指向它
}else{
    // 这个值已经存在了，it指向已有的那个
}
```

还有集中插入形式
```cpp
s.insert(v.begin(), v.end()); // 插入一整个范围（把v里的元素都插进来，自动去重排序）
s.insert({7, 8, 9}); // 插入一个初始化列表
s.emplace(10);// 原地构造元素，返回值和insert一样
```
emplace和insert对int没区别
但元素是复杂类型时(比如set<string>或set<pair< int, int>>),emplace能少一次临时对象的构造,稍微高效

### 1.3去重的本质
插入一个已经存在的值不会产生重复，返回bool是false，本质就是红黑树不存在重复key

### 1.4set的元素是只读的
不可以通过迭代器去改set里元素的值
```cpp
auto it = s.find(10);
*it = 20; // 编译错误！set的元素是const，不能改
```
为什么？因为元素的**值决定了它在红黑树里的位置(整棵树都是按值排好序的)**。要是允许随手把10改成20，它在树里的位置就错了，有序结构就废了。
因此想修改一个元素，唯一正路就是**删除旧的，插入新的**
```cpp
s.erase(10);
s.insert(20);
```

## 2.查找与存在性：find/count/contains
### 2.1find -- 返回迭代器
```cpp
auto it = s.find(10);
```
- 找到 -> 返回指向该元素的**迭代器**
- 找不到 -> 返回s.end()(尾后迭代器，不指向任何有效元素)
- 复杂度O(logn)

所以判断找没找到，就是**拿返回值和s.end()比**，它既不抛异常，也不返回null

```cpp
anto it = find(10);
if(it != s.end()){
    cout << *it; 
}else{
    cout << "没找到";
}
```
为什么find返回迭代器，而不是简单给个bool?
- 因为很多时候你找到之后，还想用这个位置继续做事
- 比如删掉它(s.erase(it)),从它开始往后遍历，或者看它前后相邻的元素
- 迭代器携带的信息比bool多得多
- 注意：**set元素只读不能改**

### 2.2count--返回个数
```cpp
if(s.count(10)){...}
```
count(x)返回x在集合里的个数。对set，因为去重，这个数只可能是0或1.而0/1正好对应false/true用
所以它常呗拿来左存在性判断，比find写着省事
- 复杂度也是O(logn)
- 注意：到了muliset，同一个值能存多份时，那时count真的会返回大于一的个数，但在set它永远都是0或1

### 2.3contains -- 返回bool
```cpp
if(s.contains(10)){...}
```
contains(x)直接返回bool，找到true，没找到false
最直观，最达意。就是专门为判断在不在设计的

### 2.4实战怎么挑
- **只想知道在不在** ->有c++20就用contains，没有就用count
- **找到后还要用那个位置** -- 用find拿迭代器
- **别拿count去找位置** -- 它只给个数，你拿不到元素的落点
- 一个常见的**啰嗦写法**：为了判断存在，写if(s.find(x) != s.end()) -- 能用，但既然只是判断存在，contains/count更短更达意，把find留给要用位置的场合

三者性能都是O(logn)差别不在速度，在语义：find给你位置，count/contains给你有没有

## 3.删除与遍历
### 3.1erase的三种形式
```cpp
// 1.按值删：返回删除的个数
size_t n = s.erase(10); // 删除成功返回1，没有这个值返回0

// 2.按迭代器删：返回指向被删元素的下一个位置的迭代器(c++11起才有)
auto nxt = s.erase(it); // 删除it指向的元素，nxt指向下一个

// 3.按范围删[first, last)，返回last
s.erase(s.begin(), s.end()); 删除整个区间
```

### 3.2迭代器失效--实战最大的坑，重点讲
关联容器(set/map)的迭代器失效规则
> 删一个元素，只让指向【指向被删元素】的迭代器失效，其余迭代器全部都还有效；插入则不让任何迭代器失效
(这正是那棵树的性质--删除制动被删节点，别的节点对象原地不动)

一个错误写法：
```cpp
for(auto it = s.begin(); it != s.end(); ++it){
    if(*it % 2== 0){
        s.erase(it);    // it失效
    }// 循环再++it -> 未定义行为
}
```

正确写法，就靠那个返回值--erase删完会把"下一个位置"还给你，用它接住

```cpp
for(auto it = s.begin(); it != s.end(); ){
    if(*it % 2== 0){
        it = s.erase(it);
    }else{
        ++it;
    }
}
```
1. 循环头不写++it
2. 删的那支用it = s.erase(it)
3. 不删的那支才用++it

若编译器支持c++20，还有个更省心的erase_if,一行干掉手写循环和它的坑

```cpp
std::erase_if(s, [](int x){ return x % 2 == 0;});
```

### 3.3遍历
```cpp
for(int x : s) cout << x << ' ';
for(auto it = s.begin(); it != s.end(); ++it)
    cout << *it << " ";
for(auto it = s.rbegin(); it != s.rend(); ++it)
    cout << *it << " ";
```
rbegin()/rend()是**反向迭代器**，从最大值往最小走--需要降序输出时用它

### 3.4size/empty/clear
```cpp
s.size()   // 元素个数
s.empty()  // 是否为空
s.clear()  // 清空全部元素
```

## 4.有序的威力：lower_bound/upper_bound/equal_range,范围，自定义比较器
这一整块，是set相对unordered_set真正值钱的地方--全建立在有序上，unordered_set一样都给不了

### 4.1ower_bound 与 upper_bound(核心)
这俩返回的都是迭代器，差别只在一个等号：
```cpp
s.lower_bound(x); // 指向第一个 >= x的元素
s.upper_bound(x); // 指向第一个 > x的元素
```
- 找不到(所有元素都比它小) -> 返回end()
- 复杂度O(logn)

差别盯死:
lower_bound 是 >= (包括x自己)
upper_bound 是 > (不含x)
一个记忆法：
lower_bound 是“x该插进去的最左位置”
upper_bound 是“最右”位置
```cpp
set<int> s = {1, 3, 5, 7, 9};
s.lower_bound(5);   // -> 5(第一个 >= 5)
s.upper_bound(5);   // -> 7(第一个 > 5)
s.lower_bound(4);   // -> 5(第一个 >= 4)
s.upper_bound(10);  // ->end()(没有 > 10的)
```
它的实战用途(这才是重点)
1. 范围查询--区间[a,b]内的所有元素，就是[lower_bound(a), upper_bound(b)):

```cpp
for(auto it = s.lower_bound(a); it != s.upper_bound(b);++it)
    cout << *it << ' ';
```

2. 批量删区间--删除[a,b]内所有元素，一次性搞定

```cpp
s.erase(s.lower_bound(a), s.upper_bound(b));
```
这就是“山一段连续区间的捷径”

3. 前驱/后继
- 后继(第一个 > x 的) ：直接s.upper_bound(x);
- 前驱(最后一个 < x的) ：s.lower_bound(x)再--， 但要判断它是不是begin()(否则没有前驱)

```cpp
auto it = s.lower_bound(x);
if(it != s.begin()){--it;...}
else{// 没有前驱}
```
一个必须知道的**性能坑**：用成员函数s.lower_bound(x),千万别用通用算法std::lower_bound(s.begin(), s.end(), x)
后者是给随机访问容器(如vector)设计的，套到set这种迭代器上会退化成O(n)
成员版才走树，才是O(logn)

### 4.2equal_range
```cpp
auto [lo, hi] = s.equal_range(5); // = {lower_bound(5), upper_bound(5)}
```
返回一个pair，正好是"等于x的那段范围[lo, hi)"。对set，这段要么空(x不在)，要么1个元素;
它的真正用武之地是下面的multiset(一次拿到所有相同元素)

### 4.3自定义比较器(改排序规则)
set默认用 < 升序。想改规则，再类型里加第二个模板参数：
```cpp
set<int, greater<int>> s;
```
对自定义类型，传一个比较器：
```cpp
struct Byx{
    bool operator()(const Point& a, const Point& b) const{
        return a.x < b.x; // 按x升序
    }
};
set<Point, Byx> s;
```
一个要当心的点：比较器不光决定排序，还决定"谁和谁算相等/重复" -- set认为a , b相等的依据是"!cmp(a,b) && !cmp(b, a)"。所以上面只按x比的话，两个x相同，但是y不同的点会被当成重叠，只留一个。自定义比较器时，请务必想清楚你的"相等"是不是你想要的

### 4.4 multiset(允许重复)
```cpp
multiset<int> ms;
ms.insert(5);
ms.insert(5); // 两个5都留着
ms.count(5);  // 2
```
和set的区别：
- insert总是成功(允许重复)，所以它不返回bool，只返回迭代器
- count(x) 可能 > 1(真的是个数了)
- erase(值) 会删掉所有等于该值的元素，返回删除个数；若只想删除一个，用erase(find(值))(删个迭代器)
- equal_range(x)拿到所有等于x的值--这才是它的主场
- 用途：需要保留重复的有序数据(多重计数，带重复的排序序列)

## 5. map入门：pair,声明，插入，operator[]的陷阱
### 5.1map是什么+元素的真面目pair
map是有序键值映射：存一堆key -> value 的对，按key唯一，按key自动升序。底层还是那颗红黑树，只不过这次按key排序

map里每个元素，真实类型是pair<const Key, Value>

```cpp
map<string, int> m;
// m里每个元素都是pair<const string, int>
// 元素.first -> key(const 不能改)
// 元素.second -> value(可以改)
```
key是const -- 和set元素只读同一个道理：key决定了这个pair再红黑树里的位置，改了key就破坏了有序结构。所以key只读，value可改。

### 5.2声明
```cpp
#include <map>

map<string, int> m;
// 空map：string -> int
map<string, int> m2 = {{"a", 1}, {"b", 2}};
// 初始化列表
map<int, string> m3;
// int -> string也行
```

### 5.3插入的几种方式(各有脾气，重点)
map往里塞东西有好几种，行为不一样，跳错了会出bug
1. operator[] -- 最常用，但隐藏着map最大的陷阱
```cpp
m["apple"] = 3; // "apple" 不存在 -> 插入并赋值3
// 若已存在 -> 覆盖成3
```
写赋值时它很顺手，但陷阱在于：m["key"]这个操作只要key不存在，就会自动插入一个value为默认值的元素(int是0，string是空串)，然后返回那个value的引用
也就是说：
```cpp
map<string, int> m;
int x = m["ghost"];
// 以为只是查，但实际上偷偷插入了{"ghost", 0}
// 现在m.size() == 1
```
operator[]既是读，又可能是写--光想查一个key在不在，绝不能用[](会污染你的map)，要用find/count/at

2. insert -- key已存在时不覆盖
```cpp
m.insert({"apple", 3});
auto [it, ok] = m.insert({"apple", 5});
```
返回值和set一样是pair<iterator, bool>
关键区别：insert再key已经存在时保留旧值，不覆盖(返回false)
而operator[]会覆盖。

3. emplace：原地构造那个pair，行为类似insert，复杂value类型时省一次构造
4. insert_or_assign(C++17) -- 有则改，无则插且更明确

```cpp
m.insert_or_assign("apple", 5);
```
它干的事和m["apple"] = 5结果一样，但更明确，还能拿到bool(告诉你是新插的还是改的)，也没有[]那种"先插默认值再覆盖"的中间步骤

## 6.map的访问与查找:operator[]/at/find,遍历，改value
### 6.1 读value的三种方式
1. operator[] -- 方便，但会写
```cpp
int v = m["apple"]; // 存在->返回value的引用；不存在->插入默认值，再返回默认值
m["apple"] = 5; // 返回的是引用，所以能直接赋值
m["apple"]++;// 也能这样改
```
它返回的是value的引用，所以可读可写。
但**不存在时会偷偷插一个默认值进去**
const map 上不能用[] (因为它可能修改map， 编译器直接拒绝)

2.at -- 安全读，不存在就报错(c++11)
```cpp
int v = m.at("apple"); // 存在->返回引用
// 不存在->抛std::out_of_range异常
```
at 和 [] 的区别：key不存在时，at抛异常，[]悄悄插一个
所以at适合"我确信这个key在，不在这个程序就是有bug"的场景--他不会污染你的map，而且能用在const map上

3.find -- 最安全的查，自己判断
```cpp
auto it = m.find("apple");
if(it != m.end()){
    cout << it->second;
}else{
    cout << "没有这个key";
}
```
find返回迭代器，找到指向那个pair，找不到返回end()
**不插入，不抛异常** 把判断权交给自己
迭代器指向的是pair，所以用it->first拿key
it->second拿value

**三者怎么选**
- 确定key在，或**接受不在时自动插入**，且要读写->operator[]
- 确定key在，不在视为错误->at
- **不确定key在不在，只想安全地查**->find(判end()),这是最常用，最稳的查法
- const map上->只能at或find，不能[]

### 6.2判断key在不在: count/contains
和set一摸一样
```cpp
if(m.count("apple")){...}
if(m.contains("apple")){...}
```
光想判断key在不在，用这俩，别用[](会插入)，也不必用find(那是要拿位置时才用)

### 6.3 遍历map
元素是pair<const Key, Value>,按key升序。最清爽的是C++17结构化绑定
```cpp
for(const auto& [key, value] : m){
    cout << key << ": " << value << "\n";
}
```
老式写法(没有结构化绑定时)用.first/.second:
```cpp
for(const auto& p : m){
    cout << p.first << " : " << p.second << "\n";
}
```
要改value就把const auto& 换成 auto&：
```cpp
for(auto& [key, value] : m){
    value*=2; // value 可以改
    // key = "new" // key是const，改不了
}
```
记住那条底色：遍历时**key永远只读(它是const)**，value是看你用const auto& 还是 auto&

### 6.4 改一个已有key的value
```cpp
m["apple"] = 10;
m.at("apple") = 10;
auto it = m.find("apple");
if(it != m.end()) it->second = 10;
```

## 7.map删除，有序操作，multimap
### 7.1删除erase
和set几乎一模一样(同一棵树)，三种形式：
```cpp
// 1.按key删，返回删掉的个数
size_t n = m.erase("apple");

// 2. 按迭代器删，返回下一个迭代器
auto nxt = m.erase(it);

// 3. 按范围删
m.erase(first, last);
```

迭代器失效规则，边遍历边删除的写法，和set一样
```cpp
for(auto it = m.begin(); it != m.end(); ){
    if(it->second < 0){
        it = m.erase(it);
    }else{
        it++;
    }
}
```
C++20一样有std::erase_if(m, 谓词)，谓词收到的是pair

### 7.2map上的有序操作
map按key有序(树按key排)，所以set那套有序操作，map全都有，只是按key来

```cpp
m.lower_bound(key); // 第一个key >= 给定值的元素
m.upper _bound(key); // 第一个key > 给定值的元素
m.equal_range(key); // 等于该key的范围
```
用途和set同构--前驱后继，范围查找，批量删区间，只不过比较的是key。
比如取出key落在[a,b]内的所有pair
```cpp
for(auto it = m.lower_bound(a); it != m.upper_bound(b);++it){
    cout << it->first << " : " << it->second << '\n';
}
```
同一个性能坑：用成员m.lower_bound(key),别用std::lower_bound

### 7.3multimap
```cpp
multimap<string, int> mm;
mm.insert({"a", 1});
mm.insert({"a", 2});
```
它与map的差别：
1. 允许重复key
2. 没有operator[]. 也没有at--因为一个key能对应好几个value，mm["a"]没有办法直接确定该返回哪一个，multimap只能靠insert/find/equal_range
3. insert总是成功(允许重复)，所以不返回bool，只返回迭代器
4. count(key) 可能大于1
5. erase（key）删除掉key所有的pair，只删一个erase(find(key));
6. equal_range 是它的主场--一次拿到某个key的所有value

```cpp
auto [lo,hi] = mm.equal_range("a");
for(auto it = lo; it != hi;++it){
    cout << it->second << " ";
}
```
用途：一个key天然要映射多个值的场景--比如一个人的多个手机号，一个标签下的多篇文章，一个分数对应的多个学生
