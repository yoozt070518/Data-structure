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
    friend void MergeLink(Clist& link1,Clist& link2);
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
    void Show(){
        Node* p = head->next;
        while(p!=nullptr){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
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

void MergeLink(Clist& link1,Clist& link2){
    Node* p = link1.head->next;
    Node* q = link2.head->next;
    Node* last = link1.head;
    while(p != nullptr && q != nullptr){
        if(p->data < q->data){
            last->next = p;
            p = p->next;
            last = last->next;
        }else{
            last->next = q;
            q = q->next;
            last = last->next;
        }
    }
    if(p != nullptr){
        last->next = p;
    }else{
        last->next = q; 
    }
    link2.head->next = nullptr;
}



int main(){
    int arr[] = {1,3,5,11,15};
    int brr[] = {2,3,7,18};
    Clist link1;
    Clist link2;
    for(int v : arr){
        link1.Inserttail(v);
    }
    for(int v : brr){
        link2.Inserttail(v);
    }
    link1.Show();
    link2.Show();
    MergeLink(link1,link2);
    link1.Show();
    link2.Show();
    return 0;
}