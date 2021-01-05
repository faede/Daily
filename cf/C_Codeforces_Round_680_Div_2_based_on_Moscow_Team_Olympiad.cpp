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
const int maxn = 20 +5;
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
	long long p,q;
	while(t--){
		cin >> p >> q;
		if(q > p){
			cout << p << endl;
		}else if(q == p){
			bool tag = true;
			for(long long  i = 2; i < 1e5 + 1; i++){
				if(p % i == 0){
					cout << p/i << endl;
					tag = false;
					break;
				}
			}
			if(tag)
				cout << 1 << endl;
		}else{
			if(p % q != 0){
				cout << p << endl;
			}else{
				long long ans = -1;
				for(long long i = 2; i < 1e5 + 1; i++){
					if(q % i == 0){
						long long temp = p;
						while(1){
							temp /= i;
							if(temp % q != 0){
								ans = max(ans, temp);
								break;
							}
							if(temp % i != 0){
								break;
							}
						}
					}
				}
				while(1){
					p /= q;
					if(p %q != 0){
						ans	= max(ans, p);
						break;
					}
				}
				cout << ans << endl;
			}
			

		}
	}

}