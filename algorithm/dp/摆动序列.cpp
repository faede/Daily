// https://leetcode-cn.com/problems/wiggle-subsequence/
// 求出最长度摆动子序列长度(非连续)  摆动指新生成的序列中前后两个差 一正,一反


// 线性dp
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size() < 2){
            return nums.size();
        }
        int dp[nums.size()+10][2]; 
        // 0 : 升序  :1 降序
        memset(dp,0,sizeof(dp));
        // 反正法可以证明第一个一定在摆动序列里,因为无论第二个比第一个
        // 大还是小,在序列中都可以换成第一个而长度不减
        dp[0][1]=dp[0][0]=1;
        //dp 以升/降序结尾的长度
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] > nums[i-1]){
                dp[i][0] = dp[i-1][1] + 1;
                dp[i][1] = dp[i-1][1];
            }else if(nums[i] < nums[i-1]){
                dp[i][0] = dp[i-1][0];
                dp[i][1] = dp[i-1][0] + 1;
            }else{
                dp[i][0] = dp[i-1][0];
                dp[i][1] = dp[i-1][1];
            }
        }

        return max(dp[nums.size()-1][0],dp[nums.size()-1][1]);
    }
};

// 优化空间

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size() < 2){
            return nums.size();
        }
        // 0 : 升序  :1 降序
        // 反正法可以证明第一个一定在摆动序列里,因为无论第二个比第一个
        // 大还是小,在序列中都可以换成第一个而长度不减
        int dp0 = 1,dp1 = 1;
        //dp 以升/降序结尾的长度
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] > nums[i-1]){
                dp0 = dp1 + 1;
                dp1 = dp1;
            }else if(nums[i] < nums[i-1]){
                dp0 = dp0;
                dp1 = dp0 + 1;
            }else{
                dp0 = dp0;
                dp1 = dp1;
            }
        }

        return max(dp0,dp1);
    }
};

// 贪心做法,我们可以想象一下将数值画到二维数轴形成的图,可以发现我们最终要找的

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1)
        	return nums.size();
        int curDiff = 0; // 当前一对差值
        int preDiff = 0; // 前一对差值
        int result = 1;  // 记录峰值个数，也是长度,所以最左边的点一定会被包含进去
        for (int i = 1; i < nums.size(); i++) {
            curDiff = nums[i] - nums[i - 1];
            // 出现峰值

            //前面是平的或者是降的

            // 前面是平的或者是升的
            if ((curDiff > 0 && preDiff <= 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff;
            }
        }
        return result;
    }
};








