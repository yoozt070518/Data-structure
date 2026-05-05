#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void BubbleSort(int arr[], int size){
    for(int i = 0;i<size-1;++i){
        bool flag = false;
        
        for(int j = 0;j < size-1-i;++j){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
        }
// 一趟的处理中 如果没有做任何的数据交换 那么说明数据已经有序了
        if(!flag){
            return;
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
    BubbleSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}