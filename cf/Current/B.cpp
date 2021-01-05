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
const int maxn = 100000 +5;
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

int getn(int t, int x, bool & tag){
	int ans = 0;
	while(t % x == 0){
		ans++;
		t /= x;
	}
	if(t != 1){
		tag = false;
	}
	if(t == 1){
		ans++;
	}
	return ans ;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		ll n,x;
		cin >> n >> x;
		std::vector<int> v;
		std::vector<int> v2;
		ll sum = 0;
		int t;
		for(int i = 1; i <= n; i++){
			cin  >> t;
			sum += t;
			v.push_back(t);
			v2.push_back(t);
		}

		bool tag = true;
		int k = 1;
		while(1){
			for(int i = 0; i < v.size(); i++){
				if(v[i] % x == 0){
					sum += v2[i];
					v[i] /= x;
				}else{
					//sum += v[i];
					tag = false;
					break;
				}

			}
			//k++;
			if(!tag){
				break;
			}
		}
		cout << sum << endl;
	}

}