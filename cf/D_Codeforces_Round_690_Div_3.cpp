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
const int maxn = 3000 +5;
int a[maxn];
int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            a[i] += a[i-1];
        }

        int sum = a[n];
        int res = 1e4;
        for(int i = 1; i <= n; i++){
            int temp = a[i];
            int j = i + 1;
            int left = i;
            bool tag = true;
            int ans = i - 1;
            while(j <= n){
                if(a[j] - a[left] > temp){
                    tag = false;
                    break;
                }
                if(a[j] - a[left] == temp){
                    ans += j - left - 1;
                    
                    left = j;
                }

                j++;
            }
            if(left != n && a[n] - a[left] != temp){
                tag = false;
            }

            if(tag)
                res = min(res, ans);

        }
        cout << res << endl;


    }


}