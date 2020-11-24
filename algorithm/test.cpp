#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 1000;
int head[maxn];
int n = 50;
int cnt = 0;
int dis[maxn];
int vis[maxn];
struct Edge
{
    int to;
    int next;
    int v;  
}edges[maxn];
typedef struct node
{
    int num,val;
    node(int _num,int _val):num(_num),val(_val){}
    bool operator < (const node & other)const{
        return val > other.val;
    }
}node;
void addedge(int from,int to,int v){
    // set edge
    edges[cnt].to = to;
    edges[cnt].v = v;
    // next[i] -> .. ->..
    // next[i+1] -> .. -> ..
    edges[cnt].next = head[from];
    head[from] = cnt++;
}
inline void dijkstra_2(int s)
{
	std::priority_queue<node> q;
    dis[s] = 0;
    q.push(node(s,0));
    while( !q.empty() )
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.num, d = tmp.val;
        if( vis[x] )
            continue;
        vis[x] = 1;
        for( int i = head[x]; i != -1; i = edges[i].next )
        {
            int y = edges[i].to;
            if( dis[y] > dis[x] + edges[i].v )
            {
                dis[y] = dis[x] + edges[i].v;
                if( !vis[y] )
                {
                    q.push(node(y,dis[y]));
                }
            }
        }
    }
}
int main(){
    //init();
    
    freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    int m,s;
    //scanf( "%d%d%d", &n, &m, &s );
    cin>>n>>m>>s;
    for(int i = 0 ; i < 1000; ++i)
        head[i] = -1;

    for(int i = 0; i < n; ++i)dis[i] = 0x7fffffff;
    for( register int i = 0; i < m; ++i )
    {
        register int u, v, d;
        cin>>u>>v>>d;
        //scanf( "%d%d%d", &u, &v, &d );
        addedge( u - 1, v - 1, d );
    }
    dijkstra_2(s - 1);
    for( int i = 0; i < n; i++ )
        printf( "%d ", dis[i] );
    return 0;
    

}
