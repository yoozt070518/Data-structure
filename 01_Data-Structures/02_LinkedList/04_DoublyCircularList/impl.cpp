// 双向循环链表代码实现

#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* prev;
    Node(int val = 0){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class DoubleCircleLink{
public:
    DoubleCircleLink(){
        head = new Node();
        head->prev = head;
        head->next = head;
    }
    ~DoubleCircleLink(){
        Node* p = head->next;
        while(p!=head){
            p->next->prev = head;
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
    }
    // 头插
    void InsertHead(int val){
        Node* node = new Node(val);
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // 尾插
    void InsertTail(int val){
        Node* node = new Node(val);
        node->next = head;
        node->prev = head->prev;
        head->prev->next = node;
        head->prev = node;
    }

    // 查找
    bool Find(int val){
        Node* p = head->next;
        while(p!=head){
            if(p->data == val){
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // 删除
    void Remove(int val){
        Node* p = head->next;
        while(p!=head){
            if(p->data==val){
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                return;
            }
            p = p->next;
        }
    }

    // 打印
    void Show(){
        Node* p = head->next;
        while(p!=head){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
        
    }

private:
    Node* head;
};
int main(){
    DoubleCircleLink dlink;
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