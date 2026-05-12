# deque
## 1.构造与初始化
- deque<int> dq;
    - 效果：空 deque。
    - 底层：分配一个初始的 map 中控器数组，并通常会默认分配一个初始的缓冲区（Buffer），以备随时头插或尾插。

- deque<int> dq(10, 5);
- deque<int> dq = {1, 2, 3};
- deque<int> dq(v.begin(), v.end());
    - 效果：同 vector。

## 2. 容量与内存管理 (Capacity)
- size_t size() const;
- bool empty() const;
    - 代价：$O(1)$。

- void resize(size_t n, val);
    - 效果：同 vector，变长则填充，变短则截断。
    - ❌ 绝对禁区：deque 没有 capacity()，也没有 reserve()！
        - 硬核拷问（为什么没有？）：vector 需要 reserve 是因为它内存是连续的一条龙，满了必须搬家。而 deque 是分段连续的，满了只需要向操作系统申请一小块新的 Buffer，然后把指针挂在中控器 map 上即可，永远不需要全量搬迁数据。既然没有全量搬迁的灾难，自然就不需要 capacity() 来预警，也不需要 reserve() 来提前占位。
## 3. 元素访问 (Element Access)
- dq[i] (下标访问)
- dq.at(i) (安全访问)
    - 代价：常数级别 $O(1)$，但常数很大！
    - 底层真相：虽然它是 $O(1)$，但底层必须经过两次计算：先通过 (offset + i) / Buffer大小 算出该去中控器找哪个指针，再通过 (offset + i) % Buffer大小 算出在 Buffer 内的槽位。这比 vector 纯粹的连续指针偏移要慢好几倍。

- T& front();
- T& back();
    - 代价：绝对的 $O(1)$。
    - ❌ 绝对禁区：deque 没有 data() 函数！原因：data() 要求返回一整块连续内存的首地址。deque 的数据是切碎在多个 Buffer 里的，根本交不出一块连续的物理内存。所以如果你要调用 C 语言老接口，绝不能用 deque。

## 4. 头尾与中间的修改 (Modifiers) —— deque 的核心战场
- void push_back(const T& val);
- void pop_back();
    - 代价：代价：绝对 $O(1)$。

- ✨ 独门绝技：
- void push_front(const T& val);
- void pop_front();
    - 代价：绝对的$O(1)$
    - 对比 vector：如果对 vector 进行头插（insert(begin(), val)），需要把所有元素往后推，代价是灾难性的 $O(N)$。而 deque 只需在最前面的 Buffer 写数据，或者申请一个新 Buffer 挂在前面，轻而易举。

- iterator insert(const_iterator pos, const T& val);
    - 代价：$O(N)$。
    - 底层细节：在中间插入时，deque 会极其聪明地计算插入点离头部近还是离尾部近。它会选择距离较短的那一端进行跨 Buffer 的数据平移，以尽量减少拷贝次数。（但即便如此，平移依然很慢）。
    - 
- iterator erase(const_iterator pos);  
    - 代价：$O(N)$。同样会自动选择挪动较短的一端。
- void clear();
    - 效果：清空所有数据。通常会释放大部分 Buffer，但会保留至少一个 Buffer 和中控器以备后用。

## 5. C++11 新特性
- emplace_front, emplace_back, emplace
    - 效果：同 vector，传参原地构造，省去拷贝/移动构造函数的开销。