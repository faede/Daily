#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
 
using namespace std;
 
int a[100000+10];
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin>>t;
	while(t--){
		int n , k ;
		cin >> n>>k;
		int last = -1;
		int pos;
		int re;
		int longest = 0;
		int last_mod = -1;
		for(int i = 0; i < n; ++i){
			scanf("%d",&a[i]);
			
		}
 
		int times = 1e9;
		for(int pos = 1; pos <= 100; ++pos){
			int t = 0;
		
			for(int i = 0 ; i < n;  ){
				if(a[i] != pos){
				i+= k;
				t++;
				}
				else{
					++i;
				}
		}
 
		times = min(times,t);
 
		}
		//cout<< pos<<endl;
		cout <<times<<endl;
 
		//Bcout << times<<endl;;
 
	}
 
 
 
 
 
 
 
	return 0;
}