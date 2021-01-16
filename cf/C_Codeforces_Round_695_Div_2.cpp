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
/*

After looked solution ,we can find that answer is (sum of even number) - (sum of odd number),
we want minmize sum of odd number, so we just construct three layer construct , and put two
min number on the odd layer, or just two layer.



https://codeforces.com/blog/entry/86566
by ScrappyDoo :



I'll suppose that the part about vertices and edges is clear. Suppose that we draw a rooted tree for the following example:

2 3 4

1 2
3 4 5
6 7 8 9
Notice that a-(b-c) is actually equal to a-b+c. This corresponds to the following graph example:

a
|
c
|
b
First we remove b, and change c for b-c, then we get the following tree:

a
|
(b-c)
Then we remove (b-c) and change a for a-(b-c) leading to:

a-b+c
This implies that we will be calculating our final answer as difference of sums of elements on even levels and sums on odd levels.

Because nodes can connect only elements from different sets we observe that we can create a tree with at least 3 levels, which turns out to be just enough to get all the nodes in a tree. Here's an example of such tree using the previously mentioned sets:

         1
     /       \
    3         6
 / / \ \     / \
2  7  8 9   4   5
What do we see? We can include just two elements from two different sets on our odd levels and all other elements on even levels. So if mn1 and mn2 are the two smallest values that don't belong to the same set (one belongs to 1. and other to 2., one belongs to 2. and other to 3., or one belongs to 1. and other to 3. set) the answer in this case is:

sum of all elements - 2 * (mn1 + mn2)
As we already counted mn1 and mn2 in total sum we have to remove them twice. There's another case where we'll store one complete set on the second level and two other sets on level 1 and level 3 (I'll leave it as an exercise for you). Again we take the minimum of those three cases and compare them to our answer.

I hope this explanation was clear. TBH I'm not too good at doing these, so feel free to ask about any part of my solution.

Here's a sample implementation I've done for you to understand completely:

https://codeforces.com/contest/1467/submission/103829704


*/

int a[maxn];
int b[maxn];
int c[maxn];

ll cac(int * a0 , int * a1, int * a2, int n1, int n2, int n3){
    ll ans = 0, m1 = a1[1], m2 = a2[1], s1 = 0, s2 = 0;
    for(int i = 1; i <= n1; i++){
        ans += a0[i];
    }
    for(int i = 2; i <= n2; i++){
        s1 += a1[i];
    }
    for(int i = 2; i <= n3; i++){
        s2 += a2[i];
    }
    //cout <<"s1 :" << s1 << "  s2:" << s2 << " ans:" << ans << endl;
    ans += max({(s2 + s1) - (m1 + m2) , (m2 + s2) - (m1 + s1), (m1 + s1) - (m2 + s2)});
    return ans;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/zyy/Documents/GitHub/Daily/cf/in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);   cin.tie(NULL);   cout.tie(NULL);
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    for(int i = 1; i <= n1; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n2; i++){
        cin >> b[i];
    }
    for(int i = 1; i <= n3; i++){
        cin >> c[i];
    }

    sort(a + 1, a + 1 + n1);
    sort(b + 1, b + 1 + n2);
    sort(c + 1, c + 1 + n3);
    ll ans = -1e18;
    ans = max(ans, cac(a,b,c,n1,n2,n3));
    ans = max(ans, cac(b,a,c,n2,n1,n3));
    ans = max(ans, cac(c,b,a,n3,n2,n1));
    cout << ans ;

}