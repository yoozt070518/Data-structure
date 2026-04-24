#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


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
    struct Node{
        int data;
        Node* next;
        Node(int val = 0){
            data = val;
            next = nullptr;
        }    
    };
    Node* head;
    Node* tail; 
};
int main(){
    srand(time(NULL));
    CircleLink link;
    for(int i = 0;i<10;++i){
        link.InsertTail(rand()%100);

    }
    link.Show();
    link.InsertHead(rand()%100);
    link.Show();
    link.InsertHead(2);
    link.InsertTail(2);
    link.Show();
    cout << link.Find(2) << endl;
    link.Remove(2);
    link.Show();
    return 0;
}