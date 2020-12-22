#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 50 +5;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		int n,k;
		cin >> n>>k;
		string s;
		cin >> s;
		int ans = 0 ;
		std::vector<int> v;

		int len = 0;
		int numofl = 0;
		for(int i = 0 ; i < s.length(); i++){
			if(s[i] == 'W' ){
				ans ++;
				if(i > 0 && s[i-1] == 'W'){
					ans ++;
				}
			}else{
				numofl++;
			}

			if(i > 0 && s[i] == 'W'){
				if(i != len &&len > 0){
					v.push_back(len);
				}
				len = 0;
			}else{
				if(s[i] == 'L')
				{
					len++;
				}
			}

		}
		if(k > numofl){
			k = numofl;
		}

		//cout <<"case " << t <<" :";
		//for(int i = 0; i < v.size(); i++){
		//	cout << v[i] << " " ;
		//}
		//cout << endl;

		sort(v.begin(), v.end());



		for(int i = 0; i < v.size(); i++){
			if(k >= v[i]){
				ans += 2*v[i] + 1;
				k -= v[i];
			}else{
				ans += 2*k;
				k = 0;
				break;
			}
		}
		if(n - numofl > 0){
			ans += k * 2;
		}else{
			if(k-1 >= 0)
				ans += (k-1)*2 + 1;
		}
		cout << ans << endl;

	}
	
}