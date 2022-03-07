#include <iostream>
#include <algorithm>
#include <stack>
using namespace  std;


/* https://codeforces.com/problemset/problem/817/D
 * 序列最大差：最大值-最小值
 * 子串 连续
 * 求序列所有子串最大差之和
 * n 5e5
 * ai 1e8
 */

/*
sum max - sum min

for min
sum num * i (i is min)

*/
#define ll long long
int a[1000000+10];
int minl[1000000+10];
int minr[1000000+10];
int maxl[1000000+10];
int maxr[1000000+10];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    // 要找左边第一个（贴近i）小于ai的数子
    // 对 i+1 来说， 比a[i] 还大的数字没用，因为a[i]都不是，那a[i+1]更不是
    // 维护一个单调递增栈
    // 只取一个 = 防止重复
    stack<int> increase;
    for(int i = 1; i <= n; i++){
        while(!increase.empty() && a[i] < a[increase.top()]){
            increase.pop();
        }
        if(!increase.empty()){
            minl[i] = increase.top();
        }
        else{
            minl[i] = 0; // omit
        }
        increase.push(i);
    }
    stack<int> increase2;
    for(int i = n; i >= 1; i--){
        while(!increase2.empty() && a[i] <= a[increase2.top()]){
            increase2.pop();
        }
        if(!increase2.empty()){
            minr[i] = increase2.top();
        }
        else{
            minr[i] = n+1;
        }
        increase2.push(i);
    }
    stack<int> decrease;
    for(int i = 1; i <= n; i++){
        while(!decrease.empty() && a[i] > a[decrease.top()]){
            decrease.pop();
        }
        if(!decrease.empty()){
            maxl[i] = decrease.top();
        }
        else{
            maxl[i] = 0; // omit
        }
        decrease.push(i);
    }
    stack<int> decrease2;
    for(int i = n; i >= 1; i--){
        while(!decrease2.empty() && a[i] >= a[decrease2.top()]){
            decrease2.pop();
        }
        if(!decrease2.empty()){
            maxr[i] = decrease2.top();
        }
        else{
            maxr[i] = n+1;
        }
        decrease2.push(i);
    }

    ll sum = 0;
    for(int i = 1; i <= n; i++){
        ll l = i - maxl[i];
        ll r = maxr[i] - i;
        sum += a[i] * (l * r-1);
    }
    for(int i = 1; i <= n; i++){
        ll l = i - minl[i] ;
        ll r = minr[i] - i;
        sum -= a[i] * (l * r-1);
    }

    /*for (int i = 1; i <= n; i ++){
        cout << minl[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i ++){
        cout << minr[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i ++){
        cout << maxl[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i ++){
        cout << maxr[i] << " ";
    }
    cout << endl;
    */
    cout << sum;
    return 0;
}