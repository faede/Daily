#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 6000+10;
int head[2*maxn];
int a[maxn];
int check_not_hightest[maxn];
int dp[maxn][2];//  子树的值都计算出来了 0不参加 1 参加
int n;
int cnt = 0;
struct Edge
{
	int to ,next;
}edges[maxn];
void addedge(int from, int to){
	edges[++cnt].to = to;
	edges[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int fa){
	for(int i = head[fa]; i ; i = edges[i].next){
		int t = edges[i].to;
		dfs(t);
		dp[fa][1] += dp[t][0];
		dp[fa][0] += max(dp[t][0],dp[t][1]); 
	}
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		scanf("%d",&dp[i][1]);
	}
	int from,to;
	for(int i = 1; i <= n - 1; ++i){
		scanf("%d %d",&from,&to);
		check_not_hightest[from] = 1;
		addedge(to,from);
	}
	//注意这里保证是一个树 那么自然不含环 n-1 个节点都有上级，剩下的那个就是大老板
	for(int i = 1; i <= n; ++i){
		if(!check_not_hightest[i]){
			dfs(i);
			cout<<max(dp[i][0],dp[i][1]);
		}
	}
}