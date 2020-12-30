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
const int maxn = 300 +5;
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
		int n;
		cin >> n;
		int i = 1;
		int j = n;
		int k = 1;
		for(int m = 1; m <= n; m++){
			cin >> b[m];
		}
		while(i <= j){
			a[k++] = b[i++];
			a[k++] = b[j--];

		}
		for(int i = 1; i <= n; i++){
			cout << a[i] << " ";
		}
		cout << endl;

	}
	
	

}