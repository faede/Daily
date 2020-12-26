#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
typedef long long ll;
using namespace std;
const int maxn = 200000 +5;
const int maxm = 300000 +5;
const int mod = 1000000007;
ll fact[maxm];
ll invfact[maxm];

ll a[maxn];

ll fast_pow(ll a, ll p){
	ll res = 1;
	while(p){
		if(p&1)
		{
			res *= a;
			res %= mod;
		}
		a *= a;
		a %= mod;
		p >>= 1;
	}
	return res;
}

ll C(int n, int k){
	if(k > n)
		return 0;
	return fact[n] * invfact[k]%mod * invfact[n-k]%mod;
}




int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	
	fact[0] = invfact[0] = 1;
	for(ll i = 1; i < maxm; i++){
		fact[i] = (fact[i-1]*i)%mod;
		invfact[i] = fast_pow(fact[i], mod - 2);
	}



	int t;
	cin >> t;
	while(t--){
		int n,m,k;
		cin >> n >> m >> k;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		sort(a+1,a+n+1);
		ll ans = 0;
		for(int i = 1; i <= n; i++){
			int l = i ;
			int r = upper_bound(a + 1, a + n + 1, a[i] + k) - a - 1;
			ans = (ans + C(r-l,m-1)) % mod;
		}
		cout << ans << endl;
	}

}