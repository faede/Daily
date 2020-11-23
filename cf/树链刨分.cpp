#include<iostream>
using namespace std;
const int maxn = 1e5+10;
struct edge
{
	int next,to;
}e[2*maxn];
struct Node
{
	int l,r,ls,rs,lazy,sum;
}node[2*maxn];
int rt,n,m,r,a[maxn],head[maxn],f[maxn],d[maxn],size[maxn],son[maxn],rk[maxn],top[maxn],id[maxn];
int main(){

}