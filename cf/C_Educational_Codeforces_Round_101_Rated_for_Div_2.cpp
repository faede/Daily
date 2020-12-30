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
const int maxn = 200000 +5;
const int mod = 1e9 + 7;
int a[maxn];
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		for(int  i = 1; i <= n; i++){
			cin >> a[i];
		}
		int low = a[1];
		int high = a[1];
		bool tag = true;
		for(int i = 2; i <= n; i++){
			low = max(a[i],low - (k - 1));
			high = min(high + (k - 1), a[i] + (k - 1));
			if(low > high){
				tag = false;
				break;
			}
		}
		if(!tag || a[n] < low || a[n] > high){
			cout << "NO" << endl;
		}else{
			cout << "YES" << endl;
		}
	}
	

}