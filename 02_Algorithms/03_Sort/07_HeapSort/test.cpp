#include <iostream>
#include <algorithm>
using namespace std;

class MyPriorityQueue {
private:
    int* p;     // 营地指针：指向你在堆区申请的动态数组
    int size;   // 当前兵力：目前队伍里到底有几个人
    int cap;    // 营地容量：当前这块地皮最多能容纳几个人

    // ================= [内部后勤与战术动作] =================

    // 1. 扩容机制 (⚠️ 这是动态堆独有的全新挑战！)
    // 目标：当发现兵力满编 (size == cap) 时，申请一块容量为当前 2 倍的新地皮。
    // 将老地皮上的兵全部转移过来，然后炸毁（释放）老地皮，更新 p 和 cap。
    void resize(int newsize) {
        int* newp = new int[newsize];
        for(int i = 0; i<size;++i){
            newp[i] = p[i];
        }
        cap = newsize;
        delete[] p;
        p = newp;
    }

    // 2. 算下标 (战术辅助)
    int parent(int i) {  return (i - 1) / 2; }
    int leftChild(int i) {  return 2*i+1; }
    int rightChild(int i) { return 2*i+2; }

    // 3. 向上调整 (新兵入伍篡位)
    // 目标：让 index 位置的新王不断和 parent 比较，比 parent 大就交换，直到封顶或镇压。
    void siftUp(int index) {
        int i = index;
        int val = p[i];
        while(i>0 && p[parent(i)] < val){
            p[i] = p[parent(i)];
            i = parent(i);
        }
        p[i] = val;
    }

    // 4. 向下调整 (老兵下放)
    // 目标：让 index 位置的弱鸡和两个儿子中较强的那个比较，比儿子弱就交换，一直滚到底部。
    void siftDown(int index) {
        int i = index;
        int val = p[i];
        while(leftChild(i) < size){
            int l = leftChild(i);
            int r = rightChild(i);
            int idx_max = l;
            if(r < size && p[l] < p[r]){
                idx_max = r;
            }
            if(val >= p[idx_max]){
                break;
            }
            p[i] = p[idx_max];
            i = idx_max;
        }
        p[i] = val;
    }

public:
    // ================= [对外作战指令] =================

    // 5. 构造函数 (建军)
    // 目标：给 cap 赋予一个初始值（比如默认 10），给 size 清零。
    // ⚠️ 最重要的一步：用 new int[cap] 为 p 申请初始营地！
    MyPriorityQueue(int init_cap = 10) {
        size = 0;
        cap = init_cap;
        p = new int[init_cap];
    }

    // 6. 析构函数 (⚠️ C++ 程序员的终极使命：有借有还)
    // 目标：军队解散时自动调用，必须在这里用 delete[] 释放 p 指向的内存！防止内存泄漏！
    ~MyPriorityQueue() {
        delete[] p;
        p = nullptr;
    }

    // 7. 入队
    // 目标：检查 capacity（不够就调用 resize 扩容），把新兵塞到数组末尾，然后调用 siftUp，最后 size++。
    void push(int val) {
        if(size == cap){
            resize(2*size);
        }
        p[size] = val;
        siftUp(size);
        size++;
    }

    // 8. 出队
    // 目标：检查是否为空。不为空时，把数组末尾的人调到 p[0]，size--，然后对 p[0] 调用 siftDown。
    void pop() {
        if(size==0){
            throw "queue is empty!";
        }
        p[0] = p[size-1];
        size--;
        siftDown(0);
    }

    // 9. 获取最高指挥官
    // 目标：返回金字塔尖 (p[0]) 的值。
    int top() {
        return p[0]; 
    }

    // 10. 刺探军情
    bool empty() {  return size==0; }
    int getSize() { return size; }
};
int main(){
    return 0;
}