#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
void set(int* bitmap, int n){
    int idx = n / 32;
    int bit = n % 32;
    bitmap[idx] |= (1 << bit);
}
bool get(int* bitmap, int n){
    int idx = n / 32;
    int bit = n % 32;
    return bitmap[idx] & (1 << bit);
}
int getMax(const vector<int>& v){
    int max = v[0];
    for(size_t i = 1;i < v.size();++i){
        if(v[i] > max) max = v[i];
    }
    return max;
}
void add(int* high, int* low, int n){
    int idx = n / 32;
    int bit = n % 32;

    if(low[idx] & (1 << bit)){
        low[idx] &= ~(1 << bit);// low位清0
        high[idx] |= (1 << bit);
    }else{
        low[idx] |= (1 << bit);
    }
}

int main(){
    /* 去重
    vector<int> nums = {5, 23, 7, 23, 99, 5, 42, 7, 42, 1};
    // 定义位图数组
    int MAX = nums[0];
    for(size_t i = 1;i<nums.size();++i){
        if(nums[i] > MAX){
            MAX = nums[i];
        }
    }
    int* bitmap = new int[MAX / 32 + 1];
    memset(bitmap, 0, (MAX / 32 + 1)*sizeof(int));

    for(const auto& i : nums){
        set(bitmap, i);
    }
    for(int i = 0;i<=MAX;++i){
        if(get(bitmap, i)){
            cout << i << " ";
        }
    }
    delete[] bitmap;
    */

    /*  取重复的数
    vector<int> file1 = {1, 5, 23, 42, 99, 200, 5, 23};
    vector<int> file2 = {23, 99, 300, 42, 500, 23, 99};

    int MAX = max(getMax(file1), getMax(file2));
    int size = MAX / 32 + 1;
    int* bitmap1 = new int[size];
    memset(bitmap1, 0 ,size*sizeof(int));
    int* bitmap2 = new int[size];
    memset(bitmap2, 0 ,size*sizeof(int));
    for(const auto& i : file1){
        set(bitmap1, i);
    }
    for(const auto& i : file2){
        set(bitmap2, i);
    }
    for(int i = 0;i<=MAX;++i){
        if(get(bitmap1, i) && get(bitmap2, i)){
            cout << i<< " ";
        }
    }
    delete[] bitmap1;
    delete[] bitmap2;
    */

    vector<int> nums = {1, 2, 3, 2, 1, 4, 3};
    int MAX = getMax(nums);
    int size = MAX / 32 + 1;
    int* low = new int[size]();
    int* high = new int[size]();
    for(const auto& i : nums){
        add(high, low , i);
    }
    for(int i = 0;i <= MAX;++i){
        if(get(low, i)) cout << i << endl;
    }
    delete[] low;
    delete[] high;


    return 0;
}
