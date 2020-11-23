#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n;
int ans;

int a[1100];

bool vis[1005];
bool DFS(int step){
    memset(vis,0,sizeof(vis));
    if(step > ans){
        if(a[ans] == n)
            return 1;
        return 0;
    }
    for(int i = step - 1; i >= 1; i--)
    {
        for(int j = i; j >= 1; j--){
            if(a[i] + a[j] > n){
                continue;
            }
            if(!vis[a[i]+a[j]]){
                if(a[i] + a[j] <= a[step - 1]) return 0;
                vis[a[i]+a[j]] = 1;
                a[step] = a[i] + a[j];
                if(DFS(step + 1))
                    return 1;
                vis[a[i]+a[j]] = 0;
                a[step] = 0;
            }
        }
    }
}

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0) return 0;
        if(n == 1)
        {
            printf("1\n");
            continue;
        }
        if(n == 2)
        {
            printf("1 2\n");
            continue;
        }
        a[1] = 1;a[2] = 2;
        for(ans = 3 ; !DFS(3) ; ans ++);
        for(register int i = 1 ; i <= ans ; i ++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        memset(a, 0, sizeof a);
    }
    return 0;
}