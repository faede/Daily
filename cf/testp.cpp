#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n;
int ans;

int a[1100];

bool use[1005];
bool DFS(int stp)
{
    memset(use, 0, sizeof use);
    
    if(stp > ans)
    {
        if(a[ans] == n) return 1;
        else return 0;
    }
    
    for(register int i = stp - 1 ; i >= 1 ; i --)
    {
        for(register int j = i ; j >= 1 ; j --)
        {
            if(a[i] + a[j] > n) continue;
            if(!use[a[i] + a[j]])
            {
                if(a[i] + a[j] <= a[stp - 1]) return 0;
                use[a[i] + a[j]] = 1;
                a[stp] = a[i] + a[j];
                if(DFS(stp + 1)) return 1;
                a[stp] = 0;
                use[a[i] + a[j]] = 0;
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