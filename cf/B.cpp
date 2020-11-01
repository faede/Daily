#include<iostream>
#include<algorithm>
#include<vector>
#include <cstdio>
using namespace std;
bool isprime(int n){
	if( n == 1)
		return false;
	if(n == 2)
		return true;
	for(int i = 2; i * i <= n;  ++i){
		if(n%i == 0){
			return false;
		}
	}
	return true;
}
int main(){
	int T;
	cin>>T;
	int n;
	for(int t = 0; t < T; ++t){
		cin>>n;

		int k = 1;
		for(; true; ++k){
			if(!isprime(k) && isprime(n-1 + k)){
				break;
			}
		}
		int k2 = 1;
		for(; true; ++k2){
			if(!isprime(k2) && isprime((n-1)*k + k2)){
				break;
			}
		}
		for(int i = 0 ;i < n - 1; ++i){
			for(int j = 0; j < n - 1; ++j){
				cout<<"1 ";
			}
			cout<<k<<endl;
		}
		for(int i =0 ; i< n-1; ++i)
			cout<<k<<" ";
		cout<<k2<<endl;

	}

}

