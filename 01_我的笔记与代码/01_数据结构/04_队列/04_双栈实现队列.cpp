#include <iostream>
#include <queue>
using namespace std;




class MyStack {
public:
    MyStack() {
        q1 = new queue<int>;
        q2 = new queue<int>;
    }
    
    ~MyStack(){
        delete q1;
        delete q2;
        q1 = nullptr;
        q2 = nullptr;
    }
    void push(int x) {
        q1->push(x);
        while(!q2->empty()){
            q1->push(q2->front());
            q2->pop();
        }
        queue<int> *p = q1;
        q1 = q2;
        q2 = p;
    }
    
    int pop() {
        if(q2->empty()){
            throw"stack is empty!";
        }
        int tmp = q2->front(); // 先把队头元素拿出来存好
        q2->pop();             // 然后再把它从队列里踢掉
        return tmp;            // 最后归还给调用者
    }
    
    int top() {
        return q2->front();
    }
    
    bool empty() {
        return q2->empty();
    }
private:
    queue<int>* q1;
    queue<int>* q2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */