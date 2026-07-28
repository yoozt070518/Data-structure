#include <iostream>
#include <vector>
using namespace std;





int main(){
    int n;
    cin >> n;
    int target;
    cin >> target;
    vector<int> nums(n);
    int left = 0;
    int right = nums.size()-1;
    int ans = nums.size();
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] >= target){
            ans = mid;
            right = mid - 1;
        }else{
            left = mid+1;
        }
    }



    return 0;
}