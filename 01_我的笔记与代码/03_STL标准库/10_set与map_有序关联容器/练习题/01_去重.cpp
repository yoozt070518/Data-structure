#include <iostream>
#include <vector>
#include <set>
using namespace std;



vector<int> dedupKeepOrder(const vector<int>& nums){
    set<int> s;
    vector<int> ans;
    for(auto n : nums){
        auto [it, inserted] = s.insert(n);
        if(inserted){
            ans.push_back(n);
        }
    }
    return ans;
}



int main(){
    vector<int> nums = {3, 1, 3, 4,1, 5, 4};
    vector<int> ans = dedupKeepOrder(nums);
    for(auto v : ans){
        cout << v << " ";
    }
    cout << endl;

    return 0;
}