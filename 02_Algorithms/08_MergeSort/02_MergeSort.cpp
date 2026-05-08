#include <iostream>
using namespace std;
void Merge(int arr[], int l, int r, int mid){
    int* p = new int[r-l+1];
    int i = l;
    int j = mid+1;
    int idx = 0;
    while(i <= mid && j <= r){
        if(arr[i] <= arr[j]){
            p[idx++] = arr[i++];
        }
        else{
            p[idx++] = arr[j++];
        }
    }
    while(i <= mid){
        p[idx++] = arr[i++];
    }
    while(j <= r){
        p[idx++] = arr[j++];
    }
    for(j = 0,i = l;i <= r;i++,j++){
        arr[i] = p[j];
    }
    delete[] p;
}
void MergeSort(int arr[] , int begin, int end){
    if(begin >= end){
        return;
    }
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid+1, end);
    Merge(arr, begin, end, mid);
}
void MergeSort(int arr[], int size){
    MergeSort(arr, 0, size-1);
}





int main(){
    return 0;
}