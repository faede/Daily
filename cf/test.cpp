#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 50 +5;
int n ;
int a[1000][1000];
void dfs(int dep,int last, int x,int y){

	if(dep == n +1){
		return ;
	}
	if(dep == n ){
		a[x][y]=1;
	}
	
	if(last == 1){
		if(y+1 <=500 + n)
			dfs(dep+1,-1,x,y+1);
		if(y-1>=500-n)
			dfs(dep+1,-1,x,y-1);
	}else{
		if(x+1<=500 + n)
			dfs(dep+1,1,x+1,y);
		if(x-1>=500-n)
			dfs(dep+1,1,x-1,y);
	}
	
	
}
int check(){
	int tot = 0;
	for(int i = 0 ; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			if(a[i][j] == 1){
				tot++;
			}
		}
	}
	return tot;
}
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);

	//cin >> n;]
	cin >> n;
	
	for(int i = 1; i <= 50 ; i++){
		memset(a,0,sizeof(a));
		n = i;
		dfs(1,-1,500,501);
		dfs(1,-1,500,499);
		dfs(1,1,501,500);
		dfs(1,1,499,500);
		cout << " n:" << n << "  zhongshu:" << check() << endl;
	}
	cout << check();
}