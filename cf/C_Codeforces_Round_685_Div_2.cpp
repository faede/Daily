#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 30;
int a[maxn];
int b[maxn];
int n;
int k;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	string s;
	while(t--){
		//int n;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin >> n >> k;
		cin >> s;
		for(int i = 0; i < s.length(); i++){
			a[s[i]-'a']++;
		}
		cin >> s;
		for(int i = 0; i < s.length(); i++){
			b[s[i]-'a']++;
		}

		bool tag = true;
		for(int i = 0; i < 26 ;++i){
			if(a[i] < b[i]){
				tag = false;
				break;
			}else if(a[i] > b[i]){
				if((a[i] - b[i]) % k == 0){
					a[i+1] += (a[i] - b[i]);

				}else{
					tag = false;
					break;
				}
			}
		}
		if(a[26] != 0){
			tag = false;
		}
		if(tag){
			cout << "Yes" << endl;
		}else{
			cout << "No" << endl;
		}
	}
	
}