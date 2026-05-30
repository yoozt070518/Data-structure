#include <iostream>
#include <vector>
#include <string>
using namespace std;


class BloomFilter{
private:
    int* bitmap;    // 位图数组
    int size;       // 位图数组大小
    int hashCount;  // 哈希函数个数
    vector<int> seeds; // 哈希函数的种子

    void set(int n){
        int idx = n / 32;
        int bit = n % 32;
        bitmap[idx] |= (1 << bit);
    }

    bool get(int n){
        int idx = n / 32;
        int bit = n % 32;
        return bitmap[idx] & (1 << bit);
    }

    int hash(const string& s, int seed){
        int h = 0;
        for(const auto& c : s){
            h = h * seed + c;
        }
        return abs(h) % size;
    }
public:
    BloomFilter(int size, vector<int> seeds)
        : size(size)
        , hashCount(seeds.size())
        , seeds(seeds)
    {
        bitmap = new int[size /32 +1]();
    }

    ~BloomFilter(){
        delete[] bitmap;
    }

    void insert(const string& s){
        for(int i = 0; i < hashCount; i++){
            set(hash(s, seeds[i]));
        }
    }

    bool contains(const string& s){
        for(int i = 0;i<hashCount;i++){
            if(!get(hash(s, seeds[i]))){
                return false;
            }
        }
        return true;
    }

};


int main(){
    BloomFilter bf(1000, {31, 37, 41});
    bf.insert("Apple");
    bf.insert("Banana");
    bf.insert("Orange");

    cout << bf.contains("Apple") << endl;
    cout << bf.contains("Banana") << endl;
    cout << bf.contains("Grape") << endl;
}