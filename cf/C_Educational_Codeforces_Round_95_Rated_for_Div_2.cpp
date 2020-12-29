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
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}

		int res = 0;
		res += a[1] == 1;
		for(int i = 2; i <= n; i++){
			if(!a[i]){
				continue;
			}
			int j = i;
			while(j <= n && a[j] == 1){
				j++;
			}
			j--;
			res += (j - i + 1)/3;
			i = j;
		}
		cout << res <<endl;
	}

	




}