#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 10;
int n,m;
int a[maxn];
int b[maxn];
int size_g[maxn];
int no[maxn][maxn];
// dp[i][j]   dp[i-1][j] ,   dp[i-1][j-w[i]]
int dp[maxn];
int main(){
	int g; 
	int tot = 0;
	scanf("%d %d",&m, &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d",&a[i],&b[i],&g);
		size_g[g]++;
		tot = max(tot, g);
		no[g][size_g[g]] = i;
	}

	for(int k = 1; k <= tot; k++){
		for(int i = m; i >= 0; i--){
			for(int j = 1; j <= size_g[k]; j++){
				if(i >= a[ no[k][j] ])
					dp[i] = max(dp[i], dp[i-a[ no[k][j] ]] + b[no[k][j]]);
			}
		}
	}
	cout << dp[m];
}