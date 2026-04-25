// 约瑟夫环问题
// 已知n个人围坐在一张圆桌周围，编号为k的人开始报数
// 数到m的那个人出列，它的下一个人又开始从1报数，数到m的人又出列
// 依次规律重复
// 知道全部出列，输出人的出列顺序

// 先重写一遍环形链表的类
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

void Joseph(Node* head, int k ,int m){
    if (head == nullptr) return;
    Node* p = head;
    Node* q = head;
    while(q->next!=head){
        q = q->next;
    }
    for(int i = 1;i<k;++i){
        q = p;
        p = p->next;
    }
    while(1){
        for(int i = 1;i<m;++i){
            q = p;
            p = p->next;
        }
        
        cout << p->data << " ";
        if(p==q){
            delete p;
            break;
        }
        q->next = p->next;
        delete p;
        p = q->next;

    }
    
}
int main(){
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    head->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    n7->next = n8;
    n8->next = head;
    Joseph(head,1,1);
}