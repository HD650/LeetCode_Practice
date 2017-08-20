/*
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/


//遍历整个字符串，并且使用一个set来判断是否出现重复字符。每次遇到重复字符之后，返回这一次遍历的开头，并向后推一个字符再次遍历。
//time:432ms
class Solution {
public:
    int longest=0;
    const char* index=NULL;
    int lengthOfLongestSubstring(string s) 
    {
        char* data=(char*)s.c_str();
        for(;(*data)!='\0';)
        {
            data=parse_string(data);
        }
        return longest;
    }
    
    char* parse_string(char* s)
    {
        set<char> lookup;
        char* begin=s;
        int length=0;
        for(;(*s)!='\0';s++)
        {
            auto res=lookup.find(*s);
            if(res==lookup.end())
            {
                lookup.insert(*s);
                length+=1;
            }
            else
            {
                if(length>longest)
                {
                    longest=length;
                    index=begin;
                }
                return begin+1;
            }
        }
        if(length>longest)
        {
            longest=length;
            index=begin;
        }
        return begin+1;
    }
};

//改进了代码结构，对遍历开头的控制应该放在工作函数外边，其次，每次找到重复之后，只需要从重复字符出现的那一点开始下次遍历，不需要从这次遍历的开始重启。（这个方法还有问题，即每次重新遍历，被遍历字符串再一次缩小为常度1，然后慢慢扩充，其实是没必要的）
//time: 422ms
class Solution {
public:
    int longest=0;
    int lengthOfLongestSubstring(string s) 
    {
        char* data=(char*)s.c_str();
        int step=0;
        for(;(*data)!='\0';)
        {
            data=data+step;
            step=parse_string(data);
        }
        return longest;
    }
    
    int parse_string(char* s)
    {
        map<char, int> lookup;
        char* loc=s;
        int length=0;
        auto res=lookup.begin();
        for(;(*loc)!='\0';loc++)
        {
            res=lookup.find(*loc);
            if(res==lookup.end())
            {
                length+=1;
                lookup.insert(pair<char, int>(*loc, loc-s));
            }
            else
            {
                if(length>longest)
                    longest=length;
                return res->second+1;  
            }
        }
        if(length>longest)
            longest=length;
        return loc-s;
    }
        
};



//更快的写法，对于一个字符串或者数组相邻元素的扫描，可以使用滑动窗口，和上一个写法的思路类似，但是能减少很多重复的计算，因为当你发现一个重复时，说明重复的两个字符之间是没有重复的，这时候不需要吧扫描的窗口再次重置为1，而是可以保持窗口，仅仅把窗口的开始位置重置到重复字符第一次出现的地方就可以了。极大减少计算量
//time:35ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        char* data=(char*)s.c_str();
        int str_len=s.length();
        int length=0;
        int longest=0;
        int begin=0,end=0;
        map<char, int> lookup;
        auto res=lookup.begin();
        while((begin<str_len) && (end<str_len))
        {
            res=lookup.find(s[end]);
            if(res==lookup.end())
            {
                lookup.insert(pair<char, int>(s[end], end));
                end+=1;
                length=(end-begin);
            }
            else
            {
                for(;begin<=(res->second);)
                {
                    lookup.erase(s[begin]);
                    begin++;
                }
                if(length>longest)
                    longest=length;
            }
        }
        if(length>longest)
            longest=length;
        return longest;
    }
};

