# C++ Queue（队列）知识总结

## 1. 什么是 Queue

Queue（队列）是一种 **先进先出（FIFO，First In First Out）** 的数据结构。

也就是说：

- 最先进入队列的元素
- 会最先离开队列

就像：

- 排队买饭
- 排队上车
- 打印任务队列

---

## 2. Queue 的特点

| 特点 | 说明 |
|---|---|
| 先进先出 | 先进去的先出来 |
| 只能尾部插入 | push |
| 只能头部删除 | pop |
| 不支持随机访问 | 不能像数组一样 queue[0] |

---

# 3. 头文件

```cpp
#include <queue>
```

---

# 4. 创建 Queue

```cpp
queue<int> q;
```

这里：

- `int`
  表示队列中存储的数据类型

---

# 5. 常用操作

---

## （1）push()

向队尾加入元素

```cpp
q.push(10);
q.push(20);
q.push(30);
```

队列：

```text
队头 -> 10 20 30 <- 队尾
```

---

## （2）pop()

删除队头元素

```cpp
q.pop();
```

注意：

- `pop()` 没有返回值
- 只是删除

删除后：

```text
队头 -> 20 30 <- 队尾
```

---

## （3）front()

访问队头元素

```cpp
cout << q.front();
```

输出：

```text
20
```

---

## （4）back()

访问队尾元素

```cpp
cout << q.back();
```

输出：

```text
30
```

---

## （5）empty()

判断队列是否为空

```cpp
if(q.empty()){
    cout << "空";
}
```

返回：

| 返回值 | 含义 |
|---|---|
| true | 空 |
| false | 不空 |

---

## （6）size()

获取队列元素数量

```cpp
cout << q.size();
```

---

# 6. Queue 完整示例

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main(){

    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << "队头: " << q.front() << endl;
    cout << "队尾: " << q.back() << endl;

    q.pop();

    cout << "pop后队头: " << q.front() << endl;

    cout << "队列大小: " << q.size() << endl;

    return 0;
}
```

---

# 7. Queue 遍历

queue 不能随机访问。

因此：

```cpp
q[i]
```

这种写法是错误的。

---

## 正确遍历方法

### 方法：

不断：

- 取队头
- 输出
- 删除

---

## 示例

```cpp
while(!q.empty()){

    cout << q.front() << " ";

    q.pop();
}
```

输出：

```text
10 20 30
```

注意：

遍历后队列会被清空。

---

# 8. queue 的底层

C++ STL 中：

```cpp
queue
```

默认底层是：

```text
deque（双端队列）
```

实现的。

---

# 9. queue 和 stack 的区别

| 数据结构 | 特点 |
|---|---|
| stack | 后进先出（LIFO） |
| queue | 先进先出（FIFO） |

---

## stack

```text
1 2 3

先出3
```

---

## queue

```text
1 2 3

先出1
```

---

# 10. 常见错误

---

## （1）空队列访问 front()

错误：

```cpp
q.front();
```

如果队列为空：

会发生运行错误。

---

## 正确写法

```cpp
if(!q.empty()){
    cout << q.front();
}
```
# 11. 一句话总结

```text
queue：
先进先出（FIFO）

push尾部加入
pop头部删除
```