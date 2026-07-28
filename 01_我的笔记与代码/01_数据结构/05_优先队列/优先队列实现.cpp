#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;

template <typename T>
using Comp = function<bool(const T&, const T&)>;

template <typename T>
class MyPriorityQueue{
public:
    MyPriorityQueue  (Comp<T> cmp = [](const T& a, const T& b){return a > b;}) {
        comp = cmp;
    }
    int parent(int i){return (i-1)/2;}
    int left(int i){return 2*i+1;}
    int right(int i){return 2*i+2;}
    
    void SiftUp(int i){
        T val = v[i];
        while(i > 0 && comp(v[parent(i)],val)){
            v[i] = v[parent(i)];
            i = parent(i);
        }
        v[i] = val;
    }

    void SiftDown(int i){
        T val = v[i];
        int n = v.size();
        while(left(i) < n){
            int child = left(i);
            if(right(i) < n && comp(v[left(i)], v[right(i)])){
                child++;
            }
            if(!comp(val ,v[child])){
                break;
            }
            v[i] = v[child];
            i = child;
        }
        v[i] = val;
    }

    void push(T val){
        v.push_back(val);
        SiftUp(v.size()-1);
    }

    void pop(){
        if(v.empty()){
            throw out_of_range("Queue is empty!");
        }
        swap(v[0], v.back());
        v.pop_back();
        if(!v.empty()){
            SiftDown(0);
        }
    }

    T top() const{
        if(v.empty()){
            throw out_of_range("Queue is empty!");
        }
        return v.front();
    }

    bool empty() const{
        return v.empty();
    }

    size_t size() const{
        return v.size();
    }
private:
    vector<T> v;
    Comp<T> comp;
};

int main(){
    return 0;
}