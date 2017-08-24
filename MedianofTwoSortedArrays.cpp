/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

//原始思路无法通过，则不贴出代码。原始思路是A序列不动，遍历B序列，将B序列的元素插入A序列，这个操作不需要遍历所有B，因为遍历到A序列有总和长度的一半，就可以算出中位数了。对于时间复杂度，每一个B序列往A序列中插入都使用二分查找，复杂度为log(n)，但是因为要进行多次log(n)的插入操作，实际上复杂度为nlog(n)，超时不能通过。

//该题和数据结构关系不大，感觉纯粹是一个数学问题。因为两个序列已经有序，可以不需要第三个序列，直接在两个序列中操作找到中位数。基本思想是，两个序列各切一刀，之后左边的序列元素数量和右边相等，且左边的元素都小于右边，同时，因为两个序列都已经有序，则本序列中的切口右边肯定大于左边，则只需要对比两次就知道这一刀是否满足条件了。
//time:46ms
class Solution {
public:
    #define MAX 9999999999
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        int len_a=nums1.size();
        int len_b=nums2.size();
        if(len_b>len_a)
            return findMedianSortedArrays(nums2, nums1);
        int extend_len_a=(len_a*2+1);
        int extend_len_b=(len_b*2+1);
        int extend_len_half=(extend_len_a+extend_len_b)/2;
        int index2=(len_b*2+1)/2;
        float temp_a=0;
        float temp_b=0;
        int L1=0;
        int R1=0;
        int L2=0;
        int R2=0;
        while((index2>=0)&&(index2<extend_len_b))
        {
            int index1=extend_len_half-index2-1;
            L1=(index1==0)?(-MAX):nums1[(index1-1)/2];
            R1=((index1/2)>=len_a)?(MAX):nums1[index1/2];
            L2=(index2==0)?(-MAX):nums2[(index2-1)/2];
            R2=((index2/2)>=len_b)?(MAX):nums2[(index2/2)];
            if(L2>R1)
            {
                index2-=1;
            }
            if(L1>R2)
            {
                index2+=1;
            }
            if((L2<=R1)&&(L1<=R2))
            {
                temp_a=L2>L1?L2:L1;
                temp_b=R2>R1?R1:R2;
                break;
            }
        }
        return (temp_a+temp_b)/2;
    }
};

