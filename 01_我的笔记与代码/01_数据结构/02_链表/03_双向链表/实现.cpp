// 双向链表代码实现

#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* pre;
    Node(int val = 0)
        : data(val)
        , next(nullptr)
        , pre(nullptr)
    {}
};

// 双向链表
class DoubleLink{
public:
    DoubleLink(){
        head = new Node();
    }
    ~DoubleLink(){
        Node* p = head;
        while(p!=nullptr){
            head = head->next;
            delete p;
            p = head;
        }
    }
public:
    // 头插法
    void InsertHead(int val){
        Node* newNode = new Node(val);
        newNode->next = head->next;
        newNode->pre = head;
        if(head->next!=nullptr){
            head->next->pre = newNode;
        }
        head->next = newNode; 
    }

    // 尾插法
    void InsertTail(int val){
        Node* p = head;
        while(p->next!=nullptr){
            p = p->next;
        }
        Node* node = new Node(val);
        node->pre = p;
        p->next = node;
    }
    // 打印
    void Show() const{
        Node* p = head->next;
        while(p!=nullptr){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    //节点删除
    void Remove(int val){
        Node* p = head->next;
        while(p!=nullptr){
            if(p->data == val){
                p->pre->next = p->next;
                if(p->next!=nullptr){
                    p->next->pre = p->pre;
                }
                delete p;
                return;
            }
            p = p->next;   
        }
    }

    // 节点搜索
    bool Find(int val) const{
        Node* p = head->next;
        while(p!=nullptr){
            if(p->data == val){
                return true;
            }
            p = p->next;
        }
        return false;
    }
    
private:
    Node* head;
}; 
int main(){
    DoubleLink dlink;
    dlink.InsertTail(20);
    dlink.InsertTail(66);
    dlink.InsertTail(44);
    dlink.InsertTail(33);
    dlink.Show();
    dlink.InsertHead(23);
    dlink.InsertHead(13);
    dlink.InsertHead(55);
    dlink.InsertHead(99);
    dlink.Show();
    dlink.Remove(23);
    dlink.Show();
    dlink.Remove(99);
    dlink.Remove(33);
    dlink.Show();
    cout << dlink.Find(55) << endl;
    cout << dlink.Find(100) << endl;
    return 0;
}