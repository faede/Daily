#include <iostream>
#include <queue>
using namespace std;
const int maxn = 1000;
int head[maxn];
int n = 50;
int cnt = 0;
int dis[maxn];
int vis[maxn];
int e[maxn][maxn];
const int INF = 1e9;
struct Edge
{
	int to;
	int next;
	int v;	
}edges[maxn];
typedef struct node
{
	int num,val;
	node(int _num,int val):num(_num),val(_val){}
}node;
void init(){
	memset(head,-1,sizeof(head));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			e[i][j] = INF;
		}
	}
}
void addedge(int from,int to,int v){
	// set edge
	edges[cnt].to = to;
	edges[cnt].v = v;
	// next[i] -> .. ->..
	// next[i+1] -> .. -> ..
	edges[cnt].next = head[from];
	head[from] = cnt++;
}
int dij_lsxqx(int root){
	priority_queue<int,[](node a,node b){return a.val < b.val}> q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));

	dis[root] = 0;
	q.push(node(root,0));
	while(!q.empty()){
		node p = q.top();
		q.pop();
		int key = p.num;
		if(vis[key])
			continue;
		vis[key];
		for(int i = head[k]; i != -1 ; i = edges[i].next){
			if(dis[edges[i].to]  < dis[key] + edges[i].v){
				dis[edges[i].to] = dis[key] + edges[i].v;
				q.push(node(i,dis[edges[i].to]));
			}
		}
	}
}
int dij_no_pori(int root){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));

	dis[root] = 0;
	vis[root] = 1;
	for(int i = head[root]; i != -1; i = edges[i].next){
		dis[edges[i].to]  = edges[i].v;
	}
	for(int i = 0; i < n - 1; ++i){
		int min_dis = INF;
		int key	= -1;
		for(int j = 0; j < n; ++j){
			if(dis[j] < min_dis){
				key = j;
				min_dis = dis[j];
			}
		}
		if(key == -1)
			return key;
		vis[key] = 1;
		for(int j = head[key]; j != -1; j = edges[j].next){
			if(dis[edges[j].to] < dis[key] + edges[j].v){
				dis[edges[j].to] = dis[key] + edges[j].v;
			}
		}
	}
}
int dij_ljjz(int root){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));

	dis[root] = 0;
	vis[root] = 1;
	for(int i = 0; i < n; ++i){
		dis[i] = e[root][i];
	}
	for(int i = 0; i < n - 1; ++ i){
		int min_dis = INF;
		int key = -1;
		for(int j = 0; j < n; ++j){
			if(!vis[j] && dis[j] < min_dis){
				min_dis = j;
				key = j;
			}
		}
		if(key == -1){
			return -1;
		}

		vis[key] = 1;
		for(int j = 0; j < n; ++j){
			if(dis[j] < dis[key] + e[key][j]){
				dis[j] = dis[key] + e[key][j];
			}
		}
	}

}
int main(){

}
