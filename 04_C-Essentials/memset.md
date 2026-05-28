memset 是 C 标准库里的函数，用来批量设置内存的值。

用之前要引入头文件：
cpp#include <cstring>
用法：
cppmemset(起始地址, 填充的值, 字节数);
比如把 bitmap 数组全部填成 0：
cppint size = MAX / 32 + 1;
int* bitmap = new int[size];
memset(bitmap, 0, size * sizeof(int));
//                ^^^^^^^^^^^^^^^^
//                总字节数 = 元素个数 × 每个元素的字节数
sizeof(int) 是 int 占几个字节，一般是 4。

不过你的情况用括号初始化更简单：
cppint* bitmap = new int[size]();  // 自动全部初始化为 0
两种都行，括号初始化更简洁，memset 更灵活（可以填任意值）。