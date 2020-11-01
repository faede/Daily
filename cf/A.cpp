#include<iostream>
#include<algorithm>
#include<vector>
#include <cstdio>
using namespace std;
int main(){

	int t;
	cin>>t;
	long sum,n,m,temp;

	for(int i = 0; i < t; i ++){
		scanf("%d %d",&n,&m);
		sum = 0;
		for(int j = 0; j < n; j++){
			scanf("%d",&temp);
			sum+=temp;
		}
		if(sum == m){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}

	return 0;
}