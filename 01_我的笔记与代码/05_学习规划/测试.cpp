#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;





int main(){
    int n;
    cin >> n;
    stack<int> lst;
    stack<int> rst;
    vector<int> v(n);
    vector<int> left(n, -1);
    vector<int> right(n, n);
    for(int i = 0;i < n;++i){
        cin >> v[i];
        while(!lst.empty() && v[lst.top()] >= v[i]){
            lst.pop();
        }

        while(!rst.empty() && v[rst.top()] > v[i]){
            
            right[rst.top()] = i;
            rst.pop();
        }
        
        if(lst.empty()){
            left[i] = -1;
        }else{
            left[i] = lst.top();
        }
        lst.push(i);
        rst.push(i);
    }
    long long ans = 0;
    for(int i = 0;i < n;++i){
        long long tmp = v[i] * (right[i] - left[i] - 1);
        ans = max(ans, tmp);
    }
    cout << ans << endl;
}