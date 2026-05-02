// 有效的括号
// 括号的匹配完美契合栈结构里面的先进后出 后进先出
// 因此可以用stack来进行储存数字

#include <iostream>
#include <string>
#include <stack>
using namespace std;




class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(int i = 0;i<s.size();++i){
            if(s[i] == '{' || s[i] == '(' || s[i] == '['){
                stk.push(s[i]);
            }else{
                if(stk.empty()){
                    return false;
                }else{
                    if(s[i] == ')' && stk.top() == '('
                    || s[i] == ']' && stk.top() == '['
                    || s[i] == '}' && stk.top() == '{'){
                        stk.pop();
                    }else{
                        return false;
                    }
                }
            }
            
        }
        return stk.empty();
    }
};