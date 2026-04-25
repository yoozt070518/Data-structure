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
    friend void Reverse(Clist& link);
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

// 单链表逆序 利用头插法
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

// 法2 直接反转
void Reverse(Clist& link){
    Node* prev = nullptr;
    Node* curr = link.head->next;
    while(curr!=nullptr){
        Node* nexttemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nexttemp;
    }
    link.head->next = prev;
}