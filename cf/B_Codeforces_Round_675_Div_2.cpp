#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 100 + 10;
typedef long long ll;
int a[maxn][maxn];
int n,m;
ll ans;
void add(std::vector<int> & v){
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++){
		ans += abs(v[i] - v[v.size()/2]);
	}
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		ans = 0;
		cin >> n >> m;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				cin >> a[i][j];
			}
		}
		for(int i = 1; i <= n/2; i++){
			for(int j = 1; j <= m/2; j++){
				std::vector<int> v;
				v.push_back(a[i][j]);
				v.push_back(a[n - i + 1][j]);
				v.push_back(a[n - i + 1][m - j + 1]);
				v.push_back(a[i][m - j + 1]);
				add(v);
			}
		}
		if(n%2){
			for(int j = 1; j <= m/2; j++){
				std::vector<int> v;
				v.push_back(a[n/2+1][j]);
				v.push_back(a[n/2+1][m - j + 1]);
				add(v);
			}
		}
		if(m%2){
			for(int i = 1; i <= n/2; i++){
				std::vector<int> v;
				v.push_back(a[i][m/2+1]);
				v.push_back(a[n - i + 1][m/2+1]);
				add(v);
			}
		}
		cout << ans <<endl;
	}
}		