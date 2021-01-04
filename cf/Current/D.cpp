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
const int maxn = 150000 + 5;
const int mod = 998244353;
int a[maxn];
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
	int n;
		cin >> n;
		//n <<= 1;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		sort(a + 1, a + 1 + n);
		ll ans = 0;
		for(int i = 1; i <= n ; i++){
			for(int j = n + 1; j <= 2 * n ;j++){
				ans += abs(a[i] - a[j]);
				ans %= mod;
			}
		}
		ans *= 2;
		ans %= mod;
		cout << ans << endl;

}