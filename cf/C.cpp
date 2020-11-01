#include<iostream>
#include<algorithm>
#include<vector>
#include <cmath>
#include <cstdio>
using namespace std;
const long long mod = 1e9 + 7;
long long fab(long n){
	long long t  = 1;
	long long res = 1;
	for(;t <= n ; ++t){
		res *= t;
		res %=mod;
	}
	return res;
}
int main(){
	int n  = 123;
	int x = 24;
	cout<<( fab(n - log2(x+1)) * fab(log2(x+1)) )%mod;

}