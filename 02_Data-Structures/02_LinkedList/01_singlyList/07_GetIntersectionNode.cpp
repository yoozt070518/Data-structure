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
    friend bool IsLinkHasMerge(Node* head1,Node* head2,int& val);
    friend bool HascycGetentry(Clist& link, Node*& entry);
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

// 合并有序链表
void MergeLink(Clist& link1,Clist& link2){
    Node* p = link1.head->next;
    Node* q = link2.head->next;
    Node* last = link1.head;
    while(q != nullptr && p != nullptr){
        if(q->data <= p->data){
            last->next = q;
            q = q->next;
        }else{
            last->next = p;
            p = p->next;
        }
        last = last->next;
    }
    if(p == nullptr){
        last->next = q;
    }else{
        last->next = p;
    }
    link2.head->next = nullptr;
}

// 得到倒数第k个节点
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

// 判断是否存在环 并且找到这个环的入口
bool HascycGetentry(Clist& link, Node*& entry){
    Node* fast = link.head;
    Node* slow = link.head;
    while(fast!=nullptr&&fast->next!=nullptr){
        fast=fast->next->next;
        slow = slow->next;
        if(fast == slow){
            fast = link.head;
            while(fast!=slow){
                fast = fast->next;
                slow = slow->next;
            }
            entry = fast;
            return true;
        }
    }
    return false;
}

// 判断两个单链表是否相交 如果相交，返回相交节点的值
bool IsLinkHasMerge(Node* head1,Node* head2,int& val){
    int cnt1 = 0,cnt2 = 0;
    Node* p = head1;
    Node* q = head2;
    while(p!=nullptr){
        p=p->next;
        cnt1++;
    }
    while(q!=nullptr){
        q=q->next;
        cnt2++;
    }
    p = head1;
    q = head2;
    if(cnt1 >= cnt2){
        for(int i = 0;i<(cnt1-cnt2);++i){
            p = p->next;
        }
    }else{
        for(int i = 0;i<(cnt2-cnt1);++i){
            q = q->next;
        }
    }
    while(p!=nullptr&&q!=nullptr){
        if(p==q){
        val = p->data;
        return true;
    }
        p=p->next;
        q=q->next;
        
    }
    
    return false;
}


int main(){
    
    return 0;
}