#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#define ll long long 
using namespace std;


const int maxn = 100000+10;
char a[maxn];
int c[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,t,p,k;
	cin >> t;
	while(t--){
		cin >> n >> p >>k;
		scanf("%s",a+1);
		for(int i = n; i >=1; i--){
			if(i + k <= n){
				c[i] = c[i+k] + ('1' - a[i]); 
			}else{
				c[i] = '1' - a[i];
			}
		}
		int x,y;
		cin >> x >>y;
		ll ans = 0x3f3f3f3f;
		for(ll i = p; i <= n; ++i) {
            ans = min(ans, y * (i - p) + c[i] * x);
        }
       	cout << ans<<endl;

	}

	return 0;
}