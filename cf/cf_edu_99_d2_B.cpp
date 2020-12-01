#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;

int main(){
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	ll x;

	while(t--){
		cin >> x;
		ll i = 1;
		for(;  1 ; i++){
			if(i*(i+1)/2 >= x){
				break;
			}
		}
		if(i*(i+1)/2 == x){
			cout<< i <<endl;
			//continue;
		}
		else{
			ll j = i;
			for(; 1; j--){
				if((i-j+1)*(j+i)/2 >= i*(i+1)/2 - x)
					break;
			}
			cout<< i - (i - j + 1) <<endl;
		}
		
		//cout << ans << endl;
	}




	return 0;
}