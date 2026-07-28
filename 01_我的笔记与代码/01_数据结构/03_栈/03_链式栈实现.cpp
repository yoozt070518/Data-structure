#include <iostream>
using namespace std;
// ! 数组结构在数据量比较大时会一直重复扩容操作
// ? 而链表在扩容这块效率较高


// *链式栈
class LinkStack{
public:
    LinkStack():size(0){
        head = new Node();
    }
    ~LinkStack(){
        Node* p = head;
        while(p!=nullptr){
            head = head->next;
            delete p;
            p = head;
        }
    }
public:
    void push(int val){
        Node* p = new Node(val);
        p->next = head->next;
        head->next = p;
        size++;
    }
    void pop(){
        if(head->next == nullptr){
            throw "stack is empty!";
        }
        Node* p = head->next;
        head->next = p->next;
        delete p;
        size--;
    }
    int top() const{
        if(head->next == nullptr){
            throw "stack is empty!";
        }
        return head->next->data;
    }
    bool empty() const{
        return head->next==nullptr;
    }
    int getsize() const{
        return size;
    }
private:
    struct Node{
        int data;
        Node* next;
        Node(int val = 0):data(val),next(nullptr){}
    };
    Node* head;
    int size;
};




int main(){
    return 0;
}