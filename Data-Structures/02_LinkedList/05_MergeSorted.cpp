// 合并两个有序单链表


// 重写前面的接口
#include <iostream>
#include <cstdlib>
#include <ctime>
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
    friend void MergeSortedList(Clist& link1,Clist& link2);
    friend bool GetlastkNode(Clist& link,int k,int& kval);
    friend void ReverseList(Clist& link);
private:
    Node* head;
public:
    Clist(){
        head = new Node();
    }
    ~Clist(){
        Node* p = head;
        while(p!=nullptr){
            head = p->next;
            delete p;
            p = head;
        }
    }
    // 头插
    void InsertHead(int val){
        Node* newNode = new Node(val);
        newNode->next=head->next;
        head->next = newNode;
    }

    // 尾插
    void Inserttail(int val){
        Node* newNode = new Node(val);
        Node* curr = head;
        while(curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = newNode;
    }

    //搜索
    bool find(int val){
        Node* p = head->next;
        while(p!=nullptr){
            if(p->data==val){
                return true;
            }
            p = p->next;
        }
        return false;
    }

    void Remove(int val){
        Node* p = head->next;
        Node* q = head;
        while(p!=nullptr){
            if(p->data == val){
                q->next = p->next;
                delete p;
                return;
            }
            q = p;
            p = p->next;
        }
    }

    void RemoveAll(int val){
        Node* p = head->next;
        Node* q = head;
        while(p != nullptr){
            if(p->data == val){
                q->next = p->next;
                delete p;
                p = q->next;
            }else{
                q = p;
                p=p->next;
            }
        }
    }
};

void ReverseList(Clist& link){
    Node* p = link.head->next;
    if(p == nullptr){
        return;
    }
    link.head->next = nullptr;
    while(p!=nullptr){
        Node* q = p->next;
        p->next = link.head->next;
        link.head->next = p;
        p = q;
    }
}

bool GetlastkNode(Clist& link,int k,int& kval){
    if(k < 1){
        return false;
    }
    Node* p = link.head;
    Node* pre = link.head;
    for(int i = 0;i<k;++i){
        p = p->next; 
        if(p == nullptr){
            return false;
        }
    }
    while(p!=nullptr){
        p=p->next;
        pre=pre->next;
    }
    kval = pre->data;
    return true;
}

void MergeSortedList(Clist& link1,Clist& link2){
    Node* p = link1.head->next;
    Node* q = link2.head->next;
    Node* last = link1.head;
    while(q != nullptr){
        if(p == nullptr ||q->data <= p->data){
            last->next = q;
            q = q->next;
            last = last->next;
            if(q == nullptr){
                last->next = p;
                break;
            }
        }else {
            last->next = p;
            p = p->next;
            last = last->next;
        }
    }
    link2.head->next = nullptr;
}




int main(){
    return 0;
}