# vector常用函数
## 1. 构造与初始化 (Constructors)
- vector<int> v;
    - 效果：创建一个空的 vector。
    - 底层：此时**并未分配堆区内存**（capacity 为 0）。

- vector<int> v(10, 5);
    - 效果：创建一个包含 10 个元素，且每个元素初始值都为 5 的 vector。

- vector<int> v = {1, 2, 3, 4, 5};
    - 效果：使用 C++11 列表初始化。

- vector<int> v2(v.begin(), v.end());
    -效果：利用另一个容器的迭代器区间进行初始化（**前闭后开** [begin, end)）。

## 2. 容量与内存管理 (Capacity)
- size_t size() const;
    - size_t是一个无符号整形
    - 效果：返回当前容器中**真实存在的数据个数**
- size_t capacity() const;
    - 效果：返回当前容器在不发生重新分配的情况下，**最多能容纳的元素个数**

- bool empty() const;
    - 效果；判断容器是否为空(利用的是finish-start迭代器)

- void reserve(size_t n);
    - 效果：向操作系统强行申请至少能容纳n个元素的底层连续内存(**只改变capacity,不改变size，不构造对象**)
    - 场景：当你知道接下来要插入10万数据时 提前reserve(1000000),可以避免这10万次插入过程中的频繁扩容和数据搬迁灾难

- void resize(size_t n ,val);
    - 效果：强行把当前数据的个数(size)变成n。如果变长了，多出来的位置用val填充(并调用构造函数);如果变短了，多余的元素被截断销毁(调用析构函数)
    - 注意：**不会改变capacity**

## 3. 元素访问 (Element Access)
- v[i] (下标访问)
    - 代价：O(1)。极速的指针偏移。**绝不进行越界检查**，越界直接导致未定义行为（通常是段错误）。

- v.at(i) (安全访问)
    - 代价：O(1)。比 [] 稍微慢一点点，因为它**强制进行越界检查**。如果越界，会抛出 std::out_of_range 异常。

- T& front(); / T& back();
    - 效果：返回第一个 / 最后一个元素的**引用**。注意：对空容器调用会崩溃。

- T* data(); (C++11)
    - 效果：返回指向底层连续内存的首地址（即原生指针）。
    - 场景：当你需要把 vector 里的数据传给底层的 C 语言老接口（比如 memcpy 或操作系统 API）时，直接传 v.data() 即可。

## 4. 插入与修改
- void push_back(const T& val);
    - 效果：在尾部追加元素
    - 代价：均摊O(1) 如果恰好容器满了，会触发极其昂贵的O(N)级别全量内存搬迁（所有迭代器失效）
- void pop_back();
    - 效果：销毁尾部元素，size 减 1。
    - 代价：绝对 O(1)。不会引发缩容。

- iterator insert(const_iterator pos, const T& val);
    - 效果：在迭代器 pos 之前插入一个元素。
    - 代价：O(N)。因为 vector 是绝对连续的，插入点之后的所有元素都必须往后平移腾出位置。（如果在头部 insert，就是最灾难的 O(N)）。

- iterator erase(const_iterator pos); 
- iterator erase(const_iterator first, const_iterator last);
    - 效果：删除指定位置的元素，或删除一个区间的元素。
    - 代价：O(N)。删除点之后的所有数据必须往前平移填补空缺。注意：返回的是被删除元素之后的那个新迭代器。

- void clear();
    - 效果：清空所有元素（调用所有元素的析构函数，size 变为 0）。
    - 陷阱：clear() 绝对不会释放底层的物理内存！也就是 capacity 保持不变。

## c++11新特性
- emplace_back(参数1，参数2) O(1)
    1. 不在外部创造对象 而是只把创建对象的原材料传给vector
    2. vector在finish位置 利用这些参数原地调用构造函数
    - 效果：功能类似于 push_back，也是在尾部追加。
    - 底层原理：push_back 是在外面先造好一个对象，然后拷贝/移动进容器；而 emplace_back 是直接把构造函数的参数传进底层，在容器的内存里原地构造对象。
    - 结论：只要能用 emplace_back 就不要用 push_back，它可以省去一次无意义的拷贝/移动构造函数的调用开销。