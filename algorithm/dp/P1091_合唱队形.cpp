#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;
const int maxn = 100 + 10;
int a[maxn];
int n;
int dp[maxn]; // dp 以i 为中心
int dp1[maxn]; 
int dp2[maxn];
// 这题要是用nlogn的LIS 会多个log
int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i){
		scanf("%d",&a[i]);
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < i; ++j){ // 0开始
			if(a[i] > a[j]){
				dp1[i] = max(dp1[i], dp1[j] + 1);
			}
		}
	}
	for(int i = n; i >= 1; i--){
		for(int j = n+1; j > i; j--){ // n+1开始
			if(a[i] > a[j]){
				dp2[i] = max(dp2[i], dp2[j] + 1);
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		ans = max(dp1[i] + dp2[i] - 1, ans);
	}
	printf("%d\n", n - ans);
}