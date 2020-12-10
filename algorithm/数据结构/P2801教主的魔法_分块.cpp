#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1000005,SQ = 1005;
int st[SQ];//st[i]表示第i块的第一个元素的下标
int ed[SQ];//ed[i]表示i号块最后一个元素的下标
int bel[maxn];
int siz[SQ];
int a[maxn];
int mark[SQ];
int n,t;
vector<int> v[SQ];
void init_block(){
	int sq = sqrt(n);
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
void update(int b){
	for(int i = 0; i < siz[b]; ++i){ 
		v[b][i] = a[st[b] + i];
	}
	sort(v[b].begin(),v[b].end());
}
int read(){
    int r;
    char c;int f=1;
    while(!isdigit(c=getchar()))
        if(c=='-') f=-1;
    r=c^'0';
    while(isdigit(c=getchar())) r=r*10+(c^'0');
    return r*=f;
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	
	n = read();
	t = read();
	init_block();
	int sq = sqrt(n);
	for(int i = 1; i <= n; ++i){
		a[i] =read();
	}
	for(int i = 1; i <= sq; ++i){
		for(int j = st[i]; j <= ed[i]; ++j){
			v[i].push_back(a[j]);
		}
	}
	for(int i = 1; i <= sq; ++i){
		sort(v[i].begin(),v[i].end());
	}

	char c;
	int L,R,k;
	while(t--){
		scanf(" %c", &c);
		L = read();
		R = read();
		k = read();
		if(c == 'M'){ 
			if(bel[L] == bel[R]){
				for(int i = L; i <= R; ++i){
					a[i] += k;
					
				}
				update(bel[L]);
				continue;
			}
			for(int i = L; i <= ed[bel[L]]; ++i){
				a[i] += k;
			} 
			for(int i = st[bel[R]]; i <= R; ++i){
				a[i] += k;
			}
			update(bel[L]);
			update(bel[R]);
			for(int i = bel[L] + 1; i < bel[R]; ++i){
				mark[i] += k;
			}
		}else{	
 
			int tot = 0;
			if(bel[L] == bel[R]){
				for(int i = L; i <= R; ++i){
					if(a[i] + mark[bel[L]] >= k)
						tot++;
				} 
				printf("%d\n", tot);
				
				continue;
			}
			for(int i = L; i <= ed[bel[L]]; ++i){
				if(a[i] + mark[bel[L]] >= k)
					tot++;
			} 
			for(int i = st[bel[R]]; i <= R; ++i){
				if(a[i] + mark[bel[R]] >= k)
					tot++;
			}

			for(int i = bel[L] + 1; i < bel[R]; ++i){
				// 相当于两边都减掉begin()约掉了
				tot += v[i].end() - lower_bound(v[i].begin(),v[i].end(),k-mark[i]);
			}
 
			printf("%d\n", tot);
		}

	}
	return 0;
}