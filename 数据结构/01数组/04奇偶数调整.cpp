#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
void oddadjust(int* arr,int size){
    int* p = arr;
    int* q = arr+size-1;
//     while(p < q){
        
//         if((*p&1)==0){
//             p++;
//             continue;
//         }

//         if((*q&1)==1){
//             q--;
//             continue;
//         }

//         int temp = *p;
//         *p = *q;
//         *q = temp;
//         p++;
//         q--;

//     }
// } 此段代码看起来较短 但在判断q时如果continue又会重新判断一次p 效率较低
    while(p < q){
        while(p < q){
            if((*p&1)==1){
                break;
            }
            p++;
        }
        while(p < q){
            if((*q&1)==0){
                break;
            }
            q--;
        }
        if(p < q){// 如果不是因为找到奇数或偶数而跳出的情况就不需要交换了
            int tmp = *p;
            *p = *q;
            *q = tmp;
            p++;
            q--;
        }
    }
}

int main(){
    int arr[10] = {0};
    srand(time(0));
    for(int i = 0;i<10;++i){
        arr[i] = rand()%100;

    }
    for(int v: arr){
        cout << v << " ";  
    }
    cout << endl;
    oddadjust(arr,10);
    for(int v: arr){
        cout << v << " ";  
    }
    return 0;
}