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
const int maxn = 200000 +5;

typedef struct seg
{
    int left;
    int right;
    bool operator < (const seg & rhs)const{
        return right < rhs.right;
    }
}seg;
seg a[maxn];
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
            cin >> a[i].left >> a[i].right; 
        }
        sort(a+1,a+1+n);
        int use = a[1].right;
        int num = 1;
        for(int i = 2; i <= n; i++){
            if(a[i].left > use){
                num++;
                use = a[i].right;
            }
        }
        cout << n - num << endl;
        


    }


}