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

//改进了代码结构，对遍历开头的控制应该放在工作函数外边，其次，每次找到重复之后，只需要从重复字符出现的那一点开始下次遍历，不需要从这次遍历的开始重启。
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
