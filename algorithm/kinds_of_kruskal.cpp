#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000;
const int maxm = 1000;
int n,m;
int a[maxn];
int fa[maxn];
int sum = 0;
int cnt;
struct Edge
{
	int from;
	int to;
	int v;
	bool operator < (const Edge & other)const
	{
		return v < other.v;
	}

}edges[maxn];

int find(int x){
	while(x != fa[x]){
		fa[x] = fa[fa[x]];
		x = fa[x];
	}
	return x;
}

void kruskal(){
	sort(edges+m,edges+m);
	int fa_x,fa_y;
	for(int i = 0; i < m; i++){
		fa_x = find(edges[i].from);
		fa_y = find(edges[i].to);
		if(fa_x == fa_y){
			continue;
		}
		fa[fa_y] = fa_x;
		sum += edges[i].v;
		if(++cnt == n){
			break;
		}
	}
}

int main(){
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	cin>>n>>m;
	for(int i = 1; i <= n; ++i){
		fa[i] = i;
	}
	for(int i = 0; i < m; ++i){
		cin>>edges[i].from;
		cin>>edges[i].to;
		cin>>edges[i].v;
	}
	kruskal();
	cout<<sum;

}
