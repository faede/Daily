#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100;
int a [maxn];
int c [maxn];
int l [maxn];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int i  = 0 ; i < n; ++i){
		cin >> a[i];
	}
	memcpy(c,a,sizeof(a));
	sort(c,c+n);
	int len = unique(c,c+n) - c;
	for(int i = 0; i < n; i++){
		l[i] = lower_bound(c,c+len,a[i]) - c + 1;
	}

	for(int i = 0; i < n; i++){
		cout << a[i] << " ";
	}
	cout << endl;
	for(int i = 0; i < n; i++){
		cout << l[i] << " ";
	}
	cout << endl;
}