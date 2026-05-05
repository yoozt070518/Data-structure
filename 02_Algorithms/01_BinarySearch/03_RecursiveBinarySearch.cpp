// 二分搜索算法的递归实现
#include <iostream>
using namespace std;


// 递归
// 形式上：函数自己调用自己
// 数据规模从n到很小时 问题答案是已知的
// eg.100！不知道 但是我知道1!

// 不管是什么数据规模 求解问题的方式是一样的
// 不同规模的数据 其计算结果是有关系可循的

// 特点
// 1.一定要搞清楚递归函数的意义是什么
// 返回值 参数列表 它能完成什么功能
// 2.一定有递归结束的条件
// 3.每个数据规模要写好它们之间的计算关系

// 递归问题的思考是水平方向上的
// 递归代码的具体执行是垂直方向上的



// 二分搜索的代码实现
//    数组 => 数据规模缩减
//      起始的下标 末尾的下标
int BinarySearch(int arr[],int i, int j, int val)
// 在arr数组的[i,j]范围内，二分搜索值val,找到的话返回值的下标 找不到返回-1
{
    if(i > j){
        return -1;
    }
    int mid = (i+j)/2;
    if(arr[mid] == val){
        return mid;
    }else if(arr[mid] > val){
        return BinarySearch(arr, i, mid-1, val);
    }else{
        return BinarySearch(arr, mid+1, j, val);
    }
}