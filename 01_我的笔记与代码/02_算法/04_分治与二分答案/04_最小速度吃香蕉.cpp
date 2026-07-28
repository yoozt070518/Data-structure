#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


bool canFinish(const vector<int>& nums, int h, int k){
    long long hours = 0;

    for (int pile : nums)
    {
        hours += (pile + k - 1) / k;
    }

    return hours <= h;
    
}

int getMinSpeed(const vector<int>& nums, int h){
    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    int ans = right;

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(canFinish(nums, h, mid)){
            ans = mid;
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return ans;
}


int main(){
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    cout << getMinSpeed(piles, h) << "\n";
    return 0;
}