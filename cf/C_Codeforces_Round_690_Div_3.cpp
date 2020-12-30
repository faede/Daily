#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
typedef long long ll;
using namespace std;
const int maxn = 300 +5;

int sum;
int a[10];

void gete(int t){
    memset(a,0,sizeof(a));
    for(int i = 9; i >= 1; i--){
        if(t >= i){
            a[i] = 1;
            t -= i;
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    //freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int x;
        //memset(a,0,sizeof(a));
        cin >> x;
        if(x > 45)
        {
            cout << -1 << endl;
            continue;
        }
        gete(x);
        char dig[10];
        int k = 0;
        for(int i = 1; i <= 9; i++){
            if(a[i]){
                dig[k++] = '0' + i;
            }
        }
        dig[k] = '\0';
        printf("%s\n", dig);

    }


}