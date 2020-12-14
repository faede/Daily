#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 1000007;
const int maxn = 100 + 10;
int a[maxn];
//int dp[maxn][maxn];
int dp[maxn];
int n,m;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		scanf("%d", &a[i]);
	}
	dp[0] = 1;
	for(int i = 1; i <= n; ++i){
		for(int j = m; j >= 1; j--){
			for(int k = 1; k <= a[i]; ++k){
				if(j >= k ){
					dp[j] += dp[j - k];
					dp[j] %= mod;
				}
			}
			
		}
	}
	cout << dp[m];
}