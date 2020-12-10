#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// 原模板来自：https://www.cnblogs.com/chinhhh/p/7965433.html

const long long maxn = 200000 + 10;
long long mod = 1;
long long head[maxn];
long long nex[maxn];
long long to[maxn];
long long w[maxn];


long long dep[maxn];
long long fa[maxn];
long long siz[maxn]; // siz包含自己
long long son[maxn];
long long id[maxn];
long long top[maxn];
long long cnt;//给dfs序标记用的
long long e;  //给链式前向星用的

long long a[maxn<<2],lazy[maxn<<2];//线段树

long long wt[maxn]; //新权值

long long n,m,r,p;

inline void add(long long x,long long y){
	to[++e] = y;
	nex[e] = head[x];
	head[x] = e;
}
// ***************** 线段树 ***********************

inline long long ls(long long x){
	return x << 1;
}
inline long long rs(long long x){
	return x << 1 | 1;
}

void build(long long f,long long l, long long r){
	if(l == r)
	{
		a[f] = wt[l];
		a[f] %= mod; 
		return ;
	}
	long long mid = (l + r) >> 1;
	build(ls(f),l,mid);
	build(rs(f),mid+1,r);
	a[f] = (a[ls(f)] + a[rs(f)]) % mod;
}

inline void pushdown(long long f, long long len){
	lazy[ls(f)] = (lazy[ls(f)]+lazy[f])%mod;
	lazy[rs(f)] = (lazy[rs(f)]+lazy[f])%mod;

	a[ls(f)] += lazy[f]*(len - (len >> 1) );
	a[rs(f)] += lazy[f]*(len >> 1);
	a[ls(f)] %= mod;
	a[rs(f)] %= mod;
	lazy[f] = 0;
}

long long query(long long f,long long l ,long long r, long long L, long long R){
	if(L <= l && r <= R){
		return a[f]%mod;
	}
	long long mid = (l + r) >> 1;
	long long res = 0;
	if(lazy[f])
		pushdown(f,(r-l+1));
	if(L <= mid){
		res += (query(ls(f),l,mid,L,R))%mod;
		res %= mod;
	}
	if(mid < R){
		res += (query(rs(f),mid + 1,r,L,R))%mod;
		res %= mod;
	}
	return res;
}

void update(long long f,long long l, long long r,long long L, long long R,long long k){
	if(L <= l && r <= R){
		lazy[f] = (lazy[f] + k)%mod;
		a[f] = (a[f] + ((k%mod) * ((r - l + 1)%mod) )%mod )%mod; 
		return  ;
	}
	long long mid = (l + r) >> 1;
	if(lazy[f])
		pushdown(f,(r-l+1));
	if(L <= mid)
		update(ls(f),l,mid,L,R,k);
	if(mid < R)
		update(rs(f),mid + 1,r,L,R,k);
	a[f] = (a[ls(f)] + a[rs(f)]) %mod;
}
// ***************** 线段树 ***********************



// temp为当前节点, fa为父节点, deep为深度
void dfs1(long long temp,long long f, long long deep){ 
	dep[temp] = deep;
	fa[temp] = f;
	siz[temp] = 1;//初始化节点大小
	long long maxson = -1; // 重儿子个数
	for(long long i = head[temp]; i ; i = nex[i]){
		long long t = to[i];
		if( t == f){
			continue;
		}
		dfs1(t,temp,deep+1);
		siz[temp] += siz[t];
		if(siz[t] > maxson){
			son[temp] = t;
			maxson = siz[t];
		}
	}

}
void dfs2(long long temp, long long topf){
	// ****************** 重点 *******************
	// 因为顺序是先重再轻, 所以每一条重链的新编号是连续的
	// 因为是dfs, 所以每一个子树的新编号也是连续的
	// ****************** 重点 *******************

	id[temp] = ++cnt; //  新id     dfs序 但是优先重儿子
	wt[cnt] = w[temp];
	top[temp] = topf;
	if(!son[temp])
		return ;
	dfs2(son[temp],topf);// 优先处理重儿子

	// 处理轻儿子
	for(long long i = head[temp]; i ; i = nex[i]){
		long long t = to[i];
		if( t == fa[temp] || t == son[temp]) // 重儿子 和 父节点要跳过
			continue;
		dfs2(t,t); // 轻儿子会自己开一条重链 (如果把叶节点也是视为重链的话)
	}
}

// 区间查询
long long qRange(long long x,long long y){
	// 由于dfs2的得到节点顺序是连续的
	// 我们可以得到运用树链刨分的方式
	// 我们总是将链顶端深度更深的节点上跳 直到他们在一条重链
	// 这样做的好处是： 
	// 1. 两节点在不同重链上时 上跳的节点上升时经过的节点是连续的(在一条重链上)
	// 这样我们就可以很容易的用线段树维护
	// 2. 两节点在一条重链上时 之间的节点自然是连续的，我们也可以用线段树维护



	// 第一步将两节点跳到一条重链上
	long long ans = 0;
	while(top[x] != top[y]){
		// x 置为深度更深的节点
		if(dep[top[x]] < dep[top[y]])
			swap(x,y); 
		ans += (query(1,1,n,id[top[x]],id[x]))%mod;
		ans %= mod;
		x = fa[top[x]];
	}

	// 在一条重链上的节点编号连续，并且深度更深的节点编号更大(是深度浅的子节点)
	// x 置为深度更浅的节点
	if(dep[x] > dep[y])
		swap(x,y);
	ans += (query(1,1,n,id[x],id[y]))%mod;
	return ans % mod;
}

// 查询一个节点以及其子树的点权和：
// 由于dfs2的性质，子树的新编号也是连续的那么我们可以直接用线段树查询
long long qSon(long long x){
	return query(1,1,n,id[x],id[x]+siz[x]-1);
}

// 区间修改
void upRange(long long x,long long y,long long k){
	k %= mod;
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]])
			swap(x,y);
		update(1,1,n,id[top[x]],id[x],k);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])
		swap(x,y);
	update(1,1,n,id[x],id[y],k);
}
void updSon(long long x,long long k){
	update(1,1,n,id[x],id[x] + siz[x] - 1, k);
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/P3384_1.in","r",stdin);
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/testout.txt","w+",stdout);
	cin >>n >>m >>r >>mod;
	for(long long i = 1; i <= n; ++i)
		scanf("%lld",&w[i]);
	for(long long i = 1; i < n; ++i){
		long long a,b;
		scanf("%lld %lld",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs1(r,0,1);
	dfs2(r,r);
	build(1,1,n);
	long long k,x,y,z;
	while(m--){
		scanf("%lld",&k);
		if(k == 1){
			scanf("%lld %lld %lld",&x,&y,&z);
			upRange(x,y,z);
		}
		else if(k == 2){
			scanf("%lld %lld",&x,&y);
			printf("%lld\n",qRange(x,y));
		}
		else if(k == 3){
			scanf("%lld %lld",&x,&y);
			updSon(x,y);
		}else{
			scanf("%lld",&x);
			printf("%lld\n", qSon(x));
		}
	}

}