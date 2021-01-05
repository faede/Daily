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
const int maxn = 300000 + 5;
const int mod = 998244353;
ll fact[maxn];
ll inv[maxn];
int a[maxn];
int n;
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

void init(){
	fact[0] = inv[0] = 1;
	for(int i = 1; i <= 2*n; i++){
		fact[i] = fact[i-1] * i % mod;
		inv[i] = fast_pow(fact[i], mod - 2);
	}
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	//int n;

	cin >> n;
	init();
	for(int i = 1; i <= 2*n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + 1 + 2*n);
	ll L = 0, R = 0;
	for(int i = 1; i <= 2*n; i++){
		if(i <= n){
			L += a[i];
		}else{
			R += a[i];
		}
	}
	ll ans = R - L;
	ans %= mod;
	ans = ans * fact[2*n] % mod;
	ans = ans * inv[n] % mod;
	ans = ans * inv[n] % mod;
	cout << ans << endl; 

}