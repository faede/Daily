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
        unordered_map<int ,int >mp ;
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            int t = a[i];
            for(int j = 2; j * j  <= t; j++){
                while(a[i] % (j*j) == 0){
                    a[i] /= (j*j);
                }
            }
            if(mp.find(a[i]) == mp.end()){
                mp.insert(make_pair(a[i], 1));
            }else{
                mp[a[i]]++;
            }
        }


        int mxa = 0;
        int mxb = 0;
        for(auto i : mp){
            mxa = max(mxa , i.second);
            if(i.second % 2 == 0 || i.first == 1){
                mxb += i.second;
            }
        }

        int q;
        cin >> q;
        ll w;
        for(int i = 1; i <= q; i++){
            cin >> w;
            if(w == 0){
                cout << mxa << endl;
            }else{
                cout << max(mxa , mxb) << endl;
            }
        }

    }

}