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
int vis[maxn];
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	
	int t;
	cin >> t;
	while(t--){
		string s;
		cin >> s;
		if(s[0] != ')' && s[s.length() - 1] != '(' && s.length() % 2 == 0){
			cout << "YES" << endl;
		}else{
			cout << "NO" << endl;
		}
		
	}
	

}