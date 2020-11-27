#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 1e4 + 5;
vector<int> p[maxn], val[maxn];
int dp[3][maxn], id[maxn];
// 这应该是个树的直径模板题（


// 这题的输入有点奇怪  记得仔细看一下题目 ): 


// dp[0][i] i节点到子树的最大距离额
// id[0][i] i节点到子树最大距离时第一个走的子节点
// dp[1][i] i节点到子树，且不经过达到子树最大距离时走的那个儿子节点
// dp[2][i] i节点的反向最大距离

// 反向最大距离一定会经过父节点
// 想要求反向最大距离可以先到父节点，再从父节点出发
//
// 第二次dfs从父亲到子 子节点的反向最大距离可以由父节点更新过来



//代码：https://blog.csdn.net/qq_34374664/article/details/56669243
void dfs1(int x, int f)  //第一个dfs更新子树的最大跟次大和
{
    for(int i = 0; i < p[x].size(); i++)
    {
        int to = p[x][i];
        if(to == f) continue;
        dfs1(to, x);
        if(dp[0][x] < dp[0][to] + val[x][i]) //这里是更新最大和，记住经过哪个儿子最大
        {
            dp[0][x] = dp[0][to] + val[x][i];
            id[x] = to;
        }
    }
    for(int i = 0; i < p[x].size(); i++)
    {
        int to = p[x][i];
        if(to == f) continue;
        if(id[x] == to) continue;  //跳过这个儿子，再剩下点里面找一个最大的，就是这个点次大的
        dp[1][x] = max(dp[1][x], dp[0][to]+val[x][i]);
    }
}
void dfs2(int x, int f)  //这个是更新先往父亲节点走一步的最大和
{
    for(int i = 0; i < p[x].size(); i++)
    {
        int to = p[x][i];
        if(to == f) continue;
        if(to == id[x])  
        // 难点，每个父亲都有两种方式，一个是再往父亲走一步，一个是走父亲的子树，max(dp[2][x], dp[1][x])，
        // 这个就体现出这两部了，注意经不经过这个点直接走子树最大和的那个点
        {
            dp[2][to] = max(dp[2][x], dp[1][x]) + val[x][i];  
            // 这个是针对儿子，所以是dp[2][to] = ，
            // 体现了先走一步父亲，经过就走次大的，再走最大的就重复了一段
        }
        else
        {
            dp[2][to] = max(dp[2][x], dp[0][x])+val[x][i];
        }
        dfs2(to, x);  
        // 因为dfs1更新了所有子树的特点，子树的信息可以直接用了，父节点的信息从一步步dfs下去都已经更新好了，
        // 上面的也是可以直接用，每一步都看看是不是走父亲的父亲更好，一直更新最优
    }
}
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int a, b;
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++)
        {
            p[i].clear();
            val[i].clear();
        }
        for(int i = 2; i <= n; i++)
        {
            scanf("%d%d", &a, &b);
            p[i].push_back(a);
            val[i].push_back(b);
            p[a].push_back(i);
            val[a].push_back(b);
        }
        dfs1(1, -1);
        dfs2(1, -1);
        for(int i = 1; i <= n; i++)
            printf("%d\n", max(dp[0][i], dp[2][i]));
    }
    return 0;
}