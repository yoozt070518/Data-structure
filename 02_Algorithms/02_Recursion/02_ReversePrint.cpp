#include <iostream>
#include <stdexcept>
using namespace std;

void printReverse(int arr[], int size) {
    // 🛑 铁律 1：绝对不能出现 for, while, do-while, 甚至 goto！
    
    // 💡 提示 1：终止条件是什么？当 size 变成什么的时候，说明没东西可打印了？
    
    // 💡 提示 2：如何缩小规模？
    // 你可以通过传入 (arr, size - 1) 来让数组看起来少了一个元素
    // 或者传入 (arr + 1, size - 1) 让数组的开头往后挪一位。
    
    // 💡 提示 3：“归”的魔法
    // 如果你先调用递归，再打印，会发生什么？
    // 如果你先打印，再调用递归，又会发生什么？
    
    // 你的逻辑写在这里：
    if(size < 0){
        throw std::invalid_argument("Index is invalid!");
    }
    if(size == 0){
        return;
    }
    
    printReverse(arr+1, size-1);
    cout << arr[0] << " ";
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "期望输出: 5 4 3 2 1" << endl;
    cout << "实际输出: ";
    
    printReverse(arr, size);
    
    cout << endl;
    return 0;
}