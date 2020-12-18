#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 200000 + 10;
int a[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t ;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		cin >> a[1];
		long long tot = 0;
		for(int i = 2; i <= n; ++i){
			scanf("%d", &a[i]);
			tot += abs(a[i] - a[i-1]);
		}
		int m = max(abs(a[1]-a[2]) , abs(a[n] - a[n-1]) ) ;
		for(int i = 2; i < n; ++i){
			m = max (m,abs(a[i] - a[i-1]) + abs(a[i+1] - a[i]) -abs(a[i+1] - a[i-1]));
		}
		cout << tot - m << endl;
	}
}