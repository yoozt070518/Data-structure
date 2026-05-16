#include <iostream>
#include <stack>
#include <deque>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N, k;
        cin >> N >> k;
        vector<int> v(N);
        deque<int> dq;
        vector<int> nums;
        for(int i = 0;i < N;++i){
            int x;
            cin >> x;
            v[i] = x;
            if(!dq.empty()){
                if(dq.front() < i-k+1){
                    dq.pop_front();
                } 
            }
            while(!dq.empty() && x >= v[dq.back()]){
                    dq.pop_back();
            }
            dq.push_back(i);
            if(i >= k - 1){
                cout << v[dq.front()] << " ";
            }
        }
        cout << '\n';

    }
    return 0;
}