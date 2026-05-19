#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void BubbleSort(int arr[] , int size){
    if(size==0 || size==1) return;
    int lastswapidx = size-1;
    while(lastswapidx > 0){
        int curlastswapidx = 0;
        bool isSorted = true;
        for(int j = 0;j<lastswapidx;++j){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                curlastswapidx = j;
                isSorted = false;
            }
        }
        if(isSorted) break;
        lastswapidx = curlastswapidx;
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