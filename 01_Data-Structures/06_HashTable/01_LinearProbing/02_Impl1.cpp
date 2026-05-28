#include <iostream>
using namespace std;
// 桶的状态
enum State{
    STATE_UNSING, // 从未使用过的桶
    STATE_USING, // 正在使用的桶
    STATE_DEL    // 曾经使用过 现在被删除了的桶
};

// 桶的类型
struct Bucket{
    Bucket(int key = 0, State state = STATE_USING)
        : key_(key)
        , state_(state)
        {}
    int key_;       // 存储的数据 
    State state_;   // 桶的当前状态
};

// 线性探测哈希表类型
class HashTable{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {   
        // 把用户传入的size调整到最近的比较大的素数上
        if(size != primes_[0]){
            for(; primeIdx_ < PRIME_SIZE;primeIdx_++){
                if(primes_[primeIdx_] > size){
                    break;
                }
            }

            // 用户传入的size值过大，已经超过最后一个素数，调整到最后一个素数
            if(primeIdx_ == PRIME_SIZE){
                primeIdx_--;
            }

            tableSize_ = primes_[primeIdx_];
            table_ = new Bucket[tableSize_];
        }
    }

    ~HashTable(){
        delete[] table_;
        table_ = nullptr;
    }

public:
    // 插入元素
    bool insert(int key)
    {
        
    }


private:
    Bucket* table_;         // 指向动态开辟的哈希表
    int tableSize_;         // 哈希表当前的长度
    int useBucketNum_;      // 已经使用的桶的个数
    double loadFactor_;     // 哈希表的装载因子
    static const int PRIME_SIZE = 10;  // 素数表的大小
    static int primes_[PRIME_SIZE];    // 素数表
    int primeIdx_;          // 当前使用的素数下标
};
int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773}; 



int main(){
    return 0;
}