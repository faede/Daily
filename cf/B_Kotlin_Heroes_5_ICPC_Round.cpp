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
		string s;
		cin >> s;
		int len = 0;
		int tot = 0;
		for(int i = 0; i < s.length(); i++){

			
			if(i == 0 || s[i] == s[i-1]){
				len++;
				if(i == s.length() - 1){
					if(s[i] == 'w'){
						tot += len ;

					}else{
						tot += len / 2;
					}
				}
			}else{
				if(s[i] == 'w'){
					tot += len/2;
				}else{
					tot += len;
				}

				len = 1;
			}
		}
		cout << tot << endl;
	}
	
}