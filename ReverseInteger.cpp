/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Note:
The input is assumed to be a 32-bit signed integer. Your function should return 0 when the reversed integer overflows.
*/

//仅仅反转一个整数并不难，通过对10，100，1000取余，之后在整除以10，1000等就可以抽出这一位上的数字了
//这题主要的难度在于溢出，有符号整型的最大绝对值为0x7fffffff，该题测试用例会有大于这个绝对值的数字出现
//导致各种溢出，报错表现为不能除以0，一些数字突然变成负数等，只要处理好溢出，就可以解决
//time:12ms
class Solution {
public:
    int reverse(int x) 
    {
        int n_biggest=0x80000001;
        int p_biggest=0x7fffffff;
        if(x<n_biggest||x>p_biggest)
            return 0;
        //被除数最后会生长到和x一样的数量级，会溢出，所以使用long
        long long d=10;
        vector<int> res_v;
        //中间结果也可能溢出
        long long temp;
        while(1)
        {
            temp=x%d;
            if(temp==x)
            {
                temp=temp*10/d;
                printf("%d = %d / %d\n", temp,x,d);
                res_v.push_back(temp);
                break;
            }
            temp=temp*10/d;
            printf("%d = %d / %d\n", temp,x,d);
            res_v.push_back(temp);
            d*=10;
        }
        //最后结果可能溢出
        long long result=0;
        d=pow(10, res_v.size()-1);
        for(auto i=res_v.begin();i!=res_v.end();i++)
        {
            result+=*i*d;
            d/=10;
        }
        if(result<n_biggest||result>p_biggest)
            return 0;
        return result;
    }
};
