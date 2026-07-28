#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Complex{
public:
    int real;
    int image;
public:
    Complex(int a,int b)
    : real(a)
    , image(b)
    {

    }
};



int main(){
    vector<Complex> vec;
    vec.reserve(10);
    srand(time(NULL));
    for(int i = 0;i<5;++i){
        vec.push_back(Complex(rand() % 100 + 1,rand() % 100 + 1));
    }
    for(auto it = vec.begin(); it != vec.end();++it){
        cout << it->real << "+" << it->image << "i "; 
    }
    cout << endl;
    for(int i = 0;i<5;++i){
        vec.emplace_back(rand() % 100 + 1,rand() % 100 + 1);
    }
    for(auto it = vec.begin(); it != vec.end();++it){
        cout << it->real << "+" << it->image << "i "; 
    }
    cout << endl;
    // 删除实部为奇数 虚部为偶数的复数
    for(auto it = vec.begin();it != vec.end();){
        if(it->real % 2 == 1 && it->image % 2 == 0){
            it = vec.erase(it);
        }else{
            ++it;
        }
    }
    for(auto it = vec.begin(); it != vec.end();++it){
        cout << it->real << "+" << it->image << "i "; 
    }
    cout << endl;
    vec.shrink_to_fit();
    if(vec.size() == vec.capacity()){
        cout << "内存已收缩" << endl;
    }
    cout << endl;
}