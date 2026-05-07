#include <iostream>
using namespace std;

int Partation(int arr[], int l,int r){
    int val = arr[l];
    while(l < r){
        while(l < r && arr[r] > val){
            r--;
        }
        if(l < r){
            arr[l] = arr[r];
            l++;
        }
        while(l < r && arr[l] < val){
           l++;
        }
        if(l < r){
            arr[r] = arr[l];
            r--;
        }
    }
    // l == r的位置就是放基准数的位置
    arr[l] = val;
    return l;
}

void QuickSort(int arr[], int begin, int end){
    if(begin >= end){// 快排递归结束条件
        return;
    }
    // 在[begin，end]区间的元素做一次快排分割处理
    int pos = Partation(arr, begin, end);
    // 对基准数的左边和右边的序列再分别进行快排
    QuickSort(arr, begin, pos-1);
    QuickSort(arr, pos+1, end);
}

int main(){
    return 0;
}
