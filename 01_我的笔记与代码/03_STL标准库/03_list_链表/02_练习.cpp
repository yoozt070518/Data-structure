#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;


int main(){
    srand(time(NULL));
    list<int> L1;
    list<int> L2;
    for(int i =0;i<10;++i){
        L1.push_back(rand()%100+1);
        L2.push_back(rand()%100+1);
    }
    for(auto it = L1.begin();it != L1.end();++it){
        cout << *it << " ";
    }
    cout << endl;
    for(auto it = L2.begin();it != L2.end();++it){
        cout << *it << " ";
    }
    cout << endl;
    auto it3 = L2.begin();
    ++it3;
    ++it3;
    // 此时it3指向的是L2的第3个元素
    auto it1 = L1.begin();
    ++it1;
    auto it2 = L2.end();
    --it2;
    --it2;
    L1.splice(it1,L2,L2.begin(),it2);
    for(auto it = L1.begin();it != L1.end();++it){
        cout << *it << " ";
    }
    cout << endl;
    // 在执行完splice之后 L2的前面一长段包括it3被接入了L1
    cout << *it3 << endl;
    // 此时的it3指向的是L1的第四个元素
    --it3;
    --it3;
    --it3;
    // 经过三次--操作后指向的是原来L1的第一个元素
    // 如果打印出来刚好是L1的第一个元素就证明L2的前面一长段包括it3被接入了L1
    cout << *it3 << endl;
    return 0;
}