#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 200000+10;
long long a[maxn];
long long b[maxn];
long long gcd(long long a,long long b){
	if(b == 0)
		return a;
	return gcd(b,a%b);
}
int main(){
/*
	gcd(x,y) = gcd(x,y-x)

	gcd(a1+bj,a2+bj,...,an+bj)
	= gcd(a1+bj,a2-a1,...,an-a1)


*/


	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <=  n; i++){
		scanf("%lld", &a[i]);
	}
	for(int i = 1; i <= m; i++){
		scanf("%lld", &b[i]);
	}

	if(n == 1){
		for(int i = 1; i <= m; i++){
			cout << a[1] + b[i] <<" ";
		}
	}else{
		long long left = abs(a[2] - a[1]),right;
		for(int i = 3; i <= n; i++){
			right = abs(a[i] - a[1]);
			left = gcd(left,right);
		}
		for(int i = 1; i <= m; i++){
			cout << gcd(left,b[i] + a[1]) <<" ";
		}
	}
	
}