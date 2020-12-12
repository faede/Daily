/*

链接：https://ac.nowcoder.com/acm/contest/9886/C
来源：牛客网

牛牛拿到了一个字符串。他想知道除去字符串本身以外，这个字符串最大的公共前后缀的长度是多少？

例如，对于字符串ABABA而言，“ABA”即是它的前缀，也是它的后缀，且是最长的公共前后缀，因此最大的长度是3。

牛牛无法解决该问题，所以他只好向你求助，给定一个只包含大写字母的字符串s，
返回除去字符串本身以外公共前后缀最大长度，如果没有任何一个公共前后缀满足要求，返回-1即可。


"ABA"
1


1≤∣s∣≤1e6,且字符串中只包含大写字母
*/

// 裸的kmp ~~但我没写出来~~

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 给定一个字符串s，返回具有相同前缀后缀的子串的第二大长度，反之，返回-1即可。
     * @param s string字符串 代表题意中的字符串s
     * @return int整型
     */
    
    int solve(string s) {
        // write code here
        int n = s.size();
        int nx[n + 10];
        memset(nx,0,sizeof(nx));
        nx[0] = -1;
        int j = -1;
        int i = 0;
        while( i < n){
            if(j < 0 || s[i] == s[j]){
                nx[++i] = ++j;
            }else{
                j = nx[j];
            }
        }
        int res = nx[n];
        if(res == 0)
            return -1;
        return res;
    }
};