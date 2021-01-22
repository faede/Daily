#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int > pii;
typedef long long ll;
const int maxn = 200000 +5;
const int mod = 1e9 + 7;
const int INF = 1e9;
ll fast_pow(ll x, ll p){
    ll ans = 1;
    while(p){
        if(p & 1){
            ans *= x;
            ans %= mod;
        }
        p >>= 1;
        x *= x;
        x %= mod;
    }
    return ans;
}


char a[100000 + 10];
char sum[100000 + 10];
int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        //string a ;
        for(int i = 0; i < n; i++){

            if( i > 0 &&s[i] + 1!= sum[i-1]){
            	//cout << "sum [i-1] :" <<  sum[i-1]  <<endl;
                a[i] = '1';
            }else if(i == 0){
                a[i] = '1';
            }else{
                a[i] = '0';
            }
            sum[i] = a[i] - '0' + s[i];
        }
        for(int i = 0; i < n; i++){
        	cout << a[i];
        }
        
        cout << endl;
        //cout << a << endl;
    }

}










