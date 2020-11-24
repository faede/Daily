#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 1000;
const int maxm = 4000;
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
}edges[maxm];
typedef struct node
{
	int num,val;
	node(int _num,int _val):num(_num),val(_val){}
	bool operator < (const node & other)const{
		return val > other.val;
	}
}node;
void init(){
	for(int i = 0; i < n; ++i){
		head[i] = -1;
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
	priority_queue<node> q;
	memset(vis,0,sizeof(vis));

	dis[root] = 0;
	//这里不要vis 否则后边就加不进去了
	q.push(node(root,0));
	while(!q.empty()){
		node p = q.top();
		q.pop();
		int key = p.num;
		if(vis[key])
			continue;
		vis[key] = 1;
		for(int i = head[key]; i != -1 ; i = edges[i].next){
			if(!vis[edges[i].to]&& dis[edges[i].to]  > dis[key] + edges[i].v ){
				dis[edges[i].to] = dis[key] + edges[i].v;
				q.push(node(edges[i].to,dis[edges[i].to]));
			}	
		}
	}
	return 0;
}

int dij_no_pori(int root){
	memset(vis,0,sizeof(vis));
	for(int i = head[root]; i != -1; i = edges[i].next){
		dis[edges[i].to]  = min(dis[edges[i].to],edges[i].v);//min 一下防止重边
	}
	dis[root] = 0;
	vis[root] = 1;
	for(int i = 0; i < n - 1; ++i){
		int min_dis = INF;
		int key	= -1;
		for(int j = 0; j < n; ++j){
			if(!vis[j] && dis[j] < min_dis){
				key = j;
				min_dis = dis[j];
			}
		}
		if(key == -1)
			return key;
		vis[key] = 1;
		for(int j = head[key]; j != -1; j = edges[j].next){
			int t = edges[j].to;
			if(!vis[t] && dis[t] > dis[key] + edges[j].v){
				dis[t] = dis[key] + edges[j].v;
			}
		}
	}
	return 0;
}
int dij_ljjz(int root){
	for(int i = 0; i < n; ++i)
		dis[i] = INF;
	memset(vis,0,sizeof(vis));

	
	for(int i = 0; i < n; ++i){
		dis[i] = e[root][i]; 
	}
	dis[root] = 0; // e[0][0] = INF   这里要后置0
	vis[root] = 1;
	for(int i = 0; i < n - 1; ++ i){
		int min_dis = INF;
		int key = -1;
		for(int j = 0; j < n; ++j){
			if(!vis[j] && dis[j] < min_dis){
				min_dis = dis[j];
				key = j;
			}
		}
		if(key == -1){
			return -1;
		}

		vis[key] = 1;
		for(int j = 0; j < n; ++j){
			if(!vis[j] && dis[j] > dis[key] + e[key][j]){
				dis[j] = dis[key] + e[key][j];
			}
		}
	}
	return 0;
}
int main(){
	init();
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int x,y,w;
	//int n = 0;
	int m;
	int s;

	cin>>n>>m>>s;

	for(int i = 0; i < n; ++i)
		dis[i] = 0x7fffffff;
	for(int i = 0 ; i < m; ++i){
		cin>>x>>y>>w;
		addedge(x - 1,y - 1,w);
		e[x - 1][y - 1] = w;
	}
	//dij_lsxqx(s-1);
	dij_lsxqx(s - 1);
	for(int i = 0; i < n; i ++ ){
		cout << dis[i]<<" ";
	}

}
