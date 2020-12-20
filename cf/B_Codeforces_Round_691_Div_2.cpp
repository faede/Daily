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
	long long ans ;
	if(n % 2 == 0){
		ans = (n/2 + 1)*(n/2 + 1);
	}else{
		long long k = n/2;
		ans = 2*(k + 1)*(k + 2);
	}
	cout << ans;
	
}