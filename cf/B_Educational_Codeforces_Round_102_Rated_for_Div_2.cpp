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


bool div(string &x , string &d){
    if(x.length() < d.length() || x.length() % d.length() != 0)
        return false;
    int len = d.length();
    for(int i = 0; i < x.length(); i++){
        if(x[i] != d[i%len])
            return false;
    }
    return true;
}

int gcd(int a, int b){
    return b == 0 ? a : gcd(b , a%b);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        string a;
        string b;
        cin >> a >> b;
        int len = min(a.length(), b.length());
        if(div(a,b)){
            cout << a << endl;
        }else if(div(b,a)){
            cout << b << endl;
        }else {
            int len1 = a.length();
            int len2 = b.length();
            bool fid = false;
            for(int i = 1; i <= len; i++){
                if(fid)
                    break;
                string d = a.substr(0,i);
                if(div(a,d) && div(b,d)){
                    int x = len1/ d.length();
                    int y = len2/ d.length();
                    int k = x * y / gcd(x,y);
                    for(int i = 1; i <= k; i++){
                        cout << d;
                    }
                    cout << endl;
                    fid = true;
                }

            }
            if(!fid){
                cout << -1 << endl;
            }

        }

    }

}