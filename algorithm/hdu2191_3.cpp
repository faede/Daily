#include <cstdio>
#include <iostream>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;
// *****************  单调队列优化多重背包  *********************
const int maxn = 100+5;
int n,V;
//int price[maxn];
//int height[maxn];
//int cot[maxn];
//int dp[maxn][maxn];
int dp[maxn];
int val[maxn];
/*
  j mod a[i]的值不同则之间的不存在转移关系。
  并且经过下方的推导 我们可以发现，最终的值只会
  从(f[h*a[i]+q]-h*w[i])的最大值转移过去，
  所以我们可以枚举 p q, 用单调队列维护
  (f[h*a[i]+q]-h*w[i])的最大值。
*/




/*
以下是lunch大佬的讲解内容：
f[j]=max(f[j-k*a[i]]+k*w[i]) 

j = p * a[i] + q ;

p = j / a[i];
q = j % a[i];

f[j] = max (f[p * a[i] + q - k * a[i]]+k*w[i])

f[j] = max (f[(p-k)*a[i]+q]  +  k*w[i])


k ∈ [0,min(p,c[i])]
h = p - k ;
h ∈ [p-min(p,c[i]),p]

=>

f[j] = max (f[h*a[i]+q]    +   (p-h)*w[i]) 
f[j] = max (   f[h*a[i]+q]    -   h*w[i]  )          +    p * w[i];

For(i, 1, n) 
	For(q,0,a[i]-1)
		For(p,0,m/a[i])
*/

// 这里的h 是 下方代码中p的一个集合，将代码中p枚举可以形成h



// https://www.cnblogs.com/chinhhh/p/9011428.html

// 最终看懂是在这里：https://www.bilibili.com/video/BV1Bp411f7kZ?from=search&seid=3274599871300742144

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		memset(dp,0,sizeof(dp));
		cin>>V>>n;
		int price,height,cot;
		for(int i = 1; i <= n; ++i){
			//scanf("%d %d %d",&price[i],&height[i],&cot[i]);
			scanf("%d %d %d",&price,&height,&cot);
			for(int q = 0; q < price; ++q){
				deque<int> Q;

				// p 就是按余数分组后得到的新的序号
				for(int p = 0; p * price + q <= V; ++p){
					// 控制不超过容量


					// 就是在枚举j
					// j 

					// val[p] 就是(   f[h*a[i]+q]    -   h*w[i]  )
					val[p] = dp[p * price + q] - p * height;
					while(!Q.empty()&&val[p] >= val[Q.back()]){
						Q.pop_back();
					}
					Q.push_back(p);

					// 区间容量为cot[i] 只会从前面几个转移过来
					// 太多了就失效了
					int k = p - min(p,cot);
					while(!Q.empty()&&Q.front() < k){
						// 控制不能超过每个物品的个数
						Q.pop_front();
					}
					int s = p*price + q;
					dp[s] = max(dp[s],val[Q.front()]+p*height);
				}

			}
		}
		cout<<dp[V]<<endl;
	}
}