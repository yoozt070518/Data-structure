#include <iostream>
using namespace std;


// 链式队列
class Queue{
public:
    Queue(){
        head = new Node();
        head->next_ = head;
        head->pre_ = head;
        size = 0;
    }
    ~Queue(){
        Node* p = head->next_;
        while(p!=head){
            head->next_ = p->next_;
            p->next_->pre_ = head;
            delete p;
            p = head->next_;
        }
        delete head;
        head = nullptr;
    }
    void push(int val){
        Node* node = new Node(val);
        node->next_ = head;
        node->pre_ = head->pre_;
        head->pre_->next_ = node;
        head->pre_ = node;
        size++;
    }

    void pop(){
        if(head->next_ == head){
            throw "queue is empty!";
        }
        Node* p =head->next_;
        head->next_ = p->next_;
        p->next_->pre_ = head;
        delete p;
        p = nullptr;
        size--;
    }

    int front()const{
        if(head->next_ == head){
            throw "queue is empty!";
        }
        return head->next_->data_;
    }

    int back()const{
        if(head->next_ == head){
            throw "queue is empty!";
        }
        return head->pre_->data_; 
    }

    bool empty()const{
        return head->next_==head;
    }

    int getsize() const{
        return size;
    }

private:
struct Node{
    int data_;
    Node* next_;
    Node* pre_;
    Node(int val = 0){
        data_ = val;
        next_ = nullptr;
        pre_  = nullptr;
    }
};
    Node* head;
    int size;

};









int main(){

    return 0;
}