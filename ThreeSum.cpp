/*Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]*/

// 思路是把3 sum问题拆分成2 sum问题，先从数组中取出一个数，之后还需要的两个数就是一个2 sum问题了
// 除此之外，2 sum问题也是有一种简便方法的，就是首先对数组进行排序，之后两个指针指向开头和结尾，这时
// 开始比较开头和结尾的和与我们需要的数字的大小，如和大于目标，则把尾巴指针向前移动一个，使得和变小
// 如果小于，反之移动开头指针，在一次遍历之内就能找到需要的2 sum了。同时，这种方法也能避免重复，因为2
// sum问题的重复都是来源于重复的数字，所以我们在遍历这个排好序的数组时，指针移动的时候可以跳过重复的数字，
// 从而达到去重的目的，比使用别的方法要简单许多。
// 3 sum高于2 sum一层，则需要一个额外指针指向一开始选中的数字，每次从这个数字后边的所有数组中运行2 sum
// 因为之前的数组都是扫描过的不需要重复扫描。同时，这个指针在移动时也可以跳过重复的数字，性能进一步提升
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        std::sort(nums.begin(),nums.end());
        int a=0,b=a+1,c=nums.size()-1;
        int temp,target;
        vector<vector<int>> result;
        for(;a<nums.size();a++)
        {
            target=-nums[a];
            b=a+1;
            c=nums.size()-1;
            while(c>b)
            {
                temp=nums[b]+nums[c];
                if(temp>target)
                {
                    c--;
                    for(;nums[c]==nums[c+1];c--)
                        ;
                }
                else if(temp<target)
                {
                    b++;
                    for(;nums[b]==nums[b-1];b++)
                        ;
                }
                else
                {
                    vector<int> temp_res=vector<int>();
                    temp_res.push_back(nums[a]);
                    temp_res.push_back(nums[b]);
                    temp_res.push_back(nums[c]);
                    result.push_back(temp_res);
                    b++;
                    c--;
                    for(;nums[c]==nums[c+1];c--)
                        ;
                    for(;nums[b]==nums[b-1];b++)
                        ;
                }
            }
            for(;nums[a]==nums[a+1];a++)
                ;
        }
        return result;
    }
};