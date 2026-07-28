# memmove
memmove是定义在<cstring>中的一个标准库函数

## 作用
- 将一块内存区域的字节，原封不动地搬到另一块内存区域
## 原型
void* memmove(void* dest, const void* src, size_t count);
- dest: 目标内存的起始地址
- src:  源内存的起始地址
- count: 要搬运的字节数
## 优点
对比for循环地一次次判断循环变量的递增 
memmove是直接堆cpu下达指令 一次性打包搬运 比for循环快了几个数量级

## memcpy
也是定义在<cstirng>中的一个标准库函数
## 原型
void* memcpy(void* dest, const void* src, size_t count);
- dest: 目标内存起始地址
- src:  源内存起始地址
- count: 搬运的字节总数
## 作用场景
把一块内存的数据，原封不动地“克隆”到另一块完全独立的内存中。
## 注意
memcpy不能执行带重叠区域的地址 如有重叠需要使用memmove
原因：
- memmove每次执行前 必须做一次if(dest <= src)的地址大小判断
- 而memcpy只是一味的搬运 会出现它不停在搬运同一块地址的情况
