# ⚔️ 算法深度解析：堆排序 (Heap Sort)

堆排序是一种基于 **二叉堆 (Binary Heap)** 数据结构的比较排序算法。它利用了堆这种近似完全二叉树的特性，实现了时间复杂度为 $O(n \log n)$ 的高效就地排序。

---

## 1. 核心预备知识：什么是堆？

堆必须满足以下两个核心性质：

1.  **结构性**：是一棵 **完全二叉树**。除了最后一层外，每一层都是满的，且最后一层从左向右填充。
2.  **堆序性**：
    * **大根堆 (Max Heap)**：任一父节点的值都 $\ge$ 其子节点的值。堆顶（根节点）是全集最大值。
    * **小根堆 (Min Heap)**：任一父节点的值都 $\le$ 其子节点的值。堆顶（根节点）是全集最小值。

**数组映射公式**：
若父节点下标为 `i`，则：
- 左孩子下标 = `2 * i + 1`
- 右孩子下标 = `2 * i + 2`
- 父节点下标 = `(i - 1) / 2`

---

## 2. 堆排序的执行流程

堆排序（以升序排列为例，使用大根堆）主要分为两个阶段：

### 阶段一：初始建堆 (Build Heap)
将一个无序数组调整为一个大根堆。
- **打法**：从最后一个非叶子节点（下标为 `(n-1)/2`）开始，从后往前依次执行 `SiftDown`（向下调整）操作。
- **复杂度**：证明后可得建堆的时间复杂度为 $O(n)$。

### 阶段二：排序循环 (Sorting Loop)
1.  将堆顶元素（当前最大值）与堆的最后一个元素交换。
2.  **缩减规模**：将最后一个元素移出堆的逻辑边界（`size--`）。
3.  **恢复性质**：由于新的堆顶破坏了大根堆性质，对堆顶执行一次 `SiftDown`。
4.  重复上述步骤，直到堆中只剩一个元素。

---

## 3. 性能看板 (Performance)

| 特性 | 描述 |
| :--- | :--- |
| **平均时间复杂度** | $O(n \log n)$ |
| **最好时间复杂度** | $O(n \log n)$ |
| **最坏时间复杂度** | $O(n \log n)$ |
| **空间复杂度** | **$O(1)$** (就地排序，极度节省内存) |
| **稳定性** | **不稳定** (存在跨距离元素交换) |

---

## 4. C++ 工业级代码实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 向下调整核心函数
void siftDown(vector<int>& arr, int size, int index) {
    int i = index;
    int val = arr[i]; // 备份当前节点值
    
    while (2 * i + 1 < size) { // 只要有左孩子
        int child = 2 * i + 1; // 默认左孩子最大
        
        // 如果有右孩子，且右孩子比左孩子大
        if (child + 1 < size && arr[child] < arr[child + 1]) {
            child++;
        }
        
        // 如果父节点已经大于等于最强孩子，调整结束
        if (val >= arr[child]) {
            break;
        }
        
        arr[i] = arr[child]; // 强力孩子上浮
        i = child;           // 父节点下标下沉
    }
    arr[i] = val; // 最终落座
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // 1. 初始建堆：从最后一个非叶子节点开始向上处理
    for (int i = (n - 2) / 2; i >= 0; --i) {
        siftDown(arr, n, i);
    }
    
    // 2. 排序循环
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]); // 最大的滚到后面
        siftDown(arr, i, 0);  // 对剩余 i 个元素重新调整堆顶
    }
}

int main() {
    vector<int> data = {46, 79, 56, 38, 40, 84};
    heapSort(data);
    
    for (int x : data) cout << x << " ";
    return 0;
}
```
