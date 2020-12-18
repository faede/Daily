#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 50 +5;
int a[maxn];
int b[maxn];
int gcd(int a,int b){
	if(b == 0)
		return a;
	return gcd(b,a%b);
}
int gtn(int l,int r){
	for(int i = 1; ;i++){
		if((r + i) <= 1000000000 && ( (r + i) % l == 0 || l % (r + i) == 0)){
			return r + i;
		}else if((r-i) >= 1 && ((r - i) % l == 0 || l % (r + i) == 0)){
			return r - i;
		}
	}
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int n;
	while(t--){
		long long tot = 0;
		int x;
		cin >> n;
		long long temp = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d",&a[i]);
		}

		b[1] = a[1];
		for(int i = 1; i < n; ++i){
			if(b[i]%a[i+1] == 0 || a[i+1] % b[i] == 0){
				b[i+1] = a[i+1];
				continue;
			}
			else{
					b[i + 1] = gtn(a[i],a[i+1]);
					//cout <<"a:" << a[i] <<" " <<a[i+1] << " "<<b[i+1] << endl;
			}
		}

		for(int i = 1; i < n; ++i){
			cout << b[i] <<" ";
		}

		cout<< b[n] << endl;

	}
	
}