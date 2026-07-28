// 元素逆序



#include <iostream>
#include <cstring>
using namespace std;
// 逆序字符串
// 双指针
void Reverse(char arr[],int size){
     char* p = arr;
     char* q = arr + size-1;
     while(p < q){
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
     }
}

int main(){
    char arr[] = "hello world";
    Reverse(arr,strlen(arr));
    cout << arr << endl;
    return 0;
}