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
		if((r + i) <= 1000000000 && (r + i) % l == 0 || l % (r + i) == 0){
			return r + i;
		}else if((r-i) >= 1 && (r - i) % l == 0 || l % (r + i) == 0){
			return r - i;
		}
	}
}
int main(){
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int n;
	while(t--){
		int n;
		cin >> n;
		int last = 0;
		int pos = 0;
		int ml = 0;
		int mach_time = 0;
		int t,x;
		int cnt = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d %d",&t,&x);
			if(mach_time <= t){
				if(abs(pos - x) <= abs(t - mach_time)){
					cnt++;
					ml = mach_time;
					mach_time += abs(pos - x);
					last = pos;
					pos = x;
					//cout <<" t:" << t << "dao x:" << x <<"m:"<<mach_time<<endl;
				}else{
					//cout <<" jia le "<< abs(pos - x);
					ml = mach_time;
					mach_time += abs(pos - x);
					last = pos;
					pos = x;
				}
			}else{
				if(last <= pos && last <= x && x <= pos&& ml <= t && t <= mach_time){
					cnt++;
				}else if(pos <= last && pos <=x && x <= last && ml <= t && t <= mach_time){
					cnt++;
				}
			}
		}
		cout << cnt << endl;
	}
	
}