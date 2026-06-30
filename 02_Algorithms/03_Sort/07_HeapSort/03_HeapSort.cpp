#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

void SiftDown(int arr[], int size, int index){
    int i = index;
    int val = arr[i];
    while(2*i+1<size){
        int child = 2*i+1;
        if(child + 1 < size && arr[child] < arr[child+1]){
            child++;
        }
        if(val >= arr[child]){
            break;
        }
        arr[i] = arr[child];
        i = child;
    }
    arr[i] = val;
}
void HeapSort(int arr[], int size){
    if(size<=1) return;
    int n = size-1;
    for(int i = (n-1)/2;i>=0;--i){
        SiftDown(arr, size, i);
    }
    for(int i = n;i>0;--i){
        swap(arr[0], arr[i]);
        SiftDown(arr, i, 0);
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
    HeapSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}