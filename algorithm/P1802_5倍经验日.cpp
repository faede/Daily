#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1000 + 10;
int lose[maxn];
int win[maxn];
int use[maxn];
int n,x;
int dp[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	scanf("%d %d", &n, &x);
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d",&lose[i], &win[i], &use[i]);
	}
	for(int i = 1; i <= n; ++i){
		for(int j = x; j >= 0; j--){
			if(j >= use[i]){
				dp[j] = max(dp[j-use[i]] + win[i], dp[j] + lose[i]);
			}else{
				dp[j] = dp[j] + lose[i];
			}
			
		}
	}
	cout << dp[x] * (long long) 5;
}