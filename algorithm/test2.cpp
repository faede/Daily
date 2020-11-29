#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int W,n;
int w[105],v[105],g[105];
int dp[205][20005];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&W,&n);
        
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d",&w[i],&v[i],&g[i]);
        }
        
        for(int i=0;i<n;i++)
            for(int j=0;j<=W;j++)
            {
                dp[i+1][j]=dp[i][j];
                for(int k=1;k<=g[i];k++)
                    if(j>=k*w[i])    dp[i+1][j]=max(dp[i+1][j],dp[i][j-w[i]*k]+v[i]*k);
            }
        printf("%d\n",dp[n][W]);
    }
    return 0;
}