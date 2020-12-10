#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200+10;
int a[maxn];
int dp1[maxn][maxn]; // max
int dp2[maxn][maxn]; // min
int n;
// 合并的子区间一定取到最大值
// dp[i][j] = max(dp[i][k] + dp[k+1][j] + d(i,j))
// 枚举len就好了 
int sum[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
		a[i+n] = a[i];
	}
	for(int i = 1; i <= 2*n; ++i){
		sum[i] = sum[i-1] + a[i];
	}
	for(int len = 2; len <= n; ++len){
		for(int i = 1; i < 2*n; ++i){
			int j = i + len - 1;
			if(j >= 2*n){
				break;
			}
			dp2[i][j] = 1e9;
			for(int k = i; k < j; ++k){
				dp1[i][j] = max(dp1[i][j],dp1[i][k] + dp1[k+1][j] + sum[j] - sum[i-1]);
				dp2[i][j] = min(dp2[i][j],dp2[i][k] + dp2[k+1][j] + sum[j] - sum[i-1]);
			}
		}
	}
	int res_min,res_max;
	res_max = 0;
	res_min = 1e9;
	for(int i = 1; i <= n; i++){
		res_max = max(res_max,dp1[i][i+n-1]);
		res_min = min(res_min,dp2[i][i+n-1]);
	}
	printf("%d\n%d", res_min,res_max);
	return 0;
}