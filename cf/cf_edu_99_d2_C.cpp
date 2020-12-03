#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	int x,y;
	cin >> t;
	while(t--){
		cin >> x>>y;
		if(x == y){
			cout <<x-1<<" "<<y<<endl;
		}else if(x > y){
			cout<< x - 1 << " "<<y<<endl; 
		}else{
			cout<< x - 1 <<" "<< y<<endl;
		}
	}




	return 0;
}