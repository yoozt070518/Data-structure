#include <iostream>
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
    for(int i = 0;i < size-1;++i){// O(n)
        int min = arr[i];
        int k = i;
        for(int j = i+1;j < size;++j){ // O(n)
            if(arr[j] < min){
                min = arr[j];
                k  = j;
            }
        }
        if(k!=i){
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;

        }
    }
}



int main(){
    return 0;
}