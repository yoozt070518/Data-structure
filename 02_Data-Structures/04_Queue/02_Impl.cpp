// 环形队列代码实现
#include <iostream>
using namespace std;

// queue push pop front back empty size
class Queue{
public:
    Queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        {
            pQue_ = new int[cap_];
        }
    ~Queue(){
        delete pQue_;
        pQue_ = nullptr;
    }
    // 入队
    void push(int val){
        if((rear_+1) % cap_ == front_){
            expand(2*cap_);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
    }

    // 出队
    void pop(){
        if(front_ == rear_){
            throw "queue is empty!";
        }
        front_ = (front_ + 1) % cap_;
    }

    // 队头元素
    int front() const{
        if(front_ == rear_){
            throw "queue is empty!";
        }
        return pQue_[front_];
    }

    // 队尾元素
    int back() const{
        if(front_ == rear_){
            throw "queue is empty!";
        }
        return pQue_[(rear_-1)%cap_];
    }
private:
    void expand(int newcap){

    }
    int* pQue_;
    int cap_; // 空间容量
    int front_; // 队头
    int rear_; // 队尾
};








int main(){






    return 0;
}