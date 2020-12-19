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
	freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int n;
	cin>>n;
	for(int i = 0;  i < n; ++i){
		scanf("%d",&a[i]);
	}
	int maxd = 0;
	for(int i = 2; i < n; i++){
		maxd = max(a[i]-a[i-1],maxd);
	}
	if(maxd == 1){
		cout << -1;
	}
	else{
		if(log(maxd)-int(log(maxd)) < 1){
			cout <<int(log(maxd)) + 1<<endl;
		}else{
			cout <<int(log(maxd))<<endl;
		}
	
	

	}





	return 0;
}