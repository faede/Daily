#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 10000;
int head[maxn];
int dp[maxn];
int cnt = 0;
int n;
struct Edge
{
	int to,next,v;
}edges[maxn];
void addedge(int from, int to, int v){
	edges[++cnt].to = to;
	edges[cnt].v = v ;
	edges[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int fa){
	if(!head[fa]){
		dp[fa] = 
		return ;
	}
	for(int i = head[fa]; i; i = edges[i].next){
		int t = edges[i].to;
		dfs(t);
		dp[fa] = max(dp[t] + edges[i].v,dp[fa]);
	}
}
int main(){
	cin>>n;
	int from,v;
	for(int i = 1; i <= n; ++i)
		dp[i] = 1;
	for(int i = 2; i <= n + 1; ++i){
		scanf("%d %d",&from,&v);
		addedge(from,i,v);
	}
	dfs(1);
}