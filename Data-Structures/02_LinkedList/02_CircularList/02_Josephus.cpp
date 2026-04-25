#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Node{
        int data;
        Node* next;
        Node(int val = 0){
            data = val;
            next = nullptr;
        }    
};

class CircleLink{
public:
    CircleLink(){
        head = new Node();
        tail = head;
        head->next = head;
    }
    ~CircleLink(){
        Node* curr = head->next;
        while(curr!=head){
            head->next = curr->next;
            delete curr;
            curr = head->next;
        }
        delete head;
    }
public:
    // 尾插法
    void InsertTail(int val){
        Node* node = new Node(val);
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }
    // 头插法
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next = head->next;
        head->next = node;
        if(node->next==head){
            tail = node;
        }
    }

    // 删除节点
    void  Remove(int val){
        Node* q = head;
        Node* p = head->next;
        while(p != head){
            if(p->data == val){
                q->next = p->next;
                delete p;
                if(q->next == head){
                    tail = q;
                }
                return;
            }
            p = p->next;
            q = q->next;
        }
    }

    // 查询
    bool Find(int val) const{
        Node* p = head->next;
        while(p != head){
            if(p->data == val){
                return true;
            }
            p = p->next;
        }
        return false;
    }
    void Show() const{
        Node* p  = head->next;
        while(p != head){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
private:
friend void Joseph(CircleLink& link, int k ,int m);
    Node* head;
    Node* tail; 
};

void Joseph(CircleLink& link, int k ,int m){
    if(link.head->next == link.head){
        return;
    }
    link.tail->next = link.head->next;
    Node* p = link.head->next;
    Node* q = link.tail;
    for(int i = 1;i<k;++i){
        q = p;
        p = p->next;
    }
    while(q!=p){
        for(int i = 1;i<m;++i){
            q = p;
            p = p->next;
        }
        cout << p->data << " ";
        q->next = p->next;
        delete p;
        p = q->next;
    }
    cout << p->data << endl;
    link.head->next = p;
    p->next = link.head;
    link.tail = p;
    
    
}






int main(){
    
    return 0;
}