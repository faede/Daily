#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll maxn = 50 +5;
bool isfair(ll x){
	ll temp = x;
	while(temp > 0){
		if(temp % 10 > 0 && x % (temp%10) != 0)
			return false;
		temp /= 10;
	}
	return true;
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		ll n;
		cin >> n;
		for(;;n++){
			if(isfair(n))
			{
				cout << n  << endl;
				break;
			}
		}
	}
	
}