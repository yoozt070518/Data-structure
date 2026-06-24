# 现代 C++ 完整知识点清单（基础阶段 / 路线阶段一）

> 这是一份**知识点地图**，目的只有一个：**确保不漏**。
> 它对应学习路线里的「阶段一：现代 C++ + 面向对象 + 多线程 + 工具链」，是那一阶段的**详细展开**（时长安排见路线文件，这里只管知识点齐不齐）。

---

## 怎么用这份清单

1. **学过的勾掉（`[x]`），没见过的就是该补的。** 你已经能熟练写 C++（手写过红黑树、用过 STL），所以本清单**默认你已掌握 C++ 基本语法**（变量、控制流、函数、指针、引用、数组、基本 I/O），不再列这些，专门聚焦**类、现代特性、STL、并发、工程**这些进阶且容易漏的内容。
2. **模块是有先后逻辑的**：模块一到八大致由浅入深、由语言到工程，建议按顺序学（后面的常依赖前面的）。
3. **标注说明**：`[C++11/14/17/20]` 表示该特性从哪个标准引入；`★` 表示重点或难点，要花更多力气。
4. 学的时候照旧用你的 `原理 → 实现 → API → 实践` 那套；每个知识点都该能写出能跑的小例子。

---

## 模块一：类与面向对象（OOP）

### 1.1 类的基本机制
- [ ] 成员变量 / 成员函数、访问控制 `public`/`private`/`protected`、`this` 指针
- [ ] 构造函数：默认构造、带参构造、**成员初始化列表**（member initializer list，及为什么它比函数体内赋值好）
- [ ] 委托构造 delegating constructor `[C++11]`
- [ ] `explicit` ★（禁止隐式转换，防止意外的单参构造被当成转换）
- [ ] 析构函数 destructor
- [ ] **const 正确性** ★：`const` 成员函数、`const` 对象能调什么、`mutable`
- [ ] `static` 成员（静态成员变量 / 静态成员函数、类内声明类外定义）
- [ ] `friend` 友元（函数 / 类）

### 1.2 拷贝与移动（资源管理的核心）★
- [ ] 拷贝构造函数 copy constructor、拷贝赋值运算符 copy assignment
- [ ] **深拷贝 vs 浅拷贝**（管理裸资源时为什么必须深拷贝）
- [ ] **Rule of Three**（有析构/拷贝构造/拷贝赋值之一，往往三个都要写）
- [ ] 移动构造、移动赋值 `[C++11]`、**Rule of Five**
- [ ] `= default` / `= delete`（显式要求或禁用某个特殊成员函数）
- [ ] **Rule of Zero**（尽量用能自我管理的成员，从而一个特殊函数都不用手写）

### 1.3 运算符重载（operator overloading）
- [ ] 算术运算符 `+ - * /`、复合赋值 `+= -=` 等
- [ ] 比较运算符 `== != < >` 等
- [ ] 赋值运算符 `=`（和拷贝/移动赋值的关系）
- [ ] 下标 `[]`、函数调用 `()`（**仿函数 functor**，STL 里到处用）
- [ ] 流插入 / 提取 `<<` `>>`（自定义类型的输入输出）
- [ ] 自增自减 `++` `--`（前置 / 后置的区别）
- [ ] 解引用 `*` 与成员访问 `->`（写智能指针 / 迭代器要用）
- [ ] 类型转换运算符 conversion operator
- [ ] 三向比较运算符 `<=>`（spaceship）`[C++20]`

### 1.4 继承与多态 ★
- [ ] 继承、继承的访问控制、**构造 / 析构的调用顺序**
- [ ] 虚函数 `virtual`、`override` / `final` `[C++11]`（为什么要写 `override`）
- [ ] 纯虚函数 pure virtual、抽象类 abstract class、接口的表达
- [ ] **虚析构函数** ★★（多态基类必须有，否则 `delete` 基类指针时派生类析构不被调用 → 内存泄漏）
- [ ] `vtable` / `vptr` 原理（虚函数怎么实现的，你之前接触过）
- [ ] **对象切片** object slicing（按值传基类时派生部分被切掉）
- [ ] 多重继承 multiple inheritance
- [ ] 虚继承 virtual inheritance、**菱形继承问题** diamond problem

### 1.5 运行期类型信息
- [ ] RTTI、`typeid`
- [ ] `dynamic_cast`（向下转型，失败返回 `nullptr` / 抛异常）
- [ ] **四种类型转换** ★：`static_cast` / `dynamic_cast` / `const_cast` / `reinterpret_cast`（各自用途、为什么不用 C 风格强转）

---

## 模块二：内存与资源管理

### 2.1 裸内存
- [ ] `new` / `delete`、`new[]` / `delete[]`（为什么不能混用）
- [ ] **栈 vs 堆**（生命周期、分配释放、各自代价）
- [ ] 内存泄漏 memory leak、悬空指针 dangling pointer、double free
- [ ] placement new（在已分配内存上构造对象，了解）
- [ ] 内存对齐 alignment、`alignof` / `alignas`（了解，性能 / 底层会用）

### 2.2 RAII 与智能指针 ★
- [ ] **RAII** ★★（资源获取即初始化——C++ 资源管理的根本思想，你写红黑树的内存释放其实就在边缘）
- [ ] `unique_ptr`（独占所有权）、`make_unique` `[C++14]`
- [ ] `shared_ptr`（共享所有权、引用计数）、`make_shared`
- [ ] `weak_ptr`（不增加计数的弱引用）
- [ ] **循环引用问题** ★（两个 `shared_ptr` 互指导致永不释放）与用 `weak_ptr` 破环
- [ ] 自定义删除器 custom deleter

---

## 模块三：现代 C++ 语言特性（C++11/14/17/20）

### 3.1 类型推导与初始化
- [ ] `auto` 类型推导（及它会丢掉 `const`/引用的细节）
- [ ] `decltype`、`decltype(auto)` `[C++14]`
- [ ] 列表初始化 `{}`、统一初始化 uniform initialization
- [ ] `std::initializer_list`（自定义类型支持 `{...}` 初始化）
- [ ] 聚合初始化 aggregate init、指定初始化 designated initializers `[C++20]`
- [ ] `nullptr`（取代 `NULL`）、范围 for range-based for

### 3.2 右值与移动语义 ★★（重点难点）
- [ ] 左值 lvalue / 右值 rvalue / 将亡值 xvalue 的区分
- [ ] 右值引用 `&&`
- [ ] `std::move`（它本身不移动，只是转成右值）、移动语义到底省了什么
- [ ] **完美转发** perfect forwarding、`std::forward`、引用折叠、万能引用（forwarding reference）
- [ ] `noexcept` ★（为什么移动操作通常要标 `noexcept`，不然容器可能退回拷贝）
- [ ] 拷贝消除 copy elision、RVO / NRVO（返回值优化）

### 3.3 lambda 与可调用对象
- [ ] lambda 表达式、**捕获** capture（值捕获 / 引用捕获 / 混合、`[=]` `[&]` 的坑）
- [ ] init capture（广义捕获，可移动捕获）`[C++14]`
- [ ] `mutable` lambda、泛型 lambda generic lambda `[C++14]`
- [ ] 闭包 closure 的本质（lambda 其实是个带 `operator()` 的匿名类）
- [ ] `std::function`（统一存储各种可调用对象）、`std::bind`

### 3.4 枚举与编译期
- [ ] `enum class` 强类型枚举 ★（比传统 `enum` 安全，不会隐式转 int、不污染命名空间）
- [ ] `constexpr`（编译期常量 / 函数）、`consteval` `[C++20]`
- [ ] `if constexpr` `[C++17]`（编译期分支，写模板时极有用）

### 3.5 实用工具类型（C++17，工程天天用）
- [ ] **结构化绑定** structured bindings `[C++17]`（你已经在用 `auto [it, ok]`）
- [ ] `std::optional`（可能有值可能没有，替代「用特殊值表示无」）
- [ ] `std::variant`（类型安全的联合体）、`std::any`
- [ ] `std::string_view` ★（不拷贝的字符串视图，传参高效）

---

## 模块四：STL 深入

> 你已经学过容器/迭代器/lambda/适配器，这里查漏补全 + 加深。

- [ ] 序列容器：`vector` / `deque` / `list` / `array` / `forward_list`（各自底层与**选用场景**）
- [ ] `vector` 深入：容量 capacity vs size、扩容机制、`reserve`、迭代器失效规则
- [ ] 关联容器：`set` / `map` / `multiset` / `multimap`（**你已学完**）
- [ ] 无序容器：`unordered_*`（**你已学过对比**）
- [ ] 容器适配器：`stack` / `queue` / `priority_queue`（**你学过**）
- [ ] 迭代器：**五种迭代器类别** ★（input/output/forward/bidirectional/random-access）及其能力差异
- [ ] 算法库 `<algorithm>`：`sort` / `find` / `find_if` / `for_each` / `transform` / `copy` / `remove` / `unique` / `accumulate` 等常用算法
- [ ] `<numeric>`、`<functional>`
- [ ] `emplace` vs `insert`（就地构造省一次拷贝，你在 set/map 里见过）
- [ ] 移动语义在容器中的作用（为什么 `push_back(std::move(x))` 更快）

---

## 模块五：异常与错误处理

- [ ] `try` / `catch` / `throw` 基本机制
- [ ] 标准异常层次：`std::exception` 及其派生（`runtime_error` / `logic_error` / `out_of_range` 等）
- [ ] **异常安全保证** ★：基本保证 basic / 强保证 strong / 不抛保证 nothrow
- [ ] **RAII 是异常安全的基石** ★（栈展开 stack unwinding 时析构函数自动释放资源）
- [ ] `noexcept` 说明符与 `noexcept` 运算符
- [ ] 错误处理的其它路线：错误码、`std::optional`、`std::expected` `[C++23]`（了解趋势）

---

## 模块六：模板与泛型编程（进阶）★

- [ ] 函数模板 function template、类模板 class template
- [ ] 模板参数：**类型参数 / 非类型参数 / 模板模板参数**
- [ ] 模板特化：全特化 full specialization、**偏特化** partial specialization
- [ ] 变参模板 variadic templates ★、参数包 parameter pack
- [ ] 折叠表达式 fold expressions `[C++17]`
- [ ] 模板元编程入门：**SFINAE** ★、`type_traits`、`std::enable_if`、`if constexpr`
- [ ] **concepts 与约束** `[C++20]` ★（给模板参数加约束，报错信息友好得多）
- [ ] 模板的编译模型（为什么模板通常要写在头文件里）

---

## 模块七：多线程与并发 ★

- [ ] `std::thread`、`join` / `detach`、传参与返回
- [ ] 互斥锁：`mutex`、`lock_guard`、`unique_lock`、`scoped_lock` `[C++17]`、`recursive_mutex`
- [ ] **读写锁** `shared_mutex` `[C++17]`（多读单写）
- [ ] 条件变量 `condition_variable` ★（等待 / 通知、虚假唤醒 spurious wakeup、为什么要配合谓词）
- [ ] **原子操作** `std::atomic` ★、**内存序** `memory_order` ★★（难点，先会用 `atomic` 再深究内存序）
- [ ] 异步：`std::future` / `std::promise` / `std::async` / `packaged_task`
- [ ] `thread_local` 线程局部存储
- [ ] **并发问题** ★：数据竞争 data race、死锁 deadlock、活锁、避免策略（锁顺序、RAII 锁）
- [ ] `[C++20]`：`jthread`（自动 join）、`latch` / `barrier` / `counting_semaphore`、协程 coroutines（了解即可）

---

## 模块八：工程基础与工具链

> 这些不是「语言」，但缺了它你写不出 / 调不动真实项目，之前的概要里几乎没提，重点补。

- [ ] **编译链接全过程** ★：预处理 → 编译 → 汇编 → 链接，各阶段干什么
- [ ] 声明 vs 定义、**头文件的正确组织**、include guard / `#pragma once`
- [ ] **ODR** 一次定义规则 ★（违反它的链接错误是新手噩梦）
- [ ] `namespace` 命名空间（避免名字冲突、`using` 的恰当用法）
- [ ] 静态库 `.a` / 动态库 `.so`、链接方式
- [ ] 预处理器：宏 `#define`、条件编译 `#ifdef`（及宏的危险、为什么现代 C++ 尽量少用宏）
- [ ] **构建系统** ★：CMake（重点）、Makefile
- [ ] **调试** ★：GDB（断点、单步、看变量、看调用栈）
- [ ] **版本控制** ★：Git（你做项目必须熟练）
- [ ] **Sanitizers** ★：AddressSanitizer（内存错误）、UBSan（未定义行为）、ThreadSanitizer（数据竞争）——查 bug 的神器
- [ ] 编译器警告：`-Wall -Wextra`，把警告当错误对待的习惯

---

## 配合学习路线怎么走

- 这份清单是阶段一的**知识点全集**，对应路线里大约 **6-8 个月**那一段。
- 一个合理的吃法：**模块一 → 二 → 三**（类 + 内存 + 现代特性，这是 C++ 进阶的主干，约前半段）→ **模块四 + 五 + 六**（STL 深入 + 异常 + 模板进阶）→ **模块七 + 八**（并发 + 工具链，常和实战项目一起练）。
- 工具链（模块八）不必等到最后——**Git、CMake、GDB 越早用越好**，从你写第一个像样项目时就该上手，边做边熟。
- 每个模块学完，最好有个**小产出**（路线里提过的 `MyString`、手写 `SharedPtr`、线程池等里程碑项目，正好分别压在模块二、二、七上）。

---

> 如果这份清单里有你觉得「这个我其实学过了」的，告诉我，我们就跳过；有你想优先攻的，我们就提前。后面我每带你学一个模块，都会照着这份清单走，漏不了。