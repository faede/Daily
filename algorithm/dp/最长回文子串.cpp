class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n));
        // dp  长度
        // i 开头 j 结尾的回文串
        // dp[i][j] <--- dp[i+1][j-1]
        //          <--- 0
        string res;
        for(int len = 1; len <= n; ++len){
            for(int i = 0; i < n; i++){
                int j = i + len - 1;
                if(j >= n){
                    break;
                }
                if(len == 1){
                    dp[i][j] = 1;
                }else if(len == 2){
                    dp[i][j] = (s[i] == s[j])*2;
                }else if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = dp[i+1][j-1]+2;
                }else{
                    dp[i][j] = 0;
                }
                if(dp[i][j]  > res.length()){
                    res = s.substr(i,len);
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n));
        // dp i j是不是回文串
        // i 开头 j 结尾的回文串
        // dp[i][j] <--- dp[i+1][j-1]
        //          <--- 0
        string res;
        for(int len = 1; len <= n; ++len){
            for(int i = 0; i < n; i++){
                int j = i + len - 1;
                if(j >= n){
                    break;
                }
                if(len == 1){
                    dp[i][j] = 1;
                }else if(len == 2){
                    dp[i][j] = (s[i] == s[j]);
                }else if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1];
                }else{
                    dp[i][j] = 0;
                }
                if(dp[i][j] && len > res.length()){
                    res = s.substr(i,len);
                }
            }
        }
        return res;
    }
};