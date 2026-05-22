// 线性探测哈希桶简单实现(取模法)
#include <iostream>
using namespace std;

// 桶的状态
enum State{
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL
};

// 哈希桶
struct Bucket{
    Bucket(int key = 0, State state = STATE_UNUSE)
        : key_(key)
        , state_(state)
        {}
    int key_;
    State state_;
};

// 创建哈希表
class HashTable{
public:
    // 构造函数(可传入大小与负载因子)
    HashTable(int size = Prime_Table[0], double loadFactor = 0.75)
        :useTableNum_(0)   
        ,loadFactor_(loadFactor)
        ,PrimeIdx_(0)
    {
        // 如果用户传入的值不符合素数表的值 对这个size调整至最近的比较大的素数值
        if(size != Prime_Table[0]){
            for(;PrimeIdx_ < PRIME_SIZE;++PrimeIdx_){
                if(Prime_Table[PrimeIdx_] >= size){
                    break;
                }
            }
            // 如果用户传入的值过大 使用最大的素数值
            if(PrimeIdx_ == PRIME_SIZE){
                PrimeIdx_--;
            }
        } 
        // 在函数内部创建大小与堆内存
        table_size = Prime_Table[PrimeIdx_];
        table_ = new Bucket[table_size];
    }

    // 析构函数
    ~HashTable(){
        delete[] table_;
        table_ = nullptr;
    }

    // 插入
    bool insert(int key){
        double factor = useTableNum_*1.0 / table_size;
        cout << "factor: "<< factor << endl;
        if(factor >= loadFactor_){
            expand();
        }
        int idx = (key % table_size + table_size) % table_size;
        int i = idx;
        do{
            if(table_[i].state_ != STATE_USING){
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useTableNum_++;
                return true;
            }
            i = (i+1) % table_size;
        }while(table_[i].state_!=STATE_UNUSE && i != idx);
        return false;
    }

    // 删除所有值为key的哈希桶
    void erase(int key){
        int idx = (key % table_size + table_size) % table_size;
        int i = idx;
        do{
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key){
                table_[i].state_ = STATE_DEL;
                useTableNum_--;
            }
            i = (i+1) % table_size;
        }while(table_[i].state_!=STATE_UNUSE && i != idx);
    }

    // 查询
    bool find(int key){
        int idx = (key % table_size + table_size) % table_size;
        int i = idx;
        do{
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key){
                return true;
            }
            i = (i+1) % table_size;
        }while(table_[i].state_!=STATE_UNUSE && i != idx);
        return false;
    }

private:
    // 扩容操作
    void expand(){
        ++PrimeIdx_;
        if(PrimeIdx_ == PRIME_SIZE){
            throw "HashTable is too large, can not expand anymore!";
        }
        int new_size = Prime_Table[PrimeIdx_];
        Bucket* newTable = new Bucket[new_size];
        for(int i = 0;i<table_size;++i){
            if(table_[i].state_ == STATE_USING){
                int idx = (table_[i].key_ % new_size + new_size) % new_size;
                int k = idx;
                do{
                    if(newTable[k].state_ != STATE_USING){
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                }while(k != idx);
            }
        }
        delete[] table_;
        table_ = newTable;
        table_size = Prime_Table[PrimeIdx_];
    }
    Bucket* table_;
    int table_size;
    int useTableNum_;
    double loadFactor_;
    static const int PRIME_SIZE = 10;
    static int Prime_Table[PRIME_SIZE];
    int PrimeIdx_;
};
int HashTable::Prime_Table[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};


 int main(){
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);
    htable.insert(21);




    return 0;
 }