#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 1000 + 10;
int isnp[maxn];
std::vector<int> primes;
void init(int n){
	isnp[1] = 1;
	for(int i = 2;i <= n; ++i){
		if(!isnp[i])
			primes.push_back(i);
		for(int p : primes){
			if(p * i > n)
				break;
			isnp[p*i] = 1;
			if(i % p == 0)
				break;
		}
	}
}
long long dp[maxn];
int main(){
	int n;
	cin >> n;
	init(n);
	int m = primes.size();
	//for(int i : primes){
	//	cout << i <<" ";
	//}
	dp[0] = 1; // 注意边界
	for(int i = 0; i < m; ++i){
		for(int j = primes[i]; j <= n; ++j){
			dp[j] += dp[j - primes[i]];
		}
	}
	cout << dp[n];
}