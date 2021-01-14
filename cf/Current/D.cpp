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
int MIN[maxn][50];
int MAX[maxn][50];

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
        int n, m;
        cin >> n >> m;
        a[0] = 0;
        getchar();
        char c;

        int tot = 0;
        for(int i = 1; i <= n; i++){
            c = getchar();
            if(c == '+'){
                a[i] = a[i-1] + 1;
            }else{
                a[i] = a[i-1] - 1;
            }
            tot = max(tot , a[i]);
        }

        for(int i=1;i<=n;i++)
        {
            MAX[i][0]=a[i];
            MIN[i][0]=a[i];
        }
        for( int j=1;j<=(log(n)/log(2));j++)
        {
            for(int i=1;i<=n-pow(2,j)+1;i++)
            {
                MAX[i][j]=max(MAX[i][j-1],MAX[i+(int)pow(2,j-1)][j-1]);
                MIN[i][j]=min(MIN[i][j-1],MIN[i+(int)pow(2,j-1)][j-1]);
            }
        }
        int l , r;
        for(int i = 1; i <= m; i++){
            cin >> l >> r;
            int k,e,f;
            k=(int)(log(n-m+1)/log(2));
            e=max(MAX[m][k],MAX[n-(int)pow(2,k)+1][k]);
            f=min(MIN[m][k],MIN[n-(int)pow(2,k)+1][k]);
            cout << tot + 1 - (e - f + 1) << endl;
        }

    }

}