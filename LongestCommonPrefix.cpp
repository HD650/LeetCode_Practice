//Write a function to find the longest common prefix string amongst an array of strings.


//比好想的方法就是先排序整个输入数组，因为如果第一个字符串是最短的，后边的比较就会更快，之后慢慢比较就行了
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) 
    {
        if(strs.size()==0)
            return string();
        if(strs.size()==1)
            return strs[0];
        std::sort(strs.begin(),strs.end(),sort_function);
        string temp=strs[0];
        for(auto i=(strs.begin()+1);i!=strs.end();i++)
        {
            int ii=0;
            for(;ii<temp.length();ii++)
            {
                if(temp[ii]!=(*i)[ii])
                    break;
            }
            temp=temp.substr(0,ii);
        }
        return temp;
    }
    
    static bool sort_function(string a, string b)
    {
        return (a.length()<b.length());
    }
};