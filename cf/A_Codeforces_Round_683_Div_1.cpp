#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2000000 + 10;
int n;
struct wp
{
	int num;
	int v;
	bool operator < (const struct wp & rhs) const{
		if(v == rhs.v){
			return num < rhs.num;
		}
		return v < rhs.v;
	}
} a[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;

	while(t--){
		long long W;
		cin >> n >> W; 
		for(int i = 1; i <= n; ++i){
			a[i].num = i;
			scanf("%d" ,&a[i].v);
		}
		sort(a+1,a+1+n);
		long long temp = 0;
		int last = -1;
		bool tag = false;
		for(int i = 1;i <= n; i++){
			if(temp + a[i].v <= W){
				last = i;
				temp += a[i].v;
				if(temp >= W/2){
					tag = true;
					break;
				}
			}else{
				//tag = false;
				break;
			}
		}
		if(tag){
			cout << last << endl;
			for(int i = 1; i <= last; i++){
				cout << a[i].num <<" ";
			}
			cout << endl;
		}
		else{
			cout << -1 << endl;
		}

	}
	
}