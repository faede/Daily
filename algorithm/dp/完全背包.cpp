/*

 完全背包问题,i种每种无限个
 dp[i][j] = max(dp[i-1][j] , dp[i][j-v] + w)

 for(int i = 1; i <= n; ++i){//可以换顺序
	for(int j = v[i]; j <= V; ++j){ // 这里和0/1 背包不同可以取之前的,所以顺序遍历
		dp[j] = max(dp[j],dp[j-v[i]] + w[i]);
	}
 }



*/