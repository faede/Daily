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
		int n;
		cin >> n;
		string s;
		cin >> s;
		int num = 0;
		
		int len = 0;
		for(int i = s.length() - 1; s[i] == ')' ;i --){
			len ++;
		}
		//cout <<"num:" <<len << " " << endl;
		if(len > s.length() - len){
			cout << "Yes" << endl;
		}else{
			cout << "No"  << endl;
		}
	}
	
}