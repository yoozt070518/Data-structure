// 中缀转后缀表达式
// 在求表达式结果问题时 我们很难用编程语言去像正常计算一样的顺序
// 因此就出现了逆波兰表达式
// 而由正常表达式到逆波兰表达式的算法就叫调度场算法


// 逻辑如下：
// 1.数字 -> 输出
// 2.字符：
//     1.栈为空或栈顶为左括号：入栈
//     2.否则：
//          1.当前元素为右括号：出栈直到遇到左括号
//          2.当前元素优先级 > 栈顶元素 ：输出当前元素
//          3.当前元素优先级 <= 栈顶元素 ：出栈并让当前元素入栈


#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

/* class LinkedStack{
public:
    LinkedStack(int cap):
        size(0)
    {
        head = new Node();
    }
    ~LinkedStack(){
        Node* p = head;
        while(p!=nullptr){
            head = head->next;
            delete p;
            p = head;
        }
    }

    void push(int val){
        Node* p = new Node(val);
        p->next = head->next;
        head->next = p; 
    }

    void pop(){
        if(head->next == nullptr){
            throw("stack is empty!");
        }
        Node* p = head->next;
        head->next = p->next;
        delete p;
    }

    int top() const{
        return head->next->data;
    }

    
private:
    struct Node{
        int data;
        Node* next;
        Node(int val = 0): data(0),next(nullptr){}
    };
    Node* head;
    int size;

};
int getPriority(string op){
    if(op == "*" || op == "/"){
        return 2;
    }
    if(op == "+" || op == "-"){
        return 1;
    }
    if(op == "("){
        return 0;
    }
    return -1;
}
// 严谨的判断：字符串是否为有效数字
bool isNumber(const string& token){
    if(token.empty()) return false;
    // 如果是单独的减号 返回false
    if(token.size() == 1 && token == "-") return false;
    

    // 检查第一位（可以是负号 也可以是数字
    int startIndex = 0;
    if(token[0] == '-'){
        startIndex = 1;// 如果第一位是负号 从第二位开始检查数字
    }

    // 剩下的每一位 必须全都是数字！
    for(int i = startIndex;i < token.size();++i){
        if(!isdigit(token[i])){
            return false;// 只要有一个非数字则判错
        }
    } 
    return true;
}


// 中缀表达式 -> 后缀表达式
vector<string> InfixToPostfix(vector<string> token){
    vector<string> result;
    stack<string> s;
    for(string ch : token){
        if(isNumber(ch)){
            result.push_back(ch);
        }
        else if(ch == "("){
            s.push(ch);
        }
        else if(ch == ")"){
            // 一直出栈直到左括号
            while(!s.empty() && s.top() != "("){
                result.push_back(s.top());
                s.pop();
            }
            // 如果只剩左括号 把左括号也丢进垃圾桶
            if(!s.empty()){
                s.pop();
            }
        }
        else{
            while(!s.empty() && getPriority(s.top()) >= getPriority(ch)){
                result.push_back(s.top());
                s.pop();
            }
            s.push(ch);
        }
        while(!s.empty()){
            result.push_back(s.top());
            s.pop();
        }
        return result;
        
    }
} */
int getPriority(string op){
    if(op == "*" || op == "/"){
        return 2;
    }
    if(op == "+" || op == "-"){
        return 1;
    }
    if(op == "("){
        return 0;
    }else{
        return -1;
    }
}

bool isNumber(const string& op){
    if(op.empty()) return false;
    int StartIndex = 0;
    if(op.size()==1 && op[0] == '-') return false;
    if(op[0] == '-') StartIndex = 1;
    for(int i = StartIndex;i<(int)op.size();++i){
        if(!isdigit(op[i])){
            return false;
        }
    }
    return true;
}





vector<string> InfixToPostfix(const vector<string>& token){
    vector<string> ret;
    stack<string> s;
    for(string ch : token){
        if(isNumber(ch)){
            ret.push_back(ch);
        }
        else if(ch == "("){
            s.push(ch);
        }
        else if(ch == ")"){
            while(!s.empty() && s.top() != "("){
                ret.push_back(s.top());
                s.pop();
            }
            if(!s.empty()){
                s.pop();
            }
        }
        else{
            while(!s.empty() && getPriority(s.top()) >= getPriority(ch)){
                ret.push_back(s.top());
                s.pop();
            }
            s.push(ch);
        }
       
    } 
    while(!s.empty()){
        ret.push_back(s.top());
        s.pop();
    }   
    return ret;
}








int main(){
    vector<string> s = {"2","+","(","4","+","6",")","*","8"};
    vector<string> ret = InfixToPostfix(s);
    for(string ch : ret){
        cout << ch << " ";
    }
    cout << endl;
    return 0;
}
