// 插入排序

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void InsertSort(int arr[],int size){
    if(size <= 1) return;
    for(int i = 1;i<size;++i){
        int val = arr[i];
        int j = i;
        while(j > 0 && arr[j-1] > val){
            arr[j] = arr[j-1];
            j--;
        }
        if(j != i){
            arr[j] = val;
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
    InsertSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}