#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
const int maxn = 600000+10;
int n,m;
int a[maxn];
int dp[maxn];
// 题目:
// https://nanti.jisuanke.com/t/A2229

/*
 经典最大值最小值,二分check
 不会check((
 https://blog.csdn.net/qq_41289920/article/details/87032762

 我们将开心值排序 

 对于前i个人
 i =  [0,m-1]
 i < m 时,显然可以每个人单独一组

 i >= m 时,
 对于第i个元素来说,它一定能加进某个堆,否则后面的人都加不进去了
 因为维护的是最大的差值,不管放到哪一组,后面的人一定会产生更大的差值

 当 i 能插入堆时,我们要判断的是它能不能插入最难插入的一组,也就是
 没到m ,并且 组中最小元素 最小的那一个组

 于是:
 我们用dp[i]代表：对前i个人进行划分，最后一个可以进行分组的（可以被塞进某个分组的）人的编号
 dp[0~m-1]=0
 
 考虑最后一个人，判断当前第i个人能不能作为当前分组的最后一个人，
 由于i 新加了进来, 可能会挤出某个人出之前的分组,我们要看的就是到底会不会有这个人,

 而这个人至少是 ,刨除最近新组的m个人,之后的第一个人,
 也就是之前 i-m个人形成的分组的最后一个人 之后的一个人,也就是被i破坏的分组的第一个人分,最小的

 即dp[i-m]+1。
 
 //  
 我们要判断的就是和它的距离是不是小于x,如果小于,i 就可以作为前i个分组的最后一个人分进上一组,dp[i]=i,

 否则dp[i-1]。
*/


bool check(int x) {
	// dp[0~m-1]=0
	for (int i = m; i <= n; i++) {
		if (a[i] - a[dp[i - m] + 1] <= x) 
			dp[i] = i;
		else dp[i] = dp[i - 1];
	}
	return dp[n] == n;
}
int main(){
    //freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    cin>>n>>m;
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	int l = 0, r = 1e9;
	int mid = (l + r) >> 1;
	while (l < r) {
		mid = (l + r) >> 1;
		if (check(mid)){
			r = mid;
		}
		else{
			l = mid + 1;
		}
	}
	printf("%d\n", l);
	return 0;
}