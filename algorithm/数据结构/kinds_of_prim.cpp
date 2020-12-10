#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1000;
const int maxm = 4000;
const int INF = 1e9;
int n;
int cnt = 0;
int sum = 0;
int head[maxn];
int vis[maxn];
int dis[maxn];
int k = 0;
struct Edge
{
	int to,next,v;
}edges[maxm];// 无向图记得改成     maxm <<1
typedef struct node
{
	int num;
	int val;
	node(int _num,int _val) : num(_num),val(_val){}
	bool operator < (const node &other) const {
		return val > other.val;
	}

}node;
void addedge(int from,int to, int v){
	edges[cnt].to = to;
	edges[cnt].v = v;
	edges[cnt].next = head[from];
	head[from] = cnt ++;
}

void prim(int s){
	for(int i = 0; i < n; ++i){
		dis[i] = INF;
		vis[i] = 0;
	}
	priority_queue<node>q;
	dis[s] = 0;
	q.push(node(s,0));
	while(!q.empty()){
		node p = q.top();
		q.pop();
		int key = p.num;
		if(vis[key])
			continue;
		vis[key] = 1;
		++k;
		sum += p.val;
		for(int i = head[key]; i != -1; i = edges[i].next){
			int t = edges[i].to;
			if( !vis[t] && dis[t] > edges[i].v){
				dis[t] = edges[i].v;
				q.push(node(t,dis[t]));
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int m,x,y,w;


	cin>>n>>m;
	for(int i = 0 ; i < n; ++i)
		head[i] = -1;
	for(int i = 0 ; i < m; ++i){
		cin>>x>>y>>w;
		addedge(x-1,y-1,w);
		addedge(y-1,x-1,w);
	}
	prim(0);
	auto tag = [=]()->bool {return k==n;};
	tag();
	if(k==n){
		cout << sum;
	}
	else{
		cout <<"orz";
	}

	return 0;
}