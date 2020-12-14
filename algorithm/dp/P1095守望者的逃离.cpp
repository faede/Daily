#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 10;
const int maxm = 300000 + 10;
int dp[maxm]; // dp[T][M]
// 每一步应该有两种选择 等待或者走
// 对于走的情况一定先会把魔法值花完,因为肯定更优
// 判断达到S的时间
int main(){
	int m,s,t;
	cin >> m >> s >>t;
	for(int i = 1; i <= t; ++i){
		if(m >= 10){
			dp[i] = dp[i-1] + 60;
			m -= 10;
		}else{
			dp[i] = dp[i-1];
			m += 4;
		}
	}
	for(int i = 1; i <= t; ++i){
		if(dp[i] < dp[i-1] + 17)
			dp[i] = dp[i-1] + 17;
		if(dp[i] >= s){
			cout << "Yes" << endl;
			cout<< i;
			return 0;
		}
	}
	printf("No\n%d", dp[t]);
}