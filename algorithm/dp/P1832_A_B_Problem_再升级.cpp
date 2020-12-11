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
int dp[maxn][maxn];
int main(){
	int n;
	cin >> n;
	init(n);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= primes.size(); ++j){
			dp[i]
		}
	}
}