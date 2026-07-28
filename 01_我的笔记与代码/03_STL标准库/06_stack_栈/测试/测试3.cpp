#include <iostream>
#include <stack>
#include <deque>
#include <stdexcept>
using namespace std;




class MinStack{
private:
    stack<int> data_s;
    stack<int> min_s;
public:
    void push(int val){
        data_s.push(val);
        if(min_s.empty()){
            min_s.push(val);
        }else{
            if(val <= min_s.top()){
                min_s.push(val);
            }
        }
    }
    bool empty(){
        return data_s.empty();
    }
    void pop(){
        if(data_s.empty()) throw out_of_range("stack is empty!");
        if(data_s.top() == min_s.top()){
            min_s.pop();
        }
        data_s.pop();
    }
    int top(){
        if(data_s.empty()) throw out_of_range("stack is empty!");
        return data_s.top();
    }
    int getMin(){
        if(data_s.empty()) throw out_of_range("stack is empty!");
        return min_s.top();
    }
}; 


int main(){
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
   cout << minStack.getMin() << endl; // 返回 -3
    minStack.pop();
    cout << minStack.top() << endl;    // 返回 0
    cout << minStack.getMin() << endl;  // 返回 -2



    return 0;
}