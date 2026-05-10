# vector(一维动态数组)
## 1.类模板的定义
1. 核心成员变量
    - 在vector底层 并没有采用size和capacity， 而是采用了三个迭代器 更加有利于迭代器遍历 区间操作等
```cpp
template <class T, class Alloc = allocator<T>>
class vector {
protected:
    iterator start;           // 指向当前可用空间的起始位置
    iterator finish;          // 指向当前已被使用的空间的尾部（最后一个元素的下一个位置）
    iterator end_of_storage;  // 指向当前整块预留堆区空间的尾部
    // ...
};
```
## 2.内存分配和对象构造的解耦
在vector中 申请内存与构造对象是分开进行的
> 这样就不会出现分配内存的时候疯狂掉哦那个默认构造函数的情况 只有在需要插入数据的时候才会调用构造函数
### size() 和 capacity()
- size() -> finish - start
- capacity() -> end_of_storage - start

### reserve()与resize()
- reserve(n) : 只操作容量
  - 底层行为：只改变end_of_storage的位置
  - 关键：不会调用构造函数
  - 适用场景：提前已经知道要放入多大数据时 调用reserve可以避免很多自动扩容
  - ++警告++：“严禁对 reserve 出来的未初始化裸内存使用 operator[] 进行赋值。
- resize(n) : 同时操作容量和大小
  - 底层行为：同时移动finish和end_of_storage
  - 反向行为：如果n小于size()它会从尾部开始调用析构函数销毁对象 移动finish的位置

### 扩容机制
1. 开辟新内存（1.5或者2倍）
2. 拷贝
3. 析构旧内存的对象
4. 归还内存
5. 指针重定位

## 插入
1. push_back(item); O(1)
    1. 在外部创建一个对象item
    2. vector接收到这个对象
    3. vector在堆区的finish位置，调用拷贝构造函数或者移动构造函数，把外部的对象复制或者移动到自己的地盘里
2. emplace_back(参数1，参数2) O(1)
    1. 不在外部创造对象 而是只把创建对象的原材料传给vector
    2. vector在finish位置 利用这些参数原地调用构造函数

## 删除
1. pop_back() O(1)
   1. 销毁finish-1的位置的对象(调用析构函数),然后执行--finish
   2. 内存并没有归还，end_of_storage没动，意味着capacity没变
2. earse(iterator) O(n)
   1. 删除iterator指向的元素 并将后面的元素移动

## 退还内存(内存收缩)
> 即便用clear()删除了所有元素 capacity一九会保持原有的大小
1. 方案1 ：调用vec.shrink_to_fit(),这会请求系统减小capacity以匹配size
2. 方案2 ：std::vector<T>(vec).swap(vec);
    - 即利用vec创造一个临时的刚好够大的副本 然后交换两者的内部指针。当临时副本在行末销毁时，它带走了原本巨大的旧内存

## 迭代器失效
在vector发生自动扩容时 内存发生了重新分配，原本手中的迭代器会指向一块已经被还给操作系统的非法地址
### 两种经典场景
1. 扩容导致
    - 在push_back,insert时触发了扩容，所偶有迭代器，指针，引用会立即失效
2. 平移导致
    - 如果在vector中间erase了一个元素 删除之后的所有元素都会向前平移，这意味着删除点及其之后的所有迭代器都失效了
解决：在使用 erase 删除元素时，必须手动接收它返回的全新有效迭代器（例如 it = vec.erase(it);），并且在成功删除的分支中，严禁再执行 ++it，以防漏删元素。

## vector<bool> 特殊情况
c++模板库对bool类进行了一个模板特化
> 在正常的c++中一个bool变量为了班组内存对齐和寻址的需求 通常会占用1个字节 但是开发者认为01却要占8个字节 太浪费空间于是进行了改造 把8个布尔值强行塞进一个字节里
1. 优点 ：极致的空间压缩
2. 代价 ：彻底丧失了作为标准STL容器的资格

在现代CPU中最小可寻址单元时字节这意味着无法拿到第三个bit这样的物理内存
后果：无法获取vector<bool>中元素的真实指针或引用 

**非必要，绝不用vector<bool>**
# vector<vector<int>> （二维动态数组）
1. 底层内存空间
   1. 二维vector不是连续的
      1. 外层Vector: 在堆区分配一块连续内存，里面存了三个内部vector对象
      2. 内层Vector：各自独立地进行空间配置器申请了存放4个int地堆内存
   2. 这种不连续地内存会导致CPU缓存命中率吧变低 遍历时效率大幅下降
   3. 分配和析构开销变大
2. 解决方案：不使用vector<vector<T>>
   - 借助一维vector模拟二维矩阵
```cpp
class Matrix2D {
private:
    std::vector<int> data;
    int rows;
    int cols;

public:
    Matrix2D(int r, int c) : rows(r), cols(c) {
        // 只进行 1 次底层内存分配！绝对连续！
        data.resize(r * c, 0); 
    }

    // 核心寻址公式：row * cols + col
    int& at(int r, int c) {
        return data[r * cols + c];
    }
};
```
