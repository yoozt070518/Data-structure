#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class HashTable{
public:
    HashTable(int size = primes_[0], int loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        if(size != primes_[0]){
            for(;primeIdx_ < PRIME_SIZE;++primeIdx_){
                if(primes_[primeIdx_] >= size){
                    break;
                }
            }
            if(primeIdx_ == PRIME_SIZE){
                primeIdx_--;
            }
        }
        table_.resize(primes_[primeIdx_]);
    }

    // 增加元素
    void insert(int key){
        double factor = useBucketNum_*1.0 / table_.size();
        cout << "factor: " << factor << endl;
        if(factor > loadFactor_){
            expand();
        }
        int idx = (key % table_.size() + table_.size()) % table_.size();
        if(table_[idx].empty()){
            useBucketNum_++;
            table_[idx].emplace_front(key);
        }else{
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end()){
                // k不存在
                table_[idx].emplace_back(key);
            }
        }
    }

    void erase(int key){
        int idx = (key % table_.size() + table_.size()) % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end()){
            table_[idx].erase(it);
            if(table_[idx].empty()){
                useBucketNum_--;
            }
        }
    }

    bool find(int key){
        int idx = (key % table_.size() + table_.size()) % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it!=table_[idx].end();
    }
private:
    void expand(){
        if(primeIdx_+1 == PRIME_SIZE){
            throw "hashTable can not expand anymore!";
        }
        primeIdx_++;
        useBucketNum_ = 0;
        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);
        for(auto list : oldTable){
            for(auto key : list){
                int idx = key % table_.size();
                if(table_[idx].empty()){
                    useBucketNum_++;
                }
                table_[idx].emplace_back(key);
            }
        }
    }
    vector<list<int>> table_; // 哈希表的数据结构
    int useBucketNum_;        // 记录桶的个数
    int loadFactor_;          // 记录哈希表装载银子
    static const int PRIME_SIZE = 10;   // 素数表的大小
    static int primes_[PRIME_SIZE];     // 素数表
    int primeIdx_;                      // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = {3,  7, 23, 47, 97, 251, 443, 911, 1471, 42774};