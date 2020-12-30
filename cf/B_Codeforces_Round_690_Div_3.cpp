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
		string s;
		cin >> s;
		if(s.length() < 4){
			cout <<"NO" << endl;
		}
		else{
			if( s.substr(0,4) == "2020" || s.substr(s.length()-4,4) == "2020"){
				cout <<"YES" << endl;
			}else if(s.substr(0,1)=="2" && s.substr(s.length()-3,3) == "020" || s.substr(0,2) == "20" && s.substr(s.length()-2,2) == "20"){
				cout <<"YES" << endl;
			}else if(s.substr(0,3)=="202" && s.substr(s.length()-1,1) == "0"){
				cout <<"YES" << endl;
			}else{
				cout <<"NO" << endl;
			}
		}
	}
	

}