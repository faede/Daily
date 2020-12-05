#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
int main(){
    //freopen("/Users/zyy/Documents/GitHub/Daily/algorithm/in.txt","r",stdin);
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    int n,m;
    while(t--){
        std::vector<int> v;
        cin >> n >> m;
        int x;
        for(int i = 0 ; i < n; ++i){
            cin>>x;
            v.push_back(x);
        }
        for(int i = 0 ; i < m; ++i){
            cin>>x;
            v.push_back(x);
        }
        sort(v.begin(),v.end());
        int len = unique(v.begin(),v.end()) - v.begin();
        cout << n + m - len<<endl;
    }
}