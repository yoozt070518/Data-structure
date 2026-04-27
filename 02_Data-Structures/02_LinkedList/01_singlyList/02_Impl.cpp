// 代码实现



// 单链表：每一个节点只能找到下一个节点 无法回退到上一个节点
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 定义单链表节点
struct Node{
    int data;
    Node* next;
    Node(int val = 0){
        data = val;
        next = nullptr;
    }
};

class Clist {
public:
    Clist(){
        head = new Node();
    }
public:
    ~Clist(){
        // 节点的释放
        Node* p = head;
        while(p != nullptr){
            head = p->next;
            delete p;
            p = head;
        }
    }
    // O(n)
    void InsertTail(int val){
        Node* newNode = new Node(val);
        Node* curr = head;
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newNode; 
    }

    // O(1)
    void InsertHead(int val){
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
    }

    // 链表打印
    void Show(){
        Node* p = head->next;
        while(p!=nullptr){// 不要吃着碗里的看着锅里的
            // 这里不是为了找到尾节点 就不能用下一个节点来判断
            cout << p->data << " ";
            p=p->next;
        }
        cout << endl;
    }
    // 链表节点的删除（仅删除第一个值为val的节点就返回）
    void Remove(int val){
        // 1.搜索数据是val的节点
        // 2.删除目标节点
        Node* q = head;
        Node* p = head->next;
        while(p != nullptr){
            if(p->data == val){
                q->next = p->next;
                delete p;
                return;
            }else{
                q = p;
                p = p->next;
            }
        }
    }

    // 删除多个值为val节点
    void Removeall(int val){
        Node* q = head;
        Node* p = head->next;
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

    // 搜索接口
    bool find (int val) {
        Node* p = head->next;
        while(p != nullptr){
            if(p->data == val){
                return 1;
            }
            p=p->next;
        }
        return 0;
    }

private:
    Node* head;
};
int main(){
    Clist link;
    srand(time(0));
    for(int i = 0;i<10;++i){
        int val = rand() % 100;
        link.InsertTail(val);
        cout << val << " ";
    }
    cout << endl;
    link.Show();
    for(int i = 0;i < 10;++i){
        int val = rand() % 100;
        link.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;
    link.Show();
    link.InsertTail(200);
    link.Show();
    link.Remove(200);
    link.Show();
    link.InsertHead(23);
    link.InsertTail(23);
    link.Show();
    cout << link.find(23) << endl;
    link.Removeall(23);
    link.Show();
    cout << link.find(23) << endl;
    return 0;
}