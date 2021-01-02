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
		int l1 = 0 ;
		int l2 = 0;
		int move = 0;
		for(int i = 0 ; i < s.length(); i++){
			if(s[i] == '('){
				l1++;
			}
			if(s[i] == '['){
				l2++;
			}
			if(s[i] == ')'){
				if(l1 > 0){
					l1--;
					move++;
				}
			}
			if(s[i] == ']'){
				if(l2 > 0){
					l2--;
					move++;
				}
			}
		}
		cout << move << endl;
	}
	
	

}