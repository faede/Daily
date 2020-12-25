#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 100000 +5;

int main(){
	//freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
	int t;
	cin >> t;
	while(t--){
		int n,m;
		cin >> n >> m;
		set<int > s;
        //set<int > s2;
		int x,y;
        long long res = 0;
		for (int i = 0; i < m; ++i)
		{
			cin >> x >> y;
			//if(y > x){
			//	swap(x,y);
			//}
			if( ( s.count(y))){
			    //cout <<  "+2 x :" << x << " y :" << y << endl;
			    if(x != y)
					res += 2;
			}else{
			    if(x != y){
                   //cout << "1  x :" << x << " y :" << y << endl;
			        res += 1;
			    }
                s.insert(x);
			}

		}

		cout << res << endl;
	}

}