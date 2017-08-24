/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"
*/

//比较容易想到的算法其实就是快速算法：在整个序列中寻找AA或者ABA的结构，找到后向四周
//展开窗口判断是否回文，直到生长到不回文时，记录下长度，然后继续往后寻找中心结构
//因为这两个结构是唯一可能的镜像中心，所以回文序列一定是一这个中心开始的
//但是AA和ABA的处理逻辑稍有不同，导致直接这么写的话，分支很多，逻辑复杂
//实际上和之前两个序列找中位数一样，逻辑有分支是因为奇偶数的原因，这种时候，都可以通过
//添加中间元素的方法统一
//time:12ms
class Solution {
public:
    string longestPalindrome(string s) 
    {
        int index=1;
        int longest_index=0;
        int longest_length=0;
        int length=0;
        int str_len=s.size();
        if(str_len==1)
            return s;
        int b=0,e=0;
        for(;index<str_len;index++)
        {
            if((s[index]==s[index-1]))
            {
                b=index-1;
                e=index;
                for(;(b>0)&&(e<str_len-1);)
                {
                    if(s[b-1]!=s[e+1])
                        break;
                    b=b==0?0:(b-1);
                    e=(e+1)>=str_len?str_len-1:e+1;
                }
                if((e-b+1)>longest_length)
                {
                    longest_length=(e-b+1);
                    longest_index=index;
                }
            }
            if(index>=2)
            if((s[index]==s[index-2]))
            {
                b=index-2;
                e=index;
                for(;(b>0)&&(e<str_len-1);)
                {
                    if(s[b-1]!=s[e+1])
                        break;
                    b=b==0?0:(b-1);
                    e=(e+1)>=str_len?str_len-1:e+1;
                }
                if((e-b+1)>longest_length)
                {
                    longest_length=(e-b+1);
                    longest_index=index;
                }
            }
        }
        int begin_index=0;
        if(longest_length==0)
            return s.substr(0,1);
        if(longest_length%2==0)
        {
            begin_index=longest_index-(longest_length/2);
        }
        else
        {
            begin_index=longest_index-(longest_length-1)/2-1;
        }
        return s.substr(begin_index, longest_length);
    }
};


//添加中间元素实现奇偶处理方法的统一，如原始序列为
//abccba －> a#b#c#c#b#a
//则中心可能存在与任何一个字母或者#上
//很方便的统一了奇偶元素的序列，同时访问原始数据也不受#的影响，因为无论在那个位置
//其左边的字母为(i-1)/2，右边最近的字母为i/2，右边下一个字母为i/2+1
class Solution {
public:
    string longestPalindrome(string s) 
    {
        int str_len=s.size();
        if(str_len==1)
            return s;
        //扩展整个序列，使得奇偶可以一视同仁
        int extend_len=str_len*2-1;
        int index=1;
        int b=0,e=0;
        int longest_length=0;
        int longest_index=0;
        //以扩展之后的下标遍历序列，因为中心可能出现在两个字母的中间
        for(;index<extend_len;index++)
        {
            //上一个字母的原始坐标
            b=(index-1)/2;
            //下一个字母的原始坐标
            e=(index/2)+1;
            if(s[b]==s[e])
            {
                for(;(b>0)&&(e<str_len-1);)
                {
                    if(s[b-1]!=s[e+1])
                        break;
                    b-=1;
                    e+=1;
                }
                if((e-b+1)>longest_length)
                {
                    longest_length=(e-b+1);
                    longest_index=b;
                }
            }
        }
        if(longest_length==0)
            return s.substr(0,1);
        return s.substr(longest_index, longest_length);    
    }
};