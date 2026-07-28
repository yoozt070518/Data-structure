// 希尔排序
#include <iostream>
using namespace std;

void ShellSort(int arr[], int size){
    for(int gap = size/2;gap>0;gap /= 2){
        for(int i = gap;i < size;++i){
            int val = arr[i];
            int j = i;
            while(j > 0 && arr[j-gap] > val){
                arr[j] = arr[j-gap];
                j -= gap;
            }
            if(j != i){
                arr[j] = val;
            }
        }
    }
}

int main(){
    return 0;
}