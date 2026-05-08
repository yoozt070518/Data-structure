#include <iostream>
#include <string>
#include <vector>
using namespace std;

void RadixSort(int arr[], int size){
    // 找到最大的数 由此确定遍历的趟数
    int maxData = arr[0];
    for(int i = 1;i < size;i++){
        if(maxData < arr[i]){
            maxData = arr[i];
        }
    }
    
    // 通过to_string来确定位数
    int len = to_string(maxData).size();
    
    // 用两层vector来作为桶临时存放数据
    vector<vector<int>> vecs;
    int mod = 10;
    int dev = 1;
    for(int i = 0;i<len;mod*=10, dev*=10, i++){
        // 修改size大小 以便直接访问到桶
        vecs.resize(10);
        for(int j = 0;j < size;j++){
            // 得到当前元素第i个位置的数字
            int index = arr[j] % mod / dev;
            vecs[index].push_back(arr[j]);
        }
        // 依次遍历所有的桶 把元素拷贝回原始的数组当中
        int idx = 0;
        for(auto vec : vecs){
            for(int v : vec){
                arr[idx++] = v;
            }
        }

        vecs.clear();
    }

}



int main(){
    return 0;
}