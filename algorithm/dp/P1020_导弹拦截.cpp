#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
int dp[100000+10],a[100000+10];
int n;
int cmp(int a,int b){return a > b;}
// 代码是之前的,关于这道题有一种更加直观(x)的证明方式
// 运用离散数学的知识我们可以得到:
// 最小的反链划分数等于最长链长度
// 此问题可以规约到上述定理阐明的问题上,两者等价



int main()
{
    
    /*
    2、对于问二求整个数列的最长上升子序列即可。证明如下：

（1）假设打导弹的方法是这样的：取任意一个导弹，从这个导弹开始将能打的导弹全部打完。而这些导弹全部记为为同一组，再在没打下来的导弹中任选一个重复上述步骤，直到打完所有导弹。

（2）假设我们得到了最小划分的K组导弹，从第a(1<=a<=K)组导弹中任取一个导弹，必定可以从a+1组中找到一个导弹的高度比这个导弹高（因为假如找不到，那么它就是比a+1组中任意一个导更高，在打第a组时应该会把a+1组所有导弹一起打下而不是另归为第a+1组），同样从a+1组到a+2组也是如此。那么就可以从前往后在每一组导弹中找一个更高的连起来，连成一条上升子序列，其长度即为K;

（3）设最长上升子序列长度为P，则有K<=P;又因为最长上升子序列中任意两个不在同一组内(否则不满足单调不升)，则有

P>=K，所以K=P。
    */
    while(cin>>a[++n]);n--;
    /*int x;
    while(scanf("%d",&x) ){
        if(x==-1)
            break;

        a[++n] = x;
        //dp[n] = 0xc0c0c0c0;
    }
*/

    /*
    n^2 LIS:

    int maxx = 0xc0c0c0c0;
    for(int i = 1; i <= n; i++){
        dp[i] = 1;
        for(int j = 1; j < i; j++){
            if(a[j] >= a[i] && dp[j] + 1 >dp[i]){
                dp[i] = dp[j]+1;
            }
        }
        maxx = max(maxx , dp[i]);
    }
    cout<< maxx;
    */



    dp[1] = a[1]; 
    int len1 = 1;
    for(int i = 2; i <= n; i++){
        if(a[i] <= dp[len1]){
            dp[++len1] = a[i];
        }
        else{
            *upper_bound(dp+1,dp+1+len1,a[i],cmp) = a[i];
        }
    }

    dp[1] = a[1]; 
    int len2 = 1;
    for(int i = 2; i <= n; i++){
        if(a[i]  > dp[len2]){
            dp[++len2] = a[i];
        }
        else{
            *lower_bound(dp+1,dp+1+len2,a[i]) = a[i];
        }
    }
    cout<<len1<<endl;
    cout<<len2<<endl;
    return 0;
}