// 力扣27移除元素




// 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。

// 假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：

// 更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
// 返回 k。
#include<iostream>
#include <vector>
using namespace std;
// 写法1
// class Solution {
// public:
//     int removeElement(vector<int>& nums, int val) {
//         int l = 0;
//         int r = nums.size();
//         while(l<r){
//             if(nums[r-1] == val){
//                 r--;
//                 continue;
//             }
//             if(nums[l] == val){
//                 nums[l] = nums[r-1];
//                 r--;
                
//             }else{
//                 l++;
                
//             }
//         }
//         return l;
//     }
// };

// 写法2
// class Solution {
// public:
//     int removeElement(vector<int>& nums, int val) {
//         int left = 0;
//         int right = nums.size(); // right 指向有效数组的下一个位置（即当前有效长度）
        
//         while (left < right) {
//             if (nums[left] == val) {
//                 // 如果左边遇到了 val，把它和最后一个有效元素交换
//                 // 并且有效长度 right 减一
//                 nums[left] = nums[right - 1]; 
//                 right--; 
//                 // 注意：交换过来后，left 不能加 1，因为换过来的新数字还要在下一轮继续判断！
//             } else {
//                 // 只有当 left 指向的不是 val 时，left 才可以安全后移
//                 left++; 
//             }
//         }
//         return right; // right 最终就是剩下的有效元素个数
//     }
// };



// 写法3 快慢指针
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                // 发现有效元素，把它塞到 slow 的位置
                nums[slow] = nums[fast];
                slow++; // 准备放下一个
            }
        }
        // slow 走了几步，就有几个有效元素
        return slow; 
    }
};