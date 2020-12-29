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
		memset(vis,0,sizeof(vis));
		cin >> s;
		bool tag = true;
		for(int i = 0; i < s.length(); i++){
			if(s[i] == ')' && !vis[i]){
				tag =false;
				break;
			}else if((s[i] == '(' ) && !vis[i]){
				bool fd = false;
				for(int j = i + 1; j < s.length(); j++){
					if(s[j] == ')' && !vis[j]){
						vis[j] = 1;
						fd = true;
						break;
					}
				}
				if(!fd)
				for(int j = i + 1; j < s.length(); j++){
					if(s[j] == '?' && !vis[j]){
						vis[j] = 1;
						fd = true;
						break;
					}
				}

				if(!fd){
					tag = false;
					break;
				}
				vis[i] = 1;
			}else if((s[i] == '?') && !vis[i]){
				bool fd = false;
				for(int j = i + 1; j < s.length(); j++){
					if(s[j] == '?' && !vis[j]){
						vis[j] = 1;
						fd = true;
						break;
					}
				}
				if(!fd)
				for(int j = i + 1; j < s.length(); j++){
					if(s[j] == ')' && !vis[j]){
						vis[j] = 1;
						fd = true;
						break;
					}
				}

				if(!fd){
					tag = false;
					break;
				}
				vis[i] = 1;
			}
		








		} 



		if(!tag){
			cout << "NO" << endl;
		}else{
			cout <<"YES" << endl;
		}
	}
	

}