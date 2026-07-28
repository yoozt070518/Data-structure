#include <iostream> 
using namespace std;
int medianOfThree(int arr[], int begin, int end){
    int mid = begin + (end - begin) / 2;
    if(arr[begin] > arr[mid]) swap(arr[begin], arr[mid]);
    if(arr[begin] > arr[end]) swap(arr[begin], arr[end]);
    if(arr[mid] > arr[end])   swap(arr[mid], arr[end]);
    return mid;
}
int partition(int arr[], int begin, int end){
    int tmp = medianOfThree(arr, begin, end);
    swap(arr[begin], arr[tmp]);
    int val = arr[begin];
    int i = begin;
    int j = end;
    while(i < j){
        while(i < j && arr[j] < val)
            j--;
        if(i < j){
            arr[i] = arr[j];
            i++;
        }
        while(i < j && arr[i] > val)
            i++;
        if(i < j){
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = val;
    return i;
}
void SelectTopk(int arr[], int begin, int end, int k){
    int pos = partition(arr, begin, end);
    if(pos == k){
        return;
    }
    else if(pos > k){
        SelectTopk(arr, begin, pos-1, k);
    }
    else if(pos < k){
        SelectTopk(arr,pos+1, end, k);
    }
}

int main(){
    int arr[] = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    int size = sizeof arr / sizeof arr[0];
    int k = 3;
    SelectTopk(arr, 0, size-1, k-1);
    for(int i = 0;i<k;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}