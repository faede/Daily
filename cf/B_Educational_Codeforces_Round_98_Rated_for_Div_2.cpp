#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000+10;
//int a[maxn];
int n;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		//int n;
		cin >> n;
		long long vmax = -1;
		long long sum = 0;
		long long x;
		for(int i = 1; i <= n; i++){
			scanf("%lld", &x);
			sum += x;
			vmax = max(vmax,x);
		}
		vmax = max(vmax, (sum + n - 2)/(n-1));
		cout <<vmax*(n-1) - sum << endl;
		
	}
	
}