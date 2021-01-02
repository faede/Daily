#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int > pt;
typedef long long ll;
const int maxn = 200000 +5;
const int mod = 1e9 + 7;
int a[maxn];
/*
by Nicode  :


对于[1,n] ，每次选择y>=ceil(n/y)的最小的y。这样可以保证对于[y+1,n-1]来说，每个位置都只需要一次操作就可以让
其变为1（a[i]=ceil(i/y)），花两次操作把a[n]变为1。这样对于[y+1,n]来说我们只花了n-y+1次操作，问题规模就缩小到了[1,y]，接着递归就可以了。
至于如何保证这个操作次数小于n+5？我们知道1和2不用动，剩下只有每个段的右边界需要多进行一次操作。所以操作次数是n-2+段数，那会有多少个段呢？
看看y>=ceil(n/y)我们就知道每次选的边界其实就是sqrt(n)或者floor(sqrt(n))+1。所以每次的y的选取就是sqrt(n),sqrt(sqrt(n))这样选下去的，
题目数字最大是200K，开七次平方根早小于2了，所以满足题意



*/
void slove(int n, vector<pt> &ans){
	if(n == 2)
		return ;
	int y  = max(1, (int)sqrt(n) - 1);
	while(y < (n + y - 1) / y){
		y++;
	}
	for(int pos = y + 1; pos < n; pos++){
		//ans.emplace_back(pos, n);
		ans.push_back(make_pair(pos,n));
	}
	ans.push_back(make_pair(n,y));
	ans.push_back(make_pair(n,y));
	slove(y,ans);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		int n ;
		cin >> n;
		std::vector<pt> ans;
		slove(n , ans);
		cout << ans.size() << endl;
		for(int i = 0 ; i <  ans.size(); i++){
			cout << ans[i].first << " " << ans[i].second << endl;
		}
	}

}