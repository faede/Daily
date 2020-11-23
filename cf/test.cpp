#include <iostream>
struct sr{
    int a,b,c;
};
int main(){
    struct sr * p = 0;
    struct sr * q = p;
    p = p + 1;
    long long c = p-q;
    std::cout<<c;
    return 0;
}