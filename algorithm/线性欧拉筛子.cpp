#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
const int maxn = 10000;
//让每一个合数被其最小质因数筛到。
bool isnp[maxn];
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
            // 要证明p * i 的最小素因数确实是p
            // 假设 p * i 还有最小素因数 p'
            // 那么 p‘一定是i的因数,一定比i小
            // 但遇到第一个i的素因数时就break了
            // 所以p * i 的最小素因数确实是p


            //上面的证明还需要证明 <= i的合数一定会被筛出来(或者素数一定会被筛出来)

            // 下面取自:https://zhuanlan.zhihu.com/p/100051075
            // x = pr是 其中p是x的最小质因数，设r = p'r'
            // 又p‘是r的最小质因数。在处理 r 时，要遍历质数表，直到遇到 p' 时才结束，
            // 所以任意小于等于 p' 的质数与 r 的乘积，都会在此时被筛掉。
            if (i % p == 0)
                break;
        }
    }
}
int main(){
    int n = 50;
    isnp[1] = 1;
    init(n);
    for(int i = 1; i <= n; ++i){
        if(!isnp[i]){
            cout << i <<"是素数"<<endl;
        }else{
            cout << i <<"不是素数"<<endl;
        }
    }
}