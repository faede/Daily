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


int a[maxn];
int b[maxn];
int c[maxn];

int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n1, n2, n3;
        cin >> n1 >> n2 >> n3;
        for(int i = 1; i <= n1; i++){
            cin >> a[i];
        }
        for(int i = 1; i <= n2; i++){
            cin >> b[i];
        }
        for(int i = 1; i <= n3; i++){
            cin >> c[i];
        }
        
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);
        sort(c + 1, c + 1 + n);
        int i , j , k;
        i = j = k = 1;
        int first =(n1 % 2 + n2 % 2 + n3 % 2) % 2;
        
        
        
    }

}