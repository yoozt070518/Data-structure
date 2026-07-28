#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// O(n)
// 有序->选择排序
int partition(int arr[], int l ,int r){
    int val = arr[l];
    while(l < r){
        while(l < r && arr[r] >= val){
            r--;
        }
        arr[l] = arr[r];
        while(l < r && arr[l] <= val){
            l++;
        }
        arr[r] = arr[l];
    }
    arr[l] = val;
    return l;
}

void QuickSort(int arr[], int begin, int end){
    if(begin >= end) return;
    int pos = partition(arr, begin, end);
    QuickSort(arr, begin, pos-1);
    QuickSort(arr, pos+1, end);
}
void QuickSort(int arr[], int size){
    if(size <= 1) return;
    QuickSort(arr, 0, size-1);
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
    QuickSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}
