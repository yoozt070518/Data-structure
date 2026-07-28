// 括号匹配问题
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool IsValid(const string& s){
    stack<char> stk;
    for(char ch : s){
        if(ch=='(' || ch=='[' || ch=='{'){
            stk.push(ch);
        }else{
            if(stk.empty()){
                return false;
            }
            else if((stk.top()=='(' && ch==')')
        || (stk.top()=='[' && ch==']')
        || (stk.top()=='{' && ch=='}')){
            stk.pop();
        }else{
            return false;
        }
        }        
    }
    return stk.empty();
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        if(IsValid(s)){
            cout << "true\n";
        }else{
            cout << "false\n";
        }
    }
    return 0;
}