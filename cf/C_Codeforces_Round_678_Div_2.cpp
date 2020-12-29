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
const int maxn = 1000 +5;
const int mod = 1e9 + 7;
ll fact[maxn];
ll invfact[maxn];
int n, x, pos;

ll fastp(ll x, ll p){
	ll res = 1;
	while(p){
		if(p&1){
			res = (res * x) % mod;
		}
		p >>= 1;
		x = (x * x) % mod;
	}
	return res;
}

void init(){
	fact[0] = 1;
	invfact[0] = 1;
	for(int i = 1; i < maxn; i++){
		fact[i] = (fact[i-1]*i)%mod;
		invfact[i] = fastp(fact[i], mod - 2);
	}
}

ll C(int n,int m){
	if(m > n){
		return 0;
	}
	return ((fact[n] * invfact[m]) % mod  * invfact[n-m]) % mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	
	init();

	cin >> n >> x >> pos;
	int great = 0;
	int less = 0;

	int left = 0;
	int right = n;
	while(left < right){
		int mid = (left + right) / 2;
		if(mid <= pos){
			if(mid != pos)
				less++;
			left = mid + 1;
		}else{
			great++;
			right = mid;
		}
	}

	//cout <<"great:" << great << endl;
    //cout << "less :" << less << endl;


	ll res = (C(n - x, great)*fact[great]) %mod;


	res = (res * C(x-1,less) ) %mod;
	//	cout<<"temp:" << res << endl;
	res = (res * fact[less] ) %mod;
	//cout<<"temp:" << res << endl;
	res = (res * fact[n - less - great - 1])%mod;
	cout << res << endl;
	//cout << C(x-1,less);
}










