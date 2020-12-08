#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
const int maxn = 10000;
bool isnp[MAXN];
//让每一个合数被其最小质因数筛到。
// 我们遍历到质数表中的 p ，且发现 p|x 时，就应当停止遍历质数表
// 因为对于任意 p' ,设x = pr p是x的最小质因数
// p'x = p'px = p (p'x) 则p'x的最小质因数不是p'
bool isnp[MAXN];
vector<int> primes; // 质数表
void init(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes)
        {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}
int main(){

}