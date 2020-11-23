#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200005;
//树链刨分模板
int n,k=0,x,head[maxn],q,deep[maxn],f[maxn],size[maxn];
int re[maxn],top[maxn],son[maxn],num=0,pos[maxn];
char s[15];
struct node
{
    int to,next;
} edge[maxn<<1];
struct Node
{
    int left,right,flag,sum;
} tree[maxn<<2];
void add(int u,int v)
{
    edge[++k].to=v;
    edge[k].next=head[u];
    head[u]=k;
}
void dfs1(int x,int fa,int depth)
{
    size[x]=1;
    f[x]=fa;
    deep[x]=depth;
    for(int i=head[x];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        dfs1(edge[i].to,x,depth+1);
        size[x]+=size[edge[i].to];
        if(!son[x]||size[edge[i].to]>size[son[x]]) son[x]=edge[i].to;
    }
}
void dfs2(int x,int tp)
{
    re[x]=++num;
    pos[re[x]]=x;
    top[x]=tp;
    if(!son[x]) 
        return;
    dfs2(son[x],tp);
    for(int i=head[x];i;i=edge[i].next)
    {
        if(edge[i].to!=son[x]&&edge[i].to!=f[x])
            dfs2(edge[i].to,edge[i].to);
    }
}
void build(int id,int l,int r)
{
    tree[id].left=l;tree[id].right=r;
    tree[id].sum=0;tree[id].flag=-1;
    if(l==r) 
        return;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);build(id<<1|1,mid+1,r);
    return;
}
void down(int id)
{
    tree[id<<1].sum=(tree[id<<1].right-tree[id<<1].left+1)*tree[id].flag;
    tree[id<<1|1].sum=(tree[id<<1|1].right-tree[id<<1|1].left+1)*tree[id].flag;
    tree[id<<1].flag=tree[id<<1|1].flag=tree[id].flag;
    tree[id].flag=-1;
}
int get(int id,int l,int r)
{
    if(tree[id].right<l||tree[id].left>r) 
        return 0;
    if(tree[id].right<=r&&tree[id].left>=l) 
        return tree[id].sum;
    if(tree[id].flag!=-1) 
        down(id);
    return get(id<<1,l,r)+get(id<<1|1,l,r);
}
void update(int id,int l,int r,int val)
{
    if(tree[id].right<l||tree[id].left>r) return;
    if(tree[id].right<=r&&tree[id].left>=l)
    {
        tree[id].sum=(tree[id].right-tree[id].left+1)*val;
        tree[id].flag=val;
        return;
    }
    if(tree[id].flag!=-1) 
        down(id);
    update(id<<1,l,r,val);
    update(id<<1|1,l,r,val);
    tree[id].sum=tree[id<<1].sum+tree[id<<1|1].sum;
    return;
}
void change(int u,int v,int val)
{
    while(top[u]!=top[v])
    {
        if(deep[top[u]]<deep[top[v]]) 
                std::swap(u,v);
        update(1,re[top[u]],re[u],val);
        u=f[top[u]];
    }
    if(deep[u]>deep[v]) 
        std::swap(u,v);
    update(1,re[u],re[v],val);
    return;
}
int main()
{
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        cin>>x;
        x++;
        add(x,i);
    }
    dfs1(1,1,1);
    dfs2(1,1);
    cin>>q;
    build(1,1,num);
    for(int i=1;i<=q;i++)
    {
        scanf("%s",s);
        cin>>x;;x++;
        int t1=tree[1].sum;
        if(s[0]=='i')
        {
            change(1,x,1);
            int t2=tree[1].sum;
            cout<<abs(t2-t1)<<endl;
            
        }
        if(s[0]=='u')
        {
            update(1,re[x],re[x]+size[x]-1,0);
            int t2=tree[1].sum;
            cout<<abs(t1-t2)<<endl;
        }
    }
    return 0;
}