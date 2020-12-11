#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
const int maxn = 200;
int main(){
	
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int n,k;
	int t;
	cin >> t;
	while(t--){
		scanf("%d %d",&n,&k);
		string s;
		for(int i = 0; i < k ; i++){
			s += "a";
		}

		for(int i = 0; i < n - k ; i++){
			if(i % 3 == 0){
				s += "b";
			}else if(i % 3 == 1)
				s += "c";
			else if(i % 3 == 2)
				s += "a";

		}
		cout << s <<endl;
	}
	


}