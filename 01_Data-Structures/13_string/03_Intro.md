# 串
## KP1-串的本质与存储
**串是什么？**
> 串是0个或多个字符组成的有限序列。
**序列**：它和vector的区别就是把这个序列当成一个整体来操作(求子串、定位、比较)。
- **空串**也是合法的串

### 存储方式
串是一种线性结构，物理存储有三条路
1. 定长顺序串———优点是开销小，连续内存且随机访问，缺点是不能扩容
2. 堆分配串————优点是随机访问，连续内存且可以扩容，缺点是开销比定长大一些
3. 块链串————优点是能解决删除导致的大数据搬移，缺点是不能随机访问，且内存利用率低

我们用的一般是**堆分配加SSO**

## KP2-BF朴素匹配
问题：在主串text(长n)里，找模式串pattern(长m)第一次完整出现的初始位置

**最直接的想法**：
直接拿着模式串一个个去比对，如果有一位对不上，就回到最初比对的位置，往后一位继续比较

**实现**
拆成两个指针来驱动：
- `i`指向主串当前比较的字符
- `j`指向模式串当前比较的字符

每一轮，比较text[i] 和 pattern[j]
- **相等**，则二者皆往后推进
- **不相等**，则判定为失败，模式串要整体后移一位重新对齐

失配时，`i`指针应该回到当初最开始的`start`指针，并向后一位,即`start + 1`
`j`指针则需要重新归零

而最初的那个位置`start`就是最开始的`i`，所以只需要减去这一段走的步长`j`就能得到

因此就是`i = i - j + 1;`
`j = 0;`

代码实现

```cpp
#include <string>
using namespace std;

int bruteForce(const string& text, const string& pattern){
    // 先用int类型转换掉size(),以便后续操作
    int n = text.size();
    int m = pattern.size();

    // 定义双指针
    int i = 0;
    int j = 0;

    // 循环的作用：一步步比对俩串，直至模式串完全结束，则成功
    // 若是主串结束，则失败
    while(i < n && j < m){
        // 循环内部，要做的就是比对两串
        if(text[i] == pattern[j]){
            i++;
            j++;
        }else{
            i = i-j+1;
            j = 0;
        }
    }
    return (j==m) ? i-j : -1;
    // 若j==m，则证明是因为模式串完结才导致的循环跳出，证明成功了，要返回的位置就是当前的主串位置减去步长
}
```
**复杂度分析**:
因为此代码在循环内部的i回退以及j的回退，若pattern的前面位置全部一致的话，就会出现`i`和`j`反复走到最后再退回
这就导致了最坏O(nm)的时间复杂度

## KP3-失配
对于BF的失配，我们直接将`i = i-j+1`
对于这串代码，我们实际上是**浪费掉了主串与模式串的相匹配片段**
实际上，在扫描过两相等片段之后，我们就能知道，主串的信息，全部都包含在了模式串的前`j`个片段中

而我们该往哪对其，只取决于这段前缀里**开头一截**和**结尾一截***“最长能重合多少”*

也就是**前缀和后缀的最长公共部分**
知道这部分的**长度**后，我们就能只对模式串进行调正，让模式串对齐应该对齐的部分

## KP4-KMP主匹配
前面KP3拿到的洞察，就是
> 失配时主串i不退，模式串j退到“已经匹配前缀的前后缀公共长度”处继续

而对于这段前缀的前后缀公共长度，我们可以通过next数组来储存不同前缀的长度，来保存下来

我们现在假设它已经算好了，来继续解决KMP

对于BF,循环内部的正确那段并不用改，要改的只有失配的那一段
只需
`else {j = next[j]};`
就能让j退到该退的位置
不过如果失配发生在`j == 0`,即主串的第一位就和模式串不一样，这部分也就无需再比，j也退不了了。所以最保险的写法，就是直接分情况
```cpp
if( text[i] == pattern[j]){
    ++i;
    ++j;
}else if(j == 0){
    i++;
}else{
    j = next[j];
}
```
但是这里有一个更加巧妙的设计，我们将`j==0`时的`next[0]`设置为-1，并且让`j==-1`也包含在第一个条件当中，这样，随着`i++`和`j++`的进行，也能达到让j归0，i往后的效果，同时也合并了两个方向

即
```cpp
if(j == -1 || text[i] == pattern[j]){
    i++;
    j++;
}else{
    j = next[j];
}
```
### 完整代码实现
```cpp
#include <string>
#include <vector>

vector<int> getNext(const string& pattern);

int kmp(const string& text, const string& pattern){
    int n = text.size();
    int m = pattern.size();
    int i = 0, j = 0;
    while(i < n && j < m){
        if(j == -1 || text[i] == pattern[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    return (j == m) i - j : -1;
}

```
**时间复杂度**：
此处虽说`j`也在反反复复的倒退
但是`i`全程只增不减，且`j`想增加就必须带着`i`一起
而`i<n`是循环的基本条件，所以`j`至多也只会增加n次
因此这里只有**O(n)**的时间复杂度
加上后面要说的getNext函数里的**O(m)**
也只有**O(n+m)**的时间复杂度


## KP5-next数组
对于next数组，它就是**前缀里的真前缀与真后缀最长公共长度**，这个长度刚好与`j`后面要匹配的长度一致
而要求的内容就是把pattern的前j个数取出来，然后从j-1开始对比前缀和后缀，第一个相等的长度就是答案
一直比到0都没有就填0，也就是重新开始
j==0时特判为-1

### 完整代码实现
```cpp
#include <string>
#include <vector>
using namespace std;

vector<int> getNext(const string& pattern){
    int m = pattern.size();
    vector<int> next(m);
    next[0] = -1;
    for(int j = 1;j < m;++j){
        int ans = 0;
        for(int k = j-1;k >= 0;--k){
            bool same = true;    
            for(int t = 0;t < k;++t){
                if(pattern[t] != pattern[j-k+t]){
                    same = false;
                    break;
                }
            }
            if(same){
                ans = k;
                break;
            }
        }
        next[j] = ans;
    }
    return next;
}
```

## KP6-next的递推求法
递归思路：**已知next[j], 怎么推next[j+1]**
若next[j] == k;
也就是说pattern的前j个元素的前k个元素和后k个元素一致
如果**pattern[j] == pattern[k]**
那就说明**pattern[j+1] == k+1**

如果**pattern[j] != pattern[k]**
那就只能寄希望于比k小的数目相同。
要找**更短的公共前后缀**，同时必须是pattern[0..j-1]的前缀和后缀
而长度k的公共部分，pattern[0..k-1]本身就是pattern[0..j-1]的前缀和后缀。所以，更短的前缀和后缀，**也就是pattern[0..k-1]的前缀和后缀**
而这部分，也就是**next[k]**


### 完整代码实现
```cpp
#include <string>
#include <vector>

vector<int> getNext(const string& pattern){
    int m = pattern.size();
    vector<int> next(m);
    next[0] = -1;
    int j = 0;
    int k = -1;
    while(j < m-1){
        if(pattern[j] == pattern[k]){
            j++;
            k++;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return next;
}

int kmp(const string& text, const string& pattern){
    int n = text.size();
    int m = pattern.size();
    vector<int> next = getNext(pattern);
    int i = 0;
    int j = 0;
    while(i < n && j < m){
        if(j == -1 || text[i] == pattern[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
}