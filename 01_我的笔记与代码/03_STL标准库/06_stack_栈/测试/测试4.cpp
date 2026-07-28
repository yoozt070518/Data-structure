#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    
    while(T--){
        int N;
        cin >> N;
        
        vector<int> temps(N);
        vector<int> ans(N,0);
        stack<int> max_s;
        for(int i = 0;i<N;++i){
            int t;
            cin >> t;
            temps[i] = t;
            while(!max_s.empty() && temps[max_s.top()] < temps[i]){
                ans[max_s.top()] = i - max_s.top();
                max_s.pop();
            }
            max_s.push(i);
        }
        for(int a : ans){
            cout << a << " ";
        }
        cout << "\n";




    }
    return 0;
}