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
	int n ;
	cin >> n;
	long long ans = 4;
	if( n == 1 || n == 2){
	}
	else{
		if(n %2 == 0){
			ans = 13;
		}else{
			ans = 12;
		}
	}
	cout << ans;
	
}