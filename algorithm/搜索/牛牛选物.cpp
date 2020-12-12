/*
链接：https://ac.nowcoder.com/acm/contest/9886/B
来源：牛客网

牛牛有现在有n个物品，每个物品有一个体积v[i]和重量g[i],他想选择其中总体积恰好为V的若干个物品，想使这若干个物品的总重量最大，
他想知道最大总重量为多少。（如果不存在合法方案，返回-1）

[1,2,3],[2,3,4],3

5

对于100%的数据，1≤n≤20,1≤v[i]≤1e8,1≤g[i]≤1e8,1≤V≤1e9
给定三个参数，第一个参数为数组v，第二个参数为数组g，第三个参数为体积V，求最大总重量为多少。
(所给字符串与返回字符串都不带引号)
*/

// n只有20 大力搜 用二进制优化一下
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 返回总体积为V若干物品的最大总重量，如果g存在选择若干物品总体积为V的情况，返回-1
     * @param v int整型vector 
     * @param g int整型vector 
     * @param V int整型 
     * @return int整型
     */
    int Maximumweight(vector<int>& v, vector<int>& g, int V) {
        // write code here
        // 状压防爆栈
        int n = v.size();
        int res = -1;
        for(int i = 0; i <= (1<<n); ++i){
            int re = V;
            int val = 0;
            for(int j = 0; j < n;j++){
                if( i & (1<<j)){
                    re -= v[j];
                    val += g[j];
                }
                
            }
            if( re == 0){
                res = max(res,val);
            }
        }
        return res;
    }
};