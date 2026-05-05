// 二分搜索非递归实现
#include <iostream>
using namespace std;

int BinarySearch(int arr[],int size, int val){
    int first = 0;
    int last = size-1;
    while(first <= last){
        int mid = (first+last) /2;
        if(arr[mid] == val){
            return mid;
        }
        else if(arr[mid] > val){
            last = mid - 1;
        }else{
            first = mid + 1;
        }
    }
    return -1;
}






int main(){
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82 , 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << BinarySearch(arr,size, 39) <<endl;
    cout << BinarySearch(arr,size, 45) <<endl;
    cout << BinarySearch(arr,size, 12) <<endl;
    cout << BinarySearch(arr,size, 64) <<endl;
    return 0;
}