#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn = 1e6+10;
int st[maxn];//st[i]表示第i块的第一个元素的下标
int ed[maxn];//ed[i]表示i号块最后一个元素的下标
int bel[maxn];
int siz[maxn];
int a[maxn];
int sum[maxn];
int mark[maxn];
int sq;
int n;
void init_block(){
	sq = sqrt(n);
	for(int i = 1; i <= sq; ++i){
		st[i] = n / sq * (i - 1) + 1;
		ed[i] = n / sq * i;
 	}
 	ed[sq] = n;
 	for(int i = 1; i <= sq; ++i){
 		for(int j = st[i]; j <= ed[i]; ++j){
 			bel[j] = i; // 表示j号元素归属i
 		}
 	}
 	for(int i = 1; i <= sq; ++i){
 		siz[i] = ed[i] - st[i] + 1;
 	}
}
void update(int x,int y){
	if(bel[x] == bel[y]){
		for(int i = x;  i <= y; ++i){
			a[i] += k;
			sum[bel[i]] += k; //这个被加了多次 
		}

		return ;
	}
	for(int i = x; i <= ed[bel[x]]; ++i){
		a[i] += k;
		sum[bel[i]] += k;
	} 
	for(int i = st[bel[y]]; i <= y; ++i){
		a[i] += k;
		sum[bel[i]] += k;
	}
	for(int i = bel[x] + 1; i < bel[y]; ++i){
		mark[i] += k;
	}
}

void query(int x,int y)
{
	int s = 0;
	if(bel[x] == bel[y]){
		for(int i = x;  i <= y; ++i){
			s += a[i] + mark[bel[i]];
		}

		return s;
	}
	for(int i = x; i <= ed[bel[x]]; ++i){
		s += a[i] + mark[bel[i]];
	} 
	for(int i = st[bel[y]]; i <= y; ++i){
		s += a[i] + mark[bel[i]];
	}
	for(int i = bel[x] + 1; i < bel[y]; ++i){
		s += sum[i] + mark[i]*siz[i];
	}
	return s;
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	coin >> n >> t;

	init_block();
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}
	for(int i = 1; i <= sq; ++i){
		for(int j = st[i]; j <= ed[i]; ++j){
			sum[i] += a[j];
		}
	}

}