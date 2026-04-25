// 链表的倒数第k个节点


// 重写一遍链表结构
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int val = 0) {
        data = val;
        next = nullptr;
    }
};

class Clink{
    friend bool GetlastkNode(Clink& link, int k, int& val);
    friend void Reverselist(Clink& link);
private:
    Node* head;
public:
    Clink(){
        head = new Node();
    }

    ~Clink(){
        Node* p = head;
        while(p != nullptr){
            head = p->next;
            delete p;
            p = head;
        }
    }

    // 头插
    void InsertHead(int val){
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
    }

    // 尾插
    void InsertTail(int val){
        Node* newNode = new Node(val);
        Node* p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = newNode;
    }

    // 查找
    bool find(int val){
        Node* p = head->next;
        while(p != nullptr){
            if(p->data == val){
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // 删除一个
    void Remove(int val){
        Node* p = head->next;
        Node* q = head;
        while(p != nullptr){
            if(p->data == val){
                q->next = p->next;
                delete p;
                return;
            }
            q = p;
            p = p->next;
        }
    }

    // 全删
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
                p = p->next;
            }
        }
    }

    // 打印
    void Show(){
        Node* p = head->next;
        while(p != nullptr){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

}; 
// 链表反转
void Reverselist(Clink& link){
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

// 求倒数第k个节点
bool GetlastkNode(Clink& link, int k, int& val){
    if(k <= 0){
        return false;
    }
    Node* p = link.head;
    Node* pre = link.head;
    for(int i =0 ;i<k;i++){
        p = p->next;
        if(p == nullptr){
            return false;
        }
    }
    while(p!=nullptr){
        p=p->next;
        pre=pre->next;
    }
    val = pre->data;
    return true;
}


int main(){
    system("chcp 65001");
    srand(time(0));
    Clink link;
    for(int i = 0;i<10;i++){
        int n = rand() % 51 + 50;
        link.InsertTail(n);
        cout << n << " ";
    }
    cout << endl;
    link.Show();
    for(int i = 0;i<5;i++){
        int n = rand() % 51 + 50;
        link.InsertHead(n);
        cout << n << " ";
    }
    cout << endl;
    link.Show();
    link.InsertTail(23);
    link.Show();
    cout << link.find(23) << endl;
    link.Remove(23);
    link.Show();
    cout << link.find(23) << endl;
    link.InsertHead(23);
    link.InsertTail(23);
    link.Show();
    link.RemoveAll(23);
    link.Show();
    int vval;
    int k = 3;
    if(GetlastkNode(link,k,vval)){
        cout << "倒数第" << k << "个节点的值：" << vval << endl;
    }
    return 0;
}