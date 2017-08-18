/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

//使用vector遍历整个数组，寻找加合的另一个数，注意，我们第一层遍历数组之后，第二层遍历就不需要再计算第一层前边的元素和，但是这种遍历方法，依旧使得每个元素都和另一个元素组合过，是n方的复杂度
//time 216ms
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for(auto x=nums.begin();x!=nums.end();x++)
        {
            int temp=target-(*x);
            //不需要重复之前的元素，直接从x开始
            for(auto y=(x+1);y!=nums.end();y++)
            {
                if(temp==(*y))
                {
                    vector<int>* result=new vector<int>();
                    result->push_back((x-nums.begin()));
                    result->push_back((y-nums.begin()));
                    return *result;
                }
            }
        }
        return *(new vector<int>());
    }
};



//对于查找问题，完全可以使用hash，这里使用map之后，只需要遍历一次数组，对每个需要的补数，直接在hash中查找，整个程序复杂度为n
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> lookup_table;
        auto answer=new vector<int>();
        //对整个数组建表，之后的查找读hash表的话，复杂度为1
        for(auto i=nums.begin();i!=nums.end();i++)
        {
            lookup_table.insert(pair<int,int>(*i,(i-nums.begin())));
        }
        for(auto i=nums.begin();i!=nums.end();i++)
        {
            int temp=target-(*i);
            auto result=lookup_table.find(temp);
            if(result==lookup_table.end() || (result->second)==(i-nums.begin()))
                continue;
            answer->push_back(i-nums.begin());
            answer->push_back(result->second);
            return *answer;
        }
        return *answer;
    }
};
