#include <iostream>
#include <deque>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(){
    srand(time(NULL));
    deque<int> dq;
    for(int i = 0;i < 5;++i){
        dq.push_back(rand() % 100 + 1);
        dq.push_front(rand() % 100 + 1);
    }
    int* p = &dq[3]; 
    auto it = dq.begin() + 3;
    cout << *p << endl;
    for(int i = 0;i<1000;++i){
        dq.push_back(rand() % 100 + 1);
        dq.push_front(rand() % 100 + 1);
    }
    cout << *p << endl;// 由于没有进行跨Buffer的跃迁 p指向的依然是之前那个元素
    //但此时的it已经报废 因为node指针由于map中控器的变动已经报废 所以不能使用之前保存的迭代器
    it = dq.begin()+3;// 将it重新指回来
    dq.insert(dq.begin()+200,80);
    // 此时200位置前面的数据进行集体跨Buffer迁移 此时的p和it都会报废
    // p指针报废是因为Buffer内原有的数据由于大量跃迁导致之前的内存已经废掉
    // it报废是因为数据的大迁移导致内部的 first cur last node四个指针都报废 
    p = &dq[3]; 
    it = dq.begin() + 3;
    dq.erase(dq.begin()+342);
    // 与insert基本一致的原因


    return 0;
}