#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int > pt;
typedef long long ll;
const int maxn = 50 +5;
const int mod = 1e9 + 7;

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
	int t;
	cin >> t;
	while(t--){
		ll n, t;
		cin >> n;
		cin >> t;
		ll ans = 0;
		ll x;
		ll sum = 0;
		ll mn = 0;
		ll mx = 0;
		for(int i = 1; i <= n; i++){
			cin >> x;
			sum += x;
			mx += (x + t - 1) / t;
		}
		mn = (sum + t - 1) / t;
		cout << mn << " " << mx << endl;
 	}

}