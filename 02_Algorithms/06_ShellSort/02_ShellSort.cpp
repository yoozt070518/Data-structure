// 希尔排序
#include <iostream>
using namespace std;

void ShellSort(int arr[], int size){
    for(int gap = size / 2;gap >0;gap/=2){
        for(int i = gap;i < size;i++){
            int val = arr[i];
            int j = i-gap;
            for( ; j >= 0; j-=gap){
                if(arr[j] <= val){
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j+gap] = val;
        }
    }
}

int main(){
    return 0;
}