#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2000000 + 10;


int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	long long p,q;
	while(t--){
		scanf("%lld %lld", &p, &q);
		if(q > p){
			cout << p << endl;
		}else if(q == p){
			bool tag = true;
			for(long long  i = 2; i < 1e5 + 1; i++){
				if(p % i == 0){
					cout << p/i << endl;
					tag = false;
					break;
				}
			}
			if(tag)
				cout << 1 << endl;
		}else{
			if(p % q != 0){
				cout << p << endl;
			}else{
				long long ans = -1;
				for(long long i = 2; i < 1e5 + 1; i++){
					if(q % i == 0){
						long long temp = p;
						while(1){
							temp /= i;
							if(temp % q != 0){
								ans = max(ans, temp);
								break;
							}
							if(temp % i != 0){
								break;
							}
						}
					}
				}
				while(1){
					p /= q;
					if(p %q != 0){
						ans	= max(ans, p);
						break;
					}
				}
				cout << ans << endl;
			}
			

		}
	}
}