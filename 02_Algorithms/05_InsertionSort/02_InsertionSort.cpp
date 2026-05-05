// 插入排序

#include <iostream>
using namespace std;

void InsertSort(int arr[],int size){
    for(int i = 1;i<size;i++){
        int val = arr[i];int j = i-1;
        for(; j>=0;--j){
            if(arr[j] <= val){
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
    }
}







int main(){
    return 0;
}