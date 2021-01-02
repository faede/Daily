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
	// 8 + 5
	while(t--){
		int x,y;
		cin >> x >> y;
		int t = (max(x,y) - min(x,y) - 1) > 0 ?   (max(x,y) - min(x,y) - 1) : 0;
		cout << x + y + t<< endl;
	}
	
	

}