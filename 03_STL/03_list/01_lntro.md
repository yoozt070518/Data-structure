# list
- 底层数据结构：双向的循环链表 pre data next
list<int> mylist;
## 增加
mylist.push_back(20);  末尾添加元素 O(1)
mylist.push_front(20); 从首部添加元素 O(1)
mylist.insert(it,20); it指向的位置添加元素O(1) 
    但链表中进行insert的时候 先要进行一个query查询操作
    对链表来说查询效率比较低

## 删除
mylist.pop_back(); 末尾删除元素 O(1)
mylist.pop_front(); 从首部删除元素 O(1)
mylist.erase(it); 从it指向的位置删除元素 O(1)

## 查询操作：
iterator(连续的insert和erase一定要考虑迭代器时效问题)