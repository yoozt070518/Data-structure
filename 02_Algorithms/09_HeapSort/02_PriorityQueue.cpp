#include <iostream>
#include <functional>
#include <stdexcept>
using namespace std;

using Comp = function<bool(int, int)>;
class PriorityQueue{
public:
    PriorityQueue(int ini_cap = 20, Comp cmp = [](int a, int b){return a < b;})
    : size(0)
    , cap(ini_cap)
    , comp(cmp)
    {
        p = new int[cap];
    }
    ~PriorityQueue(){
        delete[] p;
        p = nullptr;
    }
    int parent(int i){return (i-1)/2;}
    int left(int i){return 2*i+1;}
    int right(int i){return 2*i+2;}

    void siftUp(int index){
        int i = index;
        int val = p[i];
        while(i > 0 && comp(p[parent(i)],val)){
            p[i] = p[parent(i)];
            i = parent(i);
        }
        p[i] = val;
    }

    void siftDown(int index){
        int i = index;
        int val = p[i];
        while(left(i) < size){
            int l = left(i);
            int r = right(i);
            int up_idx = l;
            if(r < size && comp(p[l],p[r])){
                up_idx = r;
            }
            if(!comp(val,p[up_idx])){
                break;
            }
            p[i] = p[up_idx];
            i = up_idx; 
        }
        p[i] = val;
    }

    void push(int val){
        if(size == cap){
            resize(2*size);
        }
        if(size==0){
            p[size] = val;
        }else{
        
        p[size] = val;
        siftUp(size);
        size++;
        }
        
    }

    void pop(){
        if(size==0){
            throw std::out_of_range("queue is empty!");
        }
        p[0] = p[size-1];
        size--;
        siftDown(0);
    }

    int top(){
        if(size==0){
            throw "queue is empty!";
        }
        return p[0];
    }
    bool empty(){return size==0;}
    int getsize(){return size;}

private:
    void resize(int newsize){
        int* newp = new int[newsize];
        for(int i = 0;i<size;++i){
            newp[i] = p[i];
        }
        cap = newsize;
        delete[] p;
        p = newp;
    } 
    int* p;
    int size;
    int cap;
    Comp comp;
};











int main(){


    return 0;
}