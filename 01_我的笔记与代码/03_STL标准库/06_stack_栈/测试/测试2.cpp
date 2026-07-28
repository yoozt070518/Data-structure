#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;



int priority(char c){
    if(c=='+' || c=='-') return 1;
    else{
        return 2;
    }
}

vector<string> translate(const string& s){
    vector<string> ans;
    stack<char> op;
    for(size_t i = 0;i<s.size();++i){
        if(s[i] ==' ') continue;
        if(isdigit(s[i])){
            int x = 0;
            while (i < s.size() && isdigit(s[i])){
                x = x * 10 + (s[i] - '0');
                ++i;
            }
            ans.push_back(to_string(x));
            --i;
        }
        else if(s[i] == '('){
            op.push(s[i]);
        }
        else if(s[i] == ')'){
            while(op.top()!='('){
                string tmp(1, op.top());
                ans.push_back(tmp);
                op.pop();
            }
            op.pop();
        }
        else {
            while(!op.empty() && op.top()!='(' && priority(s[i]) <= priority(op.top())){
                string tmp(1, op.top());
                ans.push_back(tmp);
                op.pop();
            }
            op.push(s[i]);
        }
    }
    while(!op.empty()){
        string tmp(1, op.top());
        ans.push_back(tmp);
        op.pop();
    }
    return ans;
}

int calc(const vector<string>& tokens){
    stack<int> num;
    for(string s : tokens){
        if(s == "+" || s=="-" || s=="*" || s=="/"){
            int a = num.top();
            num.pop();
            int b = num.top();
            num.pop();
            if(s=="+") num.push(b+a);
            else if(s=="-") num.push(b-a);
            else if(s=="*") num.push(b*a);
            else if(s=="/") num.push(b/a);
        }else{
            num.push(stoi(s));
        }
    }
    return num.top();
}



int main(){
    int t;
    cin >> t;
    cin.ignore();
    while(t--){
        string s;
        getline(cin, s);
        vector<string> tokens = translate(s);
        cout << calc(tokens) << endl;
    }
    return 0;
}