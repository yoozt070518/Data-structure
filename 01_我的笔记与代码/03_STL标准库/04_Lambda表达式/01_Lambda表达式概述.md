# C++11 Lambda 表达式：核心机制与实战指南

## 1. 什么是 Lambda 表达式？
Lambda 表达式是 C++11 引入的一种**匿名函数（Anonymous Function）**。
它允许你在需要函数指针或仿函数（Functor）的地方，直接“就地”编写一段逻辑代码，而不需要跑到外部去额外定义一个正式的函数或类。它是极度简化的语法糖。

## 2. 核心语法结构
Lambda 的完整语法形态如下（大部分情况下可以省略某些部分）：
`[捕获列表](参数列表) mutable -> 返回值类型 { 函数体 }`

*   **`[]` 捕获列表 (Capture Clause)**：**（灵魂所在）** 将外部作用域的变量“抓”到匿名函数内部使用。
*   **`()` 参数列表 (Parameter List)**：和普通函数的参数一样（如 `int a, int b`）。如果不需要参数，`()` 可以省略。
*   **`mutable` 关键字**：默认情况下，按值捕获的变量在 Lambda 内部是只读的。加了 `mutable` 就可以修改它们（注意：只修改副本，不影响外部原变量）。通常省略。
*   **`->` 返回值类型 (Trailing Return Type)**：绝大多数情况下可以省略，编译器会根据 `return` 语句自动推导（`auto`）。
*   **`{}` 函数体 (Body)**：具体的执行逻辑。

**最简形态**：`[]{}` （什么都不捕获，没参数，啥也不干）。

## 3. 灵魂机制：捕获列表 (Capture List)的六种形态
普通函数最大的弱点是“无法携带状态”，而捕获列表解决了这个问题，搭建了外部变量进入匿名函数内部的桥梁。

1.  **`[]` (空捕获)**：什么都不抓。内部只能使用全局变量或传入的参数。
2.  **`[x, y]` (显式值捕获)**：将外部的 `x` 和 `y` **拷贝**一份到函数内部。内部无法修改外部的原变量（除非加 `mutable` 修改副本）。
3.  **`[&x, &y]` (显式引用捕获)**：将外部的 `x` 和 `y` 按**引用**抓进来。在内部修改它们，外部的真实变量也会同步改变。（极其常用，可避免大对象拷贝开销）。
4.  **`[=]` (隐式全值捕获)**：极度偷懒的写法。编译器会自动扫描函数体，把你用到的外部变量全部按**值拷贝**进来。
5.  **`[&]` (隐式全引用捕获)**：偷懒写法。把你用到的外部变量全部按**引用**抓进来。
6.  **`[=, &x]` (混合捕获)**：除了 `x` 按引用捕获，其他的全部按值拷贝。

## 4. 底层物理真相：编译器到底做了什么？
Lambda 并不是什么魔法，它的底层本质就是我们讲过的**仿函数（Functor）**。

当你写下这段代码：
```cpp
int threshold = 10;
auto myLambda = [threshold](int n) { return n > threshold; };
```

C++ 编译器在底层会默默把它翻译成一个**匿名的类**：
```cpp
// 编译器偷偷生成的类
class __Lambda_Anonymous_xxxxx {
private:
    int threshold; // 捕获列表里的变量，变成了类的成员变量！
public:
    // 构造函数：负责把外部的值拷贝进来
    __Lambda_Anonymous_xxxxx(int t) : threshold(t) {} 

    // 重载 operator()
    bool operator()(int n) const {
        return n > threshold;
    }
};

// 你写的 auto myLambda 其实是实例化了这个类的对象
__Lambda_Anonymous_xxxxx myLambda(threshold);
```
**结论**：按值捕获，就是生成成员变量拷贝；按引用捕获，就是生成引用类型的成员变量。Lambda 是一次极其完美的编译器语法包装。

## 5. 工业实战场景：配合 STL 算法
在 `vector`、`list` 等容器配合 `<algorithm>` 库使用时，Lambda 是绝对的主力。

### 场景 1：自定义排序 (`std::sort`)
```cpp
std::vector<int> v = {5, 2, 8, 1, 9};
// 降序排列
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b; 
});
```

### 场景 2：带外部状态的条件删除 (`std::remove_if`)
```cpp
std::list<int> lst = {10, 25, 30, 45, 50};
int limit = 30; // 外部变量

// 删除所有严格大于 limit 的元素（引用捕获 limit，避免拷贝）
lst.remove_if([&limit](int n) {
    return n > limit;
});
```

### 场景 3：条件查找 (`std::find_if`)
```cpp
std::vector<int> v = {1, 3, 5, 8, 9};
// 查找第一个偶数
auto it = std::find_if(v.begin(), v.end(), [](int n) {
    return n % 2 == 0;
});
```