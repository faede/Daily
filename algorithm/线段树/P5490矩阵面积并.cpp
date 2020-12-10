#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define lson (x << 1)
#define rson (x << 1 | 1)
#define ll long long


const int maxn =1e6 + 10;
int n,cnt = 0;
ll x1,y11,x2,y2,X[maxn << 1];// y1 不用是因为和cmath冲突((

struct ScanLine
{
	ll l,r,h;
	int mark; // 维护 出入边 1 / -1
	bool operator < (const ScanLine & rhs)const{
		return h < rhs.h;
	}
}line[maxn << 1];

struct SegTree
{
	// sum : 被完全覆盖的次数.
	// len : 区间被截的长度.
	int l,r,sum ;
	ll len;
}tree[maxn << 2];

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].len = 0;
	tree[x].sum = 0;
	if(l == r)
		return ;
	int mid = (l + r) >> 1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	return ;
}

void push_up(int x){
	int l = tree[x].l;
	int r = tree[x].r;
	if(tree[x].sum){
		tree[x].len = X[r + 1] - X[l];
	}else{
		tree[x].len = tree[lson].len + tree[rson].len;
	}
}

void update(int x, ll L, ll R, int c){
	int l = tree[x].l;
	int r = tree[x].r;
	if(X[r+1] <= L || R <= X[l])
		return ;
	if(L <= X[l] && X[r+1] <= R){
		tree[x].sum += c;
		push_up(x);
		return;
	}
	update(lson,L,R,c);
	update(rson,L,R,c);
	push_up(x);

}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		scanf("%lld %lld %lld %lld",&x1,&y11,&x2,&y2);
		X[2*i - 1] = x1;
		X[2*i] = x2;
		line[2*i - 1] = (ScanLine){x1,x2,y11,1};
		line[2*i] = (ScanLine){x1,x2,y2,-1};
	}

	n = (n << 1);
	sort(line + 1,line + n + 1);
	sort(X + 1, X + n + 1);
	int tot = unique(X+1,X+n+1) - X - 1;

	/*
	这里有个问题就是为什么维护区间的时候要采用r+1的形式,举例来说 如果总区间为[1,5]
	要修改的区间为[2,4]这里(2+4)>>1=3 按朴素线段树来修改的话要修改区间 [2,3][4,4]
	但是[4,4]只有一个点,我们无法修改 因为len = 0实际上只修改了[2,3],
	而[4,4]也就是真实的[3,4]被丢掉了

	于是我们可以换一种思路,叶子节点不再维护点,而是维护区间[2,2]就是在修改[2,3]
	而[2,3]就是在修改[2,4]
	所以我们要修改[2,4]现在的表示就是[2, 3],就是(2+3)>>1=2 [2,2]和[3,3]对应要修改的
	区间就是[2,3]和[3,4]

	所以这里build的参数不再是点数tot,而是边数tot-1,之后维护的时候也要注意线段树中的r,加一之后
	才是真实的区间右端点
	*/
	build(1,1,tot-1);

	ll ans = 0;
	for(int i = 1; i < n; ++i){
		update(1,line[i].l,line[i].r,line[i].mark);
		ans += tree[1].len*(line[i+1].h - line[i].h);
	}
	printf("%lld", ans);

}