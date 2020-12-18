#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2000000 + 10;

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int a,b;

	while(t--){
		string s1,s2;
		cin >> a>> b;
		cin >> s1;

		for(int i = 0 ; i < s1.length(); i++){
			if(s1[i] == '1' && (i == 0 || s1[i-1] != '1')){
				s2 += '1';
			}
			if(s1[i] == '0'){
				s2 += '0';
			}
		}
		//cout << s2 << endl;
		int l = 0;
		long long cost = 0;
		bool first = true;
		for(int i = 0; i < s2.length(); i++){
			if(s2[i] == '1' && first){
				cost += a;
				first = false;
				continue;
			}
			if(s2[i] == '1'){

				cost += min((i-l)*b, a);
			}
			if(s2[i] == '0' &&(i == 0 || s2[i-1] != '0')){
				l = i;
			}
			//cout << " i: " << i << " l :" << l << endl;
		}
		cout << cost << endl;
	}
	//cout << sqrt((long long)857754240051582063);
}