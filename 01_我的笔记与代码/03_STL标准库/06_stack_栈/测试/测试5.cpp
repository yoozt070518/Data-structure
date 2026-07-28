#include <iostream>
#include <stack>
using namespace std;



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
       string s;
       cin >> s;
       stack<int> num;
       stack<string> strs;
       int current_num = 0;
       string current_str = "";
       for(size_t i = 0;i<s.size();++i){
            if(isdigit(s[i])){
                int x = 0;
                while(i<s.size() && isdigit(s[i])){
                    x = x*10 + (s[i] - '0');
                    ++i;
                }
                current_num = x;
                --i;
            }
            else if(s[i] == '['){   
                strs.push(current_str);
                num.push(current_num);
                current_num = 0;
                current_str = "";
            }
            else if(s[i] == ']'){
                int k = num.top();
                num.pop();
                string prev_str = strs.top();
                strs.pop();
                while(k--){
                    prev_str += current_str;
                }
                current_str = prev_str;
            }
            else{
                current_str += s[i];
            }
       }
       cout << current_str << "\n";
    }    



    return 0;
}