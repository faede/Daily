#include <cstdio>
#include <iostream>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;
const int maxn = 100+5;
int n,m;
int price[maxn];
int height[maxn];
int cot[maxn];
//int dp[maxn][maxn];
int dp[maxn];
int que[maxn];
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

f[j] = max (f[(p-k)*a[i]+q]+k*w[i])


k ∈ [0,min(p,c[i])]
h = p - k ;
h ∈ [p-min(p,c[i]),p]

f[j] = max (f[h*a[i]+q]+(p-h)*w[i]) 
f[j] = max (f[h*a[i]+q]-h*w[i]) + p * w[i];

For(i, 1, n) 
	For(q,0,a[i]-1)
		For(p,0,m/a[i])
*/


//https://leetcode-cn.com/circle/article/V5qkAa/
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		memset(dp,0,sizeof(dp));
		cin>>n>>m;
		for(int i = 1; i <= m; ++i){
			scanf("%d %d %d",&price[i],&height[i],&cot[i]);
		}

		for(int i = 1; i <= m; ++i){
			for(int r = 0; r < price[i]; ++r){
				int head = 0;
				int tail = -1;
				for(int k = 0; r + k * price[i] < n;k++){
					if(head <= tail && k - que[head] > cot[i])
						head++;
					while(head <= tail && dp[r + k * price[i]] - k * height[i] >= dp[r + que[tail]*price[i]]-que[tail]*height[i]){
						tail--;
					}
					que[++tail] = k;
					dp[r + k + price[i]] = dp[r + que[head]*price[i]] - que[head]*height[i] + k * height[i];

				}

			}
		}
		//for(int i = 1; i <=m; i++){
		//	for(int j = 1; j <= n; j++){
		//		cout<< dp[i][j]<<" ";
		//	}
		//	cout<<endl;
		//}
		cout<<dp[n]<<endl;
	}
}