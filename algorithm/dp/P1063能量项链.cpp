#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 100 + 10;
struct interval
{
    int l , r;
}a[2*maxn];
int dp[2*maxn][2*maxn];
int main(int argc, char const *argv[])
{
    //freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        scanf("%d", & a[i].l);
    }
    for(int i = 1; i <= n; ++i){
        a[i].r = a[i+1].l;
    }

    a[n].r = a[1].l;
    a[1].l = a[n].r;
    for(int i = n + 1; i <= 2*n; i++){
        a[i] = a[i - n];
    }


    for(int len = 2; len <= n; ++len){
        //for(int i = 1; i + len - 1 <= 2*n; ++i){
        for(int i = 1; i <= 2*n; ++i){ // 注意这里是2n 不是n,要枚举所有区间
            int j = i + len - 1;
            if(j > 2*n)
                break;
            for(int k = i; k <= j - 1; k++){
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + a[i].l * a[k].r * a[j].r);
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= n; ++i){
        res = max(res , dp[i][i+n-1]);
    }
    cout << res;
    return 0;
}