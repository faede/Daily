#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 100 + 10;
typedef long long ll;
int a[maxn];
int b[maxn];
int n;

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		for(int i = 1; i <= n; i++){
			cin >> b[i];
		}
		std::vector<int> v;
		for(int i = 1; i <= n; i++){
			if(!b[i]){
				v.push_back(a[i]);
			}
		}
		sort(v.begin(), v.end(),greater<int>());

		int left = 0;
		int i;
		for(i = 1; i <= n; i++){
			if(!b[i]){
				cout << v[left++] << " ";
			}else{
				cout << a[i] << " ";
			}
		}
		cout << endl;
		//cout << "ans :"<< res << endl;
	}
}		