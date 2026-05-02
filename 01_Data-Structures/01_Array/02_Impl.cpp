// 动态数组代码实现



#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class Array{
public:
    Array(int size = 10):mCur(0),mCap(size){
        mpArr = new int [mCap];
    }
    ~Array(){
        delete[] mpArr;
        mpArr = nullptr;

    }
    void push_back(int val){
        if(mCur == mCap){
            expend(2*mCap);
        }
        mpArr[mCur++] = val;
    }
    void pop_back(){
        if(mCur==0){
            throw underflow_error("Array is empty");
        }
        mCur--;
    }
    void insert(int pos, int val){
        if(pos < 0|| pos > mCur){
            throw out_of_range("index is invaild");
        }
        if(mCap == mCur){
            expend(2*mCap);
        }
        for(int i = mCur-1;i>=pos;--i){
            mpArr[i+1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++; 
    }
    void erase(int pos){
        if(pos < 0||pos >=mCur){
            throw out_of_range("pos is invaild");
        }
        for(int i = pos;i < mCur-1;++i){
            mpArr[i] = mpArr[i+1];
        }
        mCur--;
    }
    int find(int val){
        for(int i = 0;i<mCur;++i){
            if(mpArr[i]==val){
                return i;
            }
        }
        return -1;
    }
private:
    int* mpArr;
    int mCap;
    int mCur;
    void expend(int size){
        int* p = new int[size];
        memcpy(p, mpArr,sizeof(int)*mCap);
        delete[] mpArr;
        mpArr = p;
        mCap = size;
    }
};



int main(){
    return 0;
}