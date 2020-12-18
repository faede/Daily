#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	int a,b,c;
	while(t--){
		cin >> a>> b>> c;
		if((a + b + c )%9 !=0 ){
			cout << "NO"<<endl;
			continue;
		}
		int m = 1e9;
		m = min(m,a);
		m = min(m,b);
		m = min(m,c);
		if(m < (a + b + c )/9){
			cout << "NO"<<endl;
		}else{
			cout << "YES"<<endl;
		}
	}
	
}