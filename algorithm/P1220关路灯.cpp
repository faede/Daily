#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 50 + 5;
#define s(i,j) (sum[j] - sum[i-1]) 
int n,c;
int pos[maxn];
int cost[maxn];
int dp[maxn][maxn][2]; // 0 向左 1 向右
// dp[i][j][0] = 
int sum[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	scanf("%d %d",&n,&c);
	for(int i = 1; i <= n; ++i){
		scanf("%d %d",&pos[i],&cost[i]);
		sum[i] = sum[i-1] + cost[i];
	}

	memset(dp,0x3f,sizeof(dp));
	if(c >= 2)
		dp[c-1][c][0] = (pos[c] - pos[c-1]) * (s(1,c-1) + s(c+1,n));
	if(c <= n-1)
		dp[c][c+1][1] = (pos[c+1] - pos[c]) * (s(1,c-1) + s(c+1,n));

	for(int len = 3; len <= n; ++len){
		for(int l = 1; l <= n - len + 1;++l){
			int r = l+len-1;
   			dp[l][r][0] = min(dp[l+1][r][0]+(pos[l+1] - pos[l])*(s(1,l)+s(r+1,n))
   				,dp[l+1][r][1]+(pos[r] - pos[l])*(s(1,l)+s(r+1, n)));

   			dp[l][r][1] = min(dp[l][r-1][0]+(pos[r] - pos[l])*(s(1 , l-1)+s(r , n))
   				,dp[l][r-1][1]+(pos[r] - pos[r-1])*(s(1 ,l-1)+s(r , n)));
		}
	}
	cout << min(dp[1][n][0] , dp[1][n][1]);
}	