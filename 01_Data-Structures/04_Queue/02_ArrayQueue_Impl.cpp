#include <iostream>
using namespace std;


class Queue{
private:
    int* p_;
    int size_;
    int capacity_;
    int first;
    int rear;
    void expand(int newcap){
        int* q_ = new int[newcap];
        int i = 0;
        int j = first;
        for(;j!=rear;++i,j=(j+1)%capacity_){
            q_[i] = p_[j];
        }
        delete[] p_;
        p_ = q_;
        capacity_ = newcap;
        first = 0;
        rear = i;
    }
public:
    Queue(int cap)
    : size_(0)
    , capacity_(cap)    
    , first(0)
    , rear(0)
    {
        p_ = new int[cap];
    }

    ~Queue(){
        delete[] p_;
    }

    void push(int val){
        if((first + 1) % capacity_ == rear){
            expand(2 * capacity_);
        }
        p_[rear] = val;
        rear = (rear+1) % capacity_;
        size_++;
    }

    void pop(){
        if(first == rear){
            throw std::out_of_range("queue is empty!");
        }
        first = (first+1) % capacity_;
        size_--;
    }

    int front() const{
        if(first == rear){
            throw std::out_of_range("queue is empty!");
        }
        return p_[first];
    }

    int back() const{
        if(first == rear){
            throw std::out_of_range("queue is empty!");
        }
        return p_[(rear-1+capacity_) % capacity_];
    }

    bool empty() const{
        return first == rear;
    }

    int size() const{
        return size_;
    }
};

int main(){
    



    return 0;
}