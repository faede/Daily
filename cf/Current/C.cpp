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
const int maxn = 300000 +5;
const int mod = 1e9 + 7;
int a[maxn];
int b[maxn];

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


int vis[maxn];
bool comp(int x, int y){
	return b[x] > b[y];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		for(int j = 1; j <= m; j++){
			cin >> b[j];
			vis[j] = 0;
		}
		sort(a + 1, a + n + 1,comp);
		ll sum = 0;
		//intz
		int j = 1;
		for(int i = 1; i <= n; i++){
			int cost = b[a[i]];
			int pos = 0;
			for(; j <= a[i] ; j++){
				if(!vis[j] && cost > b[j]){
					cost = b[j];
					pos = j;
					break;
				}
			}
			vis[pos] = 1;
			sum += cost;
		}
		cout << sum << endl;
	}

}