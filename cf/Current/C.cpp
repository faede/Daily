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
const int maxn = 100000 +5;
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
        int n , k;
        cin >> n >> k;
        int m = n - k;
        int temp = k;
        for(int i = k - m ; i <= k; i++){
            a[i] = temp--;
        }
        temp = 1;
        for(int i = 1; i <= k - m - 1; i++){
            a[i] = temp++;
        }
        for(int i = 1; i <= k; i++){
            cout << a[i] << " ";
        }
        cout << endl;
    }

}