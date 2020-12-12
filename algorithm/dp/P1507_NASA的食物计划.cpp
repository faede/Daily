#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 50 + 10;
const int maxm = 400+10;
int dp[maxm][maxm]; // 这题目每个物品还是只有取和不取两种 不可以取一部分
int v[maxn];
int m[maxn];
int val[maxn];
int main(){
	int V,M;
	cin >> V >> M;
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d",&v[i], &m[i], &val[i]);
	}

	for(int i = 1; i <= n ;++i){
		for(int j = V; j >= v[i]; j--){
			for(int k = M; k >= m[i]; k--){
				dp[j][k] = max(dp[j][k], dp[j - v[i]][k - m[i]] + val[i]);
			}
		}
	}
	cout << dp[V][M];
}