#include <iostream>
#include <cstring>
using namespace std;

// 顺序栈 c++容器适配器stack
class SeqStack{
public:
    SeqStack(int size = 10)
        : mtop(0)
        , mcap(size)
    {
        mpStack = new int[mcap];
    }
    ~SeqStack(){
        delete[] mpStack;
        mpStack = nullptr;
    }
    void push(int val){
        if(mtop == mcap){
            expand(2*mcap);
        }
        mpStack[mtop++] = val;
    }
    void pop(){
        if(mtop == 0){
            throw "stack is empty!";
        }
        mtop--;
    }
    int top () const{
        if(mtop == 0){
            throw "stack is empty!";
        }
        return mpStack[mtop-1];
    }
    bool empty() const{
        return mtop == 0;
    }
    int size() const{
        return mtop;
    }


private:
    void expand(int newsize){
        int* newmpStack = new int[newsize];
        memcpy(newmpStack,mpStack,sizeof(int)*mtop);
        delete[] mpStack;
        mpStack = newmpStack;
        mcap = newsize;
    }
    int* mpStack;
    int mtop;
    int mcap;
};
int main(){
    return 0;
}