#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2000000 + 10;

long long getminf(long long n,long long q){
	for(long long i = 1; i <= n; i++){
		if(n%i == 0){
			if((n/i) < q || (n/i) % q != 0){
				return n/i;
			}
		}
	}
	return 1;
}
int main(){
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	long long x,y;
	while(t--){
		scanf("%lld %lld", &x, &y);
		cout << getminf(x,y) << endl;
	}
	//cout << sqrt((long long)857754240051582063);
}