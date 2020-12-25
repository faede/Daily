#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
ll a[maxn];
ll pow2[maxn];
bool init(int n, int c){
	pow2[0] = 1;
	for(int i = 1; i <= n; i++){
		pow2[i] = pow2[i-1] * c;
		if(pow2[i] < 0)
			return false;
	}
	return true;
}
ll get(ll x, ll n){
	//cout <<" 1"<<endl;
	for(ll i = 2; ;i++){
		if(pow(i,n-1) > x)
			return i;
	}
	return 1;
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a,a+n);
	ll ans = 1e18;
	init(n,1);
	ll k = 0;
	for(int i = 0; i < n; i++){
		k += abs(a[i] - pow2[i]);
	}
	int right =  get(a[n-1] + k,n);
	//cout << "right : " << right << endl;
	for(int c = 1; c <= right; c++){
		if(!init(n,c)){
			break;
		}
		ll res = 0;
		for(int i = 0; i < n; i++){
			res += abs(a[i] - pow2[i]);
		}
		if(res < 0)
			break;
		ans = min(res, ans);
	}
	
	cout << ans << endl;
}