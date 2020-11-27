#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
// 树形dp求树的直径

// 三次dfs 第一次找到距离最大的节点 （直径的一个节点
// 第二次从第一次找到的直径的其中一个节点出发 再找一次距离最大的节点 另一个节点
// 最后再从另一个直径出发再次更新一次距离


// 这阴间题目链式前向星会mle 要换成临接矩阵 ):  
// 我不想打了((
const int maxn = 10000+5;
int head[maxn];
int dp[maxn];
int cnt = 0;
int n;
int max_len = 0;
int max_len_pos = 0;
struct Edge
{
	int to,next,v;
}edges[2*maxn];
void addedge(int from, int to, int v){
	edges[++cnt].to = to;
	edges[cnt].v = v ;
	edges[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int temp,int fa,int len){
	if(max_len <= len){
		max_len = len;
		max_len_pos = temp;
	}
	for(int i = head[temp]; i; i = edges[i].next){
		int t = edges[i].to;
		if( t == fa)
			continue;
		dfs(t,temp,len + edges[i].v);
		dp[t] = max(dp[t] , edges[i].v+len);
	}
}
int main(){
	while(cin>>n)
	{
		int from,v;
		for(int i = 1; i <= n; ++i)
			dp[i] = 1;
		for(int i = 2; i <= n ; ++i){
			scanf("%d %d",&from,&v);
			addedge(from,i,v);
			addedge(i,from,v);
		}
		dfs(1,-1,0);
		dfs(max_len_pos,-1,0);
		dfs(max_len_pos,-1,0);
		for(int i = 1; i <= n; ++i){
			cout<<dp[i]<<endl;
		}
	}
}