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
const int maxn = 100000 +5;
int fa[maxn];
int find(int x){
	if(fa[x] != x){
		fa[x] = find(fa[x]);
	}
	return fa[x];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		int n,m;
		cin >> n >> m;
		for(int i = 1; i < maxn; i++){
			fa[i] = i;
		}
		int x,y;
        long long res = 0;
		for (int i = 0; i < m; ++i)
		{
			cin >> x >> y;
			if(x == y)
				continue;
			if(find(x) == find(y)){
				res += 2;
			}else{
				res += 1;
				fa[x] = y;
			}

		}

		cout << res << endl;
	}

}