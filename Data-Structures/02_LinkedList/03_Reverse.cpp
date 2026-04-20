// 单链表倒序问题



#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node(int val = 0){
        data = val;
        next = nullptr;
    }
};


class Clist{
    friend void ReverseLink(Clist& link); 
public:
    Clist(){
        head = new Node();
    }

    ~Clist(){
        Node* p = head;
        while(p != nullptr){
            head = p->next;
            delete p;
            p = head;
        }
    }
    
private:
    Node* head;
};

// 单链表逆序
void ReverseLink(Clist& link){
    Node* p = link.head->next;
    if(p == nullptr){
        return;
    }
    link.head->next = nullptr;
    while(p != nullptr){
        Node* q = p->next;
        p->next = link.head->next;
        link.head->next = p;
        p = q;
    }
}