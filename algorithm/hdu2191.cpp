#include<cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100+5;
int n,m;
int price[maxn];
int height[maxn];
int cot[maxn];
//int dp[maxn][maxn];
int dp[205][20005];

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		memset(dp,0,sizeof(dp));
		cin>>n>>m;
		for(int i = 1; i <= m; ++i){
			scanf("%d %d %d",&price[i],&height[i],&cot[i]);
		}

		for(int i = 1; i <= m; ++i){
			for(int j = 0;  j <= n; j++){
				dp[i][j] = dp[i-1][j];
				for(int k = 1;k <= cot[i]; ++k){
					if(j - k*price[i] >= 0){
						dp[i][j] = max(dp[i][j],dp[i-1][j-k*price[i]] + k*height[i]);
					}
					
				}
			}
		}
		//for(int i = 1; i <=m; i++){
		//	for(int j = 1; j <= n; j++){
		//		cout<< dp[i][j]<<" ";
		//	}
		//	cout<<endl;
		//}
		cout<<dp[m][n]<<endl;
	}
}