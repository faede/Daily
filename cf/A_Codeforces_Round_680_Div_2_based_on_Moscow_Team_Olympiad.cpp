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
const int maxn = 50 +5;
const int mod = 1e9 + 7;
int a[maxn];
int b[maxn];
int vis[maxn];
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
		ll n,  x;
		cin >> n >> x;
		for(int i = 1; i <= n ; i++){
			cin >> a[i];
		}
		for(int i = 1; i <= n ; i++){
			cin >> b[i];
		}
		//sort(b+1,b+1+n);
		bool tag = true;
		for(int i = 1; i <= n; i++){
			//cout << "x - a[i] :" << x - a[i] << endl;
			if(a[i] + b[n - i + 1] > x){
				tag = false;
				break;
			}
		}
		if(tag){
			cout << "Yes" << endl;
		}else{
			cout << "No" << endl;
		}
	}

}