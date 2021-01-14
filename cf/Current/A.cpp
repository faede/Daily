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
const int maxn = 100 +5;
const int mod = 1e9 + 7;
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




int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n , d;
        cin >> n >> d;
        bool hasg = false;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] > d){
                hasg = true;
            }
        }
        bool hasl = false;
        for(int i = 1; i <= n; i++){
            for(int j = i + 1; j <= n; j++){
                if(a[i] + a[j] <= d){
                    hasl = true;
                }
            }
        }
        if(hasg){
            if(hasl){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }else{
            cout << "YES" << endl;
        }


    }

}