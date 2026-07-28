// 逆波兰表达式求解
// 通过利用栈对数字进行入栈和出栈操作
// 可以实现对运算式子的求解

// 遇到数字 -> 输出
// 遇到字符 -> 将两个数字出栈并输出运算结果
// 返回最后一个数 即top



#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& s) {
        stack<int> cs;
        for(int i = 0;i<s.size();++i){
            if(s[i] == "+"){
                int num = cs.top();
                cs.pop();
                num += cs.top();
                cs.pop();
                cs.push(num);
            }
            else if(s[i] == "-"){
                int num = cs.top();
                cs.pop();
                num = cs.top() - num;
                cs.pop();
                cs.push(num);
            }
            else if(s[i] == "*"){
                int num = cs.top();
                cs.pop();
                num *= cs.top();
                cs.pop();
                cs.push(num);
            }
            else if(s[i] == "/"){
                int num = cs.top();
                cs.pop();
                num = cs.top() / num;
                cs.pop();
                cs.push(num);
            }else{
                cs.push(stoi(s[i]));
            }
        }
        return cs.top();
    }
};
int main(){
    return 0;
}