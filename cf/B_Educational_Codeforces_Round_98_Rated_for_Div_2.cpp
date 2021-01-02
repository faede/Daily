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
const int maxn = 100 +5;
const int mod = 1e9 + 7;
//int a[maxn];
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n ;
		if(n == 1){
			cout << 0 << endl;
			continue;
		}
		ll x;
		ll mm = -1;
		ll sum = 0;
		for(int i = 1; i <= n ; i++){
			cin >> x;
			sum += x;
			mm = max(mm,x);

		}
		ll k = max(mm,  ll((sum + n - 2)/ (n - 1)) ) ;
		cout << k * (n - 1) - sum << endl;
	}
	
	

}