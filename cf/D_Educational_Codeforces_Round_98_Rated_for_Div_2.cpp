#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int > pt;
typedef long long ll;
const int maxn = 200000 +5;
const int mod = 998244353;

/*
by PurpleCrayon:https://codeforces.com/blog/entry/84847
and reframe:

Consider dp[i] present first i number statified constriant
we want cac it using dynamic program, so we want use last
cac result such that ,dp[i-1], dp[i-2] ,... ,dp[0]
because one tower only cover odd length (put it in middle),
so for the number we can cac by dp[i] = dp[i-1] + dp[i-3] +...
dp[i - 1] present i cover by i
dp[i - 3] present i cover by i - 1 ( i - 2 ,i - 1 also cover by i )
...
that is different and all solution , so we can add it as result.
dp[i] = dp[i-1] + dp[i-3] +...


The optimization is pretty simple. Because you don't care about the actual 
values of all previous dp's but just the parity. So instead of storing the whole dp array, 
just have it store 2 values, dp[0] and dp[1]. dp[0] stores the numbers of ways to cover an even prefix, 
and dp[1] stores the number of ways to cover an odd prefix.


You still loop from 1 to n but the transitions are now 
dp[i mod 2] = dp[i mod 2] + dp[1 − (i mod 2)]. 
(or more obivously dp[i mod 2] += dp[1 − (i mod 2)] , if i is odd then 1 − (i mod 2) is even)

This is exactly the Fibonacci recurrence.

so ans is Fn/2^n
*/
ll fast_pow(ll x, ll p){
	ll ans = 1;
	while(p){
		if(p & 1){
			ans *= x;
			ans %= mod;
		}
		p >>= 1;
		x *= x;
		x %= mod;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int n ;
	cin >> n;
	int t = n;
	ll dp[2];
	dp[0] = 0;
	dp[1] = 1;
	for(int i = 2 ; i <= n; i++){
		dp[i % 2] += dp[1 - (i%2)];
		dp[i % 2] %= mod;
	}
	// cout << "dp :" << dp[n % 2] << endl;
	cout << (dp[n % 2] * fast_pow( fast_pow(2,n) , mod - 2) ) % mod << endl;


}