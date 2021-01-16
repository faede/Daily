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
int a[maxn];
int suf[maxn];
int pre[maxn];
int mnpre[maxn];
int mxpre[maxn];
int mnsuf[maxn];
int mxsuf[maxn];
char s[maxn];
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
        int n, q;
        cin >> n >> q;
        a[0] = 0;
        //string s;
        cin >> s + 1;

        int tot = 0;
        pre[0] = suf[0] = mnpre[0] = mxpre[0] = mnsuf[0] = mxsuf[0] = 0;
        pre[n+1] = suf[n+1] = mnpre[n+1] = mxpre[n+1] = mnsuf[n+1] = mxsuf[n+1] = 0;
        for(int i = 1; i <= n; i++){
            pre[i] = pre[i-1] + (s[i] == '+' ? 1 : -1);
            mnpre[i] = min(mnpre[i-1],pre[i]);
            mxpre[i] = max(mxpre[i-1],pre[i]);
        }

        for(int i = n; i >= 1; i--){
            suf[i] = suf[i+1] + (s[i] == '-' ? 1 : -1);
            mnsuf[i] = min(mnsuf[i+1], suf[i]);
            mxsuf[i] = max(mxsuf[i+1], suf[i]);
        }
        
        //cin >> q;
        while(q--){
            int l , r;
            cin >> l >> r;
            int mn = mnpre [l-1], mx = mxpre[l-1];
            mn = min(mn , pre[l-1] + mnsuf[r+1] - suf[r+1]);
            mx = max(mx , pre[l-1] + mxsuf[r+1] - suf[r+1]);
            cout << mx - mn + 1 << endl;
        }

    }

}