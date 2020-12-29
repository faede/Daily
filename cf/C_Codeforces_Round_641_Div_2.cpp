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
const int maxn = 200000 +5;
const int mod = 1e9 + 7;
int a[maxn];
int gcd(int a,int b){
	return b == 0 ? a : gcd(b,a%b);
}
int lcm(int a, int b){
	return (long long)a * (long long)b / gcd(a,b);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	
	
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int temp = 1;
	for(int i = 1; i <= n - 1; i++){
		a[i] = lcm(a[i],a[i+1]);
		temp = lcm(temp,a[i]);
	}
	temp = lcm(temp,a[n]);
	int res = a[1];
	
	for(int i = 1; i <= n - 1; i++){
		res = gcd(res,a[i]);
	}
	res = gcd(res, temp);
	cout << res  << endl;

}