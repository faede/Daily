#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 50 +5;
int a[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int n;
	while(t--){
		int x;
		cin >> n;
		long long s = 0;
		long long num[2] = {};
		for(int i = 1; i <= n; i++){
			scanf("%d",&a[i]);
			s += a[i];
			num[i%2] += a[i] - 1;
		}
		if( 2* num[0] <= s){
			for(int i = 1; i <= n; i++){
				if(i % 2 == 0){
					a[i] = 1;
				}
			}
		}else{
			for(int i = 1; i <= n; i++){
				if(i % 2 == 1){
					a[i] = 1;
				}
			}
		}
		for(int i = 1; i <= n; i++){
			cout << a[i] << " ";
		}
		cout << endl;

	}
	
}