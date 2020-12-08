#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200;
typedef struct block
{
	int x,y,z;
	block(int _x, int _y, int _z):x(_x),y(_y),z(_z){

	}
	bool operator < (const block & rhs) const{
		if(x == rhs.x){
			return y < rhs.y;
		}
		return x < rhs.x;
	}
}block;
//vector<block> v;
int dp[maxn]; // 以i为底部的最大高度
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int n;
	int x,y,z;
	int k = 0;
	while(scanf("%d",&n) && n != 0){
		++k;
		memset(dp,0,sizeof(dp));
		vector<block> v;
		for(int i = 1; i <= n; ++i){
			scanf("%d %d %d",&x,&y,&z);
			v.push_back(block(x,y,z));
			v.push_back(block(x,z,y));
			v.push_back(block(y,x,z));
			v.push_back(block(y,z,x));
			v.push_back(block(z,y,x));
			v.push_back(block(z,x,y));
		}
		sort(v.begin(),v.end());
		int ans = -1;
		for(int i = 0; i < v.size();++i){
			dp[i] = v[i].z;
			for(int j = i - 1; j >= 0; j--){
				if(v[j].x < v[i].x && v[j].y < v[i].y && dp[j] + v[i].z > dp[i]){
					dp[i] = dp[j] + v[i].z;
				}
			}
			ans = max(ans,dp[i]);
		}
		printf("Case %d: maximum height = %d\n", k,ans);
	}
}