# list
## 1.构造与初始化 (Constructors)
- list<int> lst;(空链表，仅仅=创建Dummy Node虚节点)

- list<int> lst(10,5);
- list<int> lst = {1, 4, 5};
    - 效果与前两者一致，注意：如果是初始化区间，底层是挨个new出节点并串起来的

## 2.容量与内存管理
- size_t size() const;
- bool empty() const;
    - 代价：c++11之后强制规定size()为O(1),底层用一个额外的计数器变量维护

- void resize(size_t n, val);
    - 注意：**list没有capacity()和reserve()**
    - 底层真相：因为list每次插入都是向操作系统独立申请一个节点的内存，它永远都不需要练的的一大块内存，也不存在扩容搬迁的概念

## 3.元素访问
- T& front();
- T& back();
    - 代价：O(1)。back()本质上就是返回Dummy Node的prev指向的节点数据

- 注意：**没有operator[] 也没有at()**
    - 原因：它不支持随机访问迭代器。如果允许写lst[5], 底层必须从头节点开始走五步，时间复杂度到了O(n),为了防止程序员误以为下标访问很快而写出灾难性的代码，c++强行剥夺了这个API
- 注意：**没有data()**
    - 原因：内存散落在堆区的各个角落，完全不是连续的

## 4.常规插入与删除
- push_back();
- pop_back();
- push_front();
- pop_front();
    - 代价：均为O(1)纯粹的指针重连

- iterator insert(const_iterator pos, const T& val);
    - 代价：在指定迭代器前插入。插入本身是O(1)
    - 安全契约：插入后，没有任何迭代器会失效
- iterator erase(const_iterator pos);
    - 代价：删除动作本身是O(1)
    - 安全契约：除了被删除的那个节点的迭代器失效外，其余所有迭代器安然无恙。

## 5.专属大招
- splice
    1. 把整个链表都搬走 
       - void splice(const_iterator pos, list& other);
          - pos:目标链表的一个迭代器，它决定了拼接到哪里，数据会精准地插入到这个迭代器所指元素地前面
          - other:要掏空的链表
    2. 只搬运链表里的“单个节点”
       - void splice(const_iterator pos, list& other, const_iterator it);
         - pos:目标位置（前面）
         - other：源链表对象
         - it:other的一个有效迭代器 代表要精准切下哪一个节点
    3. 搬运源链表里的一段区间
       - void splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
         - 左闭右开区间
注：版本2，3可以用来对链表进行自身移动

- void remove(const T& val)
- void remove_if(Predicate pred);
    - 效果：遍历链表，把等于val或者满足pred，物理剪除并delete删除释放内存。O(n)
    - 此处的Predicate是一个占位符 它可以是一个bool函数 也可以是仿函数，Lambda表达式之类的类bool函数

- void unique();
    - 效果：移除相邻的重复节点，只保留一个。如果要全局去用，必须先调用sort。O(N)

- void merge(list& other);
    - 效果：将另一个已经有序的链表合并到自己身上，合并后依旧有序。other链表会被抽空O(N)

- void sort();
    - 效果：非递归的归并排序。纯粹的指针重连，零数据拷贝。O(nlogn)

- void reverse();
    - 效果：将整个链表倒置
    - 底层：极速O(n).他不是将数据对调，而是将每一个节点的prev和next互换
