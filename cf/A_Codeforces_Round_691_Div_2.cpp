#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 50 +5;
int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		string s1;
		string s2;
		int n;
		cin >>n;
		cin >> s1 >> s2;
		int red = 0;
		int blue = 0;
		for(int i = 0; i < n; i++){
			if(s1[i] > s2[i])
			{
				red++ ;
			}
			if(s1[i] < s2[i]){
				blue++;
			}
		}
		if(red > blue)
		{
			cout << "RED" << endl;
		}else if(red == blue){
			cout << "EQUAL" << endl;
		}else{
			cout << "BLUE"<<endl;
		}
	}
	
}