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
const int maxn = 300000 +5;
const int mod = 1e9 + 7;
int n;
int a[maxn];
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

bool isf(int i){
    return i - 1 >= 1 && i + 1 <= n && a[i] > a[i-1] && a[i] > a[i+1] || i - 1 >= 1 && i + 1 <= n && a[i] < a[i-1] && a[i] < a[i+1];
}

bool isfeng(int i ){
    return i - 1>= 1 && i + 1<= n && a[i] > a[i-1] && a[i] > a[i+1] ;
}
bool isgu(int i){
    return i - 1>= 1 && i + 1<= n && a[i] < a[i-1] && a[i] < a[i+1] ;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        //int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        ll sum = 0;
        for(int i = 2; i <= n - 1; i ++){
            if(isf(i)){
                sum++;
            }
        }
        #define test ((int)isf(i - 1) + (int)isf(i) + (int)isf(i + 1) )
        //cout <<" sum :" << sum << endl;
        ll ans = sum;
        for(int i = 2; i <= n - 1; i++){
            int cp = a[i];
            int t;

            t = test;
            a[i] = min(a[i-1], a[i + 1]);
            ans = min (ans, sum - (t - test));
            a[i] = cp; 

            t = test;
            a[i] = max(a[i-1], a[i + 1]);
            ans = min (ans, sum - (t - test));
            a[i] = cp;



        }
        
        cout << ans << endl;
    }

}