#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100+5;
int W,n;
int w[maxn];
int v[maxn];
int g[maxn];
//int dp[maxn][maxn];
int dp[205][20005];

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		memset(dp,0,sizeof(dp));
		cin>>W>>n;
		for(int i = 1; i <= n; ++i){
			scanf("%d %d %d",&w[i],&v[i],&g[i]);
		}

		for(int i = 1; i <= n; ++i){
			for(int j = 0;  j <= W; j++){

				dp[i][j] = dp[i-1][j];
				for(int k = 1;k <= g[i]; ++k){
					if(j - k*w[i] >= 0){
						dp[i][j] = max(dp[i][j],dp[i-1][j-k*w[i]] + k*v[i]);
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