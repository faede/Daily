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
int d;
bool check(ll x){
    ll last = 1;
    ll has = 1;
    for(ll i = 2; i <=  x; i++){
        if(x % i == 0){
            if(i - last < d){
                return false;
            }
            has++;
            last = i;
        }
        if(has > 4){
            return true;
        }
    }
    if(has >= 4)
    {
        return true;
    }else{
        return false;
    }
    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        //cout <<"1111:" << endl;
        //int d;
        cin >> d;
        ll x = 3 * d;
        while(!check(x)){
            x++;
        }
        cout << x << endl;
    }

}