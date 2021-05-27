#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
bool isprime(int n){
    if(n == 2)
        return true;
    for(int i = 2; i * i <= n; i++ ){
        if(n % i == 0)
            return false;
    }
    return true;

}
int sum(int n){
    int sum = 0;
    while(n){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int main(){

    int k = 1;
    int a, b;
    for(int i = 1000000; k <= 2; i++){
        if(isprime(i) && isprime(sum(i))){
            
            if(k == 1){
                cout <<"sum :" << sum(i) << endl;
                a = i;
                k++;
            }
            else{
                cout <<"sum :" << sum(i) << endl;
                b = i;
                k++;
            }
        }
    }
    cout << a << endl;
    cout << b << endl;
}
