#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
long long getn(long long n){
        if( n < 10)
            return n;
        long long res = 1;
        while(n > 0){
            cout << "res * " << (n % 10) << endl;
            res *= (n % 10);
            n /= 10;
            cout << " n : " << n << endl;
        }
        return res;
    }
    long long mathexp(long long n) {
        // write code here
        long long last = -1;
        long long ne = n ;
        while(last != ne){
            last = ne;
            ne = getn(ne);
            cout << ne << endl;;
        }
        return last;
    }
int main(){
    long long n;
    cin  >> n;
    cout <<mathexp(n);

}