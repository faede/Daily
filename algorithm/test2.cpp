#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <cstring>
using namespace std;
int a[200000+10];
int main(){
    freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    int n,x;

    while(t--){
        long long tot = 0;
        cin >> n;
        int change = 0;
        int to = 0;
        int cha = -1;
        int pos = 1;
        long long res = 1e9;
        for(int i = 0; i < n; ++i){
            cin >> a[i];
        }
        for(int j = 0; j < n; j++){
            if(j == 0){
                to = a[1];
                a[0] = a[1];
                change = a[1] - a[0];
            }
            else{
                to = a[0];
                a[j] = a[j-1];
                change = 0;
            }

            tot = abs(a[0] - to);
            for(int i = 1 ; i < n; ++i){ 
                tot += abs(a[i] + change - to); 
                change += a[i-1] - a[i] ;
            
            }  
            res = min(res,tot); 
        }
        cout << res<<endl;;
        
    }
}