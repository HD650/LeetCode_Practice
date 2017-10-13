//Determine whether an integer is a palindrome. Do this without extra space.

//一个数字是回文的不需要像string那样麻烦，回转数字之后看看数字与之前入参的数字是否一致就好了，但是这样速度很慢
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)
            return false;
        vector<int> component;
        long long mag=10;
        long long temp=0;
        int digit=0;
        int remain=0;
        while(1)
        {
            temp=x%mag;
            if(temp==x)
            {
                digit=temp/(mag/10);
                component.push_back(digit);
                break;
            }
            digit=temp/(mag/10);
            component.push_back(digit);
            mag*=10;
        }
        long long result=0;
        mag=mag/10;
        for(auto i=component.begin();i!=component.end();i++)
        {
            result+=(*i)*mag;
            mag/=10;
        }
        if(result==x)
            return true;
        else
            return false;
    }
};