/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/

//一个z型拷贝问题，直观做法是直接按照规则拷贝(要迭代一次原始字符串，生成Z字符串，之后迭代Z字符串生成结果)
//但是实际上可以找到输出字符串和原始字符串的下标对应规律，之后使用规律就可以在一次迭代中完成(直接逐一声称结果字符，因为结果字符和原始字符串等长)
//相当于迭代了一次原始字符串，速度快很多
//time:22ms
class Solution {
public:
    string convert(string s, int numRows) 
    {
        if(numRows==1)
            return s;
        int jump[numRows][2]={0};
        jump[0][0]=jump[0][1]=jump[numRows-1][0]=jump[numRows-1][1]=(numRows-1)*2;
        int str_len=s.size();
        int index=0;
        char* result=(char*)malloc(sizeof(char)*(str_len+1));
        char* res=result;
        //原始字符串和结果字符串的下标对应规律
        for(int i=1;i<(numRows-1);i++)
        {
            jump[i][0]=jump[0][0]-(2*i);
            jump[i][1]=jump[0][0]-jump[i][0];
        }
        //直接对res迭代，一个一个生成结果字符
        for(int i=0;i<numRows;i++)
        {
            index=i;
            *res=s[index];
            res++;
            for(int ii=0;(index+jump[i][ii%2])<str_len;ii++)
            {
                index+=jump[i][ii%2];
                *res=s[index];
                res++;
            }
        }
        //防止char*因为没有结尾而越界
        *res='\0';
        return string(result);
    }
};

