#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
const int maxn = 10000;
// 思想就是让每一个合数质因数筛到,但是不是最小质因数,所以可能会被重复筛多从。

bool isnp[MAXN]; // is not prime: 不是素数
void init(int n)
{
    for (int i = 2; i * i <= n; i++)
        if (!isnp[i])
            for (int j = i * i; j <= n; j += i)
                isnp[j] = 1;
}
int main(){

}