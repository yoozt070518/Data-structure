#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
// 选择排序
// 效率比冒泡排序高
// 特点：每次在剩下的元素中选择值最小的元素，和当前元素进行交换
// 缺点：相比于冒泡排序 交换次数少了 但是比较次数依然很多
// 时间复杂度 : O(n^2) 
//            且没有办法进行优化 最好和最坏都是O(n^2)
// 空间复杂度：O(1)
// 稳定性：不稳定

void ChoiceSort(int arr[], int size){
    if(size <= 1) return;
    for(int i = 0;i<size-1;++i){
        int min_idx = i;
        for(int j = i+1;j<size;++j){
            if(arr[min_idx] > arr[j]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            swap(arr[i], arr[min_idx]);
        }
    }
}



int main(){
     int arr[10];
    srand(time(0));
    for(int i = 0;i<10;++i){
        arr[i] = rand() % 100 + 1;
    }

    for(int v : arr){
        cout << v << " ";
    }
    cout << endl;
    ChoiceSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}