#include <iostream>
using namespace std;
const int maxn = 10000 + 10;
#define ll long long 
int  mod;
ll a[maxn];
ll ans[maxn * 4];
ll add_tag[maxn * 4];
ll mul_tag[maxn * 4];
inline ll ls(ll x){
	return x << 1;
}
inline ll rs(ll x){
	return x << 1 | 1;
}
void push_up(ll p){
	ans[p] = (ans[ls(p)] + ans[rs(p)])%mod;
}
void build(ll p, ll l, ll r){
	mul_tag[p] = 1;
	add_tag[p] = 0;
	if( l == r){
		ans[p] = a[l];
		return ;
	}
	ll mid = (l + r) >> 1;
	build(ls(p),l,mid);
	build(rs(p),mid + 1,r);
	push_up(p);
}
void push_down(ll p,ll l, ll r){
	// mul and add
	// 这一步需要规定一个顺序，到底是先加还是先乘
	// 考虑一个两层的问题， 子节点: 现在有 add_tag 1, mul_tag 4

	// 如果是先算加:
 	// 父节点传来一个 add_tag 2也就是说要把底下的值都加上二 如果我们先算 add_tag
 	// add_tag = 1 + 2 = 4 但是子节点之前说要把底下的值都乘4 ，但是先算加的话
 	// 再乘4 就肯定多了 因为后多加的2 并不需要乘4 显然这样mul的值需要变化，很麻烦

	// 如果是先算乘:
 	// 我们再考虑先算乘的情况 由于乘是先算的 所以当add_tag 2来的时候，只需要把之前的
 	// add_tag + 2 就好，mul_tag是不会产生影响的，因为当传下去的时候mul_tag已经被
 	// 计算过了， 当上方传来 mul_tag的时候也不会产生影响，我们只需要把子树的add_tag 和 mul_tag
 	// 都 乘上传来的mul_tag 就可以保持对底层节点的修改是正确的


	ll mid = (l + r) >> 1;
	add_tag[ls(p)] = ( (add_tag[ls(p)] * mul_tag[p])%mod + add_tag[p] )%mod;
	add_tag[rs(p)] = ( (add_tag[rs(p)] * mul_tag[p])%mod + add_tag[p] )%mod;

	mul_tag[ls(p)] = (mul_tag[ls(p)] * mul_tag[p])%mod;
	mul_tag[rs(p)] = (mul_tag[rs(p)] * mul_tag[p])%mod;

	ans[ls(p)] = ( (ans[ls(p)] * mul_tag[p])%mod + ( (mid - l + 1)*add_tag[p])%mod )%mod;
	// (r - (mid + 1) +1) = r - mid
	ans[rs(p)] = ( (ans[rs(p)] * mul_tag[p])%mod + ( (r - mid)*add_tag[p])%mod )%mod;

	add_tag[p] = 0;
	mul_tag[p] = 1;

}
// [nl,nr]要修改的区间  [l , r]当前区间 
void update_add(ll p, ll nl, ll nr, ll l, ll r, ll k){
	if( nl <= l && r <= nr ){
		ans[p] = (ans[p] + k*(r - l + 1))%mod;
		add_tag[p] = (add_tag[p] + k)%mod;
		return ;
	}
	ll mid = (l + r) >>1;
	push_down(p,l,r);
	if(nl <= mid){
		update_add(ls(p),nl,nr,l,mid,k);
	}
	if(mid < nr){
		update_add(rs(p),nl,nr,mid+1,r,k);
	}
	push_up(p);
}
void update_mul(ll p, ll nl, ll nr, ll l, ll r, ll k){
	if( nl <= l && r <= nr ){
		ans[p] = (ans[p]*k)%mod;
		mul_tag[p] = (mul_tag[p]*k)%mod;
		add_tag[p] = (add_tag[p]*k)%mod;
		return ;
	}
	ll mid = (l + r) >>1;
	push_down(p,l,r);
	if(nl <= mid){
		update_mul(ls(p),nl,nr,l,mid,k);
	}
	if(mid < nr){
		update_mul(rs(p),nl,nr,mid+1,r,k);
	}
	push_up(p);
}
ll query(ll p,ll nl, ll nr,ll l, ll r){
	ll res = 0;
	if(nl <= l && r <= nr){
		return ans[p];
	}
	ll mid = (l + r) >> 1;
	push_down(p,l,r);
	if(nl <= mid){
		res += query(ls(p),nl,nr,l,mid);
	}
	if(mid < nr){
		res += query(rs(p),nl,nr,mid+1,r);
	}
	res = res%mod;
	return res;
}

int main(){
    int n, m;
    freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    scanf("%d%d%d", &n, &m, &mod);
    for(int i=1; i<=n; i++){
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    while(m--){
        int chk;
        scanf("%d", &chk);
        int x, y;
        long long k;
        if(chk==1){
            scanf("%d%d%lld", &x, &y, &k);
            update_mul(1, x, y, 1, n,k);
        }
        else if(chk==2){
            scanf("%d%d%lld", &x, &y, &k);
            update_add(1, x, y, 1, n,k);
        }
        else{
            scanf("%d%d", &x, &y);
            printf("%lld\n", query(1, x, y, 1, n));
        }
    }
    return 0;
}