#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void merge(int arr[],int brr[],  int l, int mid,int r){
    int i = l;
    int j = mid+1;
    int t = 0;
    while(i<= mid && j<=r){
        if(arr[i] <= arr[j]){
            brr[t++] = arr[i++];
        }else{
            brr[t++] = arr[j++];
        }
    }
    while(i <= mid){
        brr[t++] = arr[i++];
    }
    while(j <= r){
        brr[t++] = arr[j++];
    }
    for(i = 0, j = l;j<=r;++j,++i){
        arr[j] = brr[i];
    }
}

void MergeSort(int arr[], int brr[], int l, int r){
    if(l >= r) return;
    int mid = l + (r-l)/2;
    MergeSort(arr, brr, l, mid);
    MergeSort(arr, brr, mid+1, r);
    merge(arr, brr, l , mid, r);
}
void MergeSort(int arr[], int size){
    if(size<=1) return;
    int* p = new int[size];
    MergeSort(arr, p, 0, size-1);
    delete[] p;
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
    MergeSort(arr,10);
    for(int v : arr){
        cout << v << " ";
    }
    return 0;
}