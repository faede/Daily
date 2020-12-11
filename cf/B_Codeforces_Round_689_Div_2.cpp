#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500+10;
int a[maxn][maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int n,m;
	while(t--){
		cin>>n>>m;
		char c;
		for(int i = 1; i <= n; ++i){
			a[i][0] = 0;
			for(int j = 1; j <= m; ++j){
				//cin>>c;
				scanf(" %c",&c);
				a[i][j] = (c == '*');
				a[i][j] += a[i][j-1];
			}
		}
		int tot = 0;
		for(int x = 1; x <= n; x++){
			for(int y = 1; y <= m; ++y){
				if(a[x][y]-a[x][y-1] == 1)
				for(int k = m; k >= 1 ; k--){
					if( x+k-1>n||y-k<0||y+k-1>m)
            			continue;
					int t = 0;
					for(int i = 1; i <= k; ++i){
						if( a[x+i-1][y+i-1] - a[x+i-1][y - i] == 2*i -1){
							t++;
						}
					}
					if(t == k){
						tot+= k;
						break;
					}
					
				}
			}
		}
		cout<< tot << endl;
	}
	
}