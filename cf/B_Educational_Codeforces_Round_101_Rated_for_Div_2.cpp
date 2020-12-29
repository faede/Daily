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
int a[maxn];
int b[maxn];
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		int n , m;
		cin >> n;
		int t1 = 0;

		for(int i = 1; i <= n ;i++){
			cin >> a[i];
			a[i] += a[i-1];
			t1 = max(t1,a[i]);
		}
		cin >> m;
		int t2 = 0;
		for(int i = 1; i <= m; i++){
			cin >> b[i];
			b[i] += b[i-1];
			t2 = max(t2 ,b[i]);
		}
		cout << t1 + t2 << endl;
	}
	
	

}