#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
const int maxn = 100000+10;
/*
 这道题要先推导结论，令b_i 为 a_i的二进制长度
 那么我们可以得到 ： 
 如果 b_{i-1} = b_i = b_{i+1}
 那么 a_{i-1}  > a_{i}^a_{i+1}
 因为 三个数的长度相同，后两位异或之后新的数字首位变成0，
 那么就是题目要找的数字，
 又因为 2(flor(log_2^{1e9}) + 1) = 60 ，由鸽巢原理：
 当 n > 60 的时候我们可以直接输出答案 1
 
 否则我们可以采取暴力枚举的办法：
 对a[i]数组求前缀异或，前缀异或和前缀和有类似的性质，我们
 利用前缀异或就可以在 O(1) 的时间求出区间异或。

 c_i是某个阶段形成的数组
 c_i = a_l,a_{l+1},...,a_{m};
 c_{i+1} = a_{m+1},a{m+2},...,a_{r}
 c_i > c_{i+1}
 ans = min (ans , r - l - 1);
*/

int a[maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n; 
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin>>a[i];
		a[i] = a[i]^a[i-1];
	}

	if(n > 60){
		cout << 1;
		return 0;
	}
	int ans = 1e9;
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; ++j){
			for(int k = j + 1; k <= n; ++k){
				if(( a[i-1]^a[j]) > (a[j]^a[k])){
					// 异或的运算优先级更低
					ans = min(ans,k - i - 1);
				}
			}
		}
	}
	if(ans == 1e9){
		cout << -1;
	}else{
		cout << ans;
	}

	return 0;
}