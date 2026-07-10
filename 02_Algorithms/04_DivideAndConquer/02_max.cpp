#include <iostream>
#include <vector>
using namespace std;

int getMax(const vector<int>& vec, int left, int right){
    if(left == right){
        return vec[left];
    }

    int mid = left + (right - left) / 2;
    int lm = getMax(vec, left, mid);
    int rm = getMax(vec, mid+1, right);

    return max(lm, rm);
}


int main(){
     vector<int> nums = {3, 1, 7, 2, 9, 4};

    int ans = getMax(nums, 0, nums.size() - 1);

    cout << ans << "\n";

    return 0;
}