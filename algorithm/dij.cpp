#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxm = 400010;  //边
const int maxn = 200010; //点
const int inf = 0x3f3f3f3f;
int q,k,s;
struct Edge
{
    int to,v,next,altitude;
} edge[maxm];
struct node
{
    int num, val,altitude; //存编号 和距离
    node(int _num=0, int _val=0, _altitude):num(_num), val(_val) ,altitude(_altitude){}
    
};
int head[maxn];
int top;
int n,m;
int dis[maxn];

bool vis[maxn];

void init()
{
    memset(head, -1, sizeof(head));
    top = 0;
}

void addedge(int from, int to, int v,int altitude)
{
    edge[top].to = to;
    edge[top].v = v;
    edge[top].altitude = altitude;
    edge[top].next = head[from];
    head[from] = top++;
}
void dijkstra(int st) //起点
{
    priority_queue<node,[](node a,node b) { 
        if(a.altitude <= s && b.altitude)

    }> que;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[st] = 0;
    que.push(node(st, 0));
    while(!que.empty())
    {
        node p = que.top();
        que.pop();
        int nown = p.num;
        if(vis[nown])
            continue;
        vis[nown] = true;
        for(int i=head[nown]; i!=-1; i=edge[i].next)
        {
            Edge e = edge[i];
            if(dis[e.to] > dis[nown] + e.v && !vis[e.to])
            {
                dis[e.to] = dis[nown] + e.v;
                que.push(node(e.to,dis[e.to]));
            }
        }
    }
}
int n ,m;
int main()
{
    int t;
    cin>>t;
    cin>>n>>m;
    int x,y,v,at;
    for(int i = 0 ; i < m; i ++){
        cin>>x>>y>>v>>at;
        addedge(x,y,v,at);
    }
    
    for(int i = 0; i < q; ++i){

    }
    return 0;
}
