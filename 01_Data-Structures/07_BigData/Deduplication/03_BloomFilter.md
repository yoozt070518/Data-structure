# 布隆过滤器
> 位图有一个缺点--数字范围必须已知，而且只能处理整数
> 如果键是字符串呢？比如判断一个URL有没有被爬取过，URL是字符串，范围无限，位图装不下

布隆过滤器的思路是：
- 用多个哈希函数， 把一个键映射到位图的多个位置，全部置为1
- 查询时，检查这几个位置是不是全是1：
    1. 全是1 -> 可能存在
    2. 有一个是0 -> 一定不存在

## 操作思路：
1. 增加元素：
    1. 经过k个哈希函数计算，得到bitmap位数组里面的一组位的序号
    2. 把相应的位置变成1
2. 搜索一个元素
    1. 经过k个哈希函数计算，得到bitmap位数组里面的一组位的序号
    2. 判断上面的几个位置的值 如果全是一 证明相应的key存在，如果有一个是0，则证明key不在bloom filter中
注 ：**不可提供删除**
原因： 不同的key，经过k个哈希函数计算后，可能共用一些位
## 实现
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int SIZE = 1000;

void set(int* bitmap, int n) {
    int idx = n / 32;
    int bit = n % 32;
    bitmap[idx] |= (1 << bit);
}

bool get(int* bitmap, int n) {
    int idx = n / 32;
    int bit = n % 32;
    return bitmap[idx] & (1 << bit);
}

int hash1(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 31 + c;
    return abs(h) % SIZE;
}

int hash2(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 37 + c;
    return abs(h) % SIZE;
}

int hash3(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 41 + c;
    return abs(h) % SIZE;
}

void insert(int* bitmap, const string& s) {
    set(bitmap, hash1(s));
    set(bitmap, hash2(s));
    set(bitmap, hash3(s));
}

bool contains(int* bitmap, const string& s) {
    return get(bitmap, hash1(s)) &&
           get(bitmap, hash2(s)) &&
           get(bitmap, hash3(s));
}

int main() {
    int bitmap[SIZE / 32 + 1];
    memset(bitmap, 0, sizeof(bitmap));

    insert(bitmap, "apple");
    insert(bitmap, "banana");
    insert(bitmap, "cherry");

    cout << contains(bitmap, "apple")  << "\n";  // 1
    cout << contains(bitmap, "banana") << "\n";  // 1
    cout << contains(bitmap, "grape")  << "\n";  // 0（大概率）
}
```


## 核心缺点--误判
- "grape"输出了0 ，说明它一定不存在，这是准确的
- 但是有可能某个没插入过的字符串，它的三个哈希位置恰好都被别的字符串占了，就会输出1，但它其实根本没有插入过， 这就是误判

## 使用场景
宁可误判存在，也不能漏掉不在的场景
1. 爬虫判断URL有没有爬取过，误判“爬过了”最多重复爬一次，但漏掉“没爬过”就永远错过了
2. 垃圾邮件过滤，误判“是垃圾邮件”最多误伤一件正常邮件，但漏掉垃圾邮件就没有意义了
3. 数据库查询前先过滤，判断数据一定不存在就不用去磁盘查了 节省大量IO

## 误判率怎么降低？
1. 增大位图：SIZE越大，碰撞越少
2. 增加哈希函数：每个键占用的位越多，误判概率越低