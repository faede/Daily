#include<iostream>
using namespace std;
int gcd (int a,int b){
	return b == 0 ? a :  gcd(b , a%b);
}
bool isiprime(int n){
	if(n == 1)
		return false;
	if(n == 2)
		return true;
	for(int i = 2; i*i < n ; ++i){
		if(n%i == 0){
			return false;
		}
	}
	return true;
}

int phi_prime(int a,int b){
	return (a-1)*(b-1);
}

long long fast_exp(long long  a ,long long n, long long  mod){
	long long res = 1;
	while ( n  != 0){
		if(n&1){
			res = (res* a) %mod;
		}
		n = (n>>1);
		a = (a*a)%mod;
	}
	return res;
}
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    long long r=exgcd(b,a%b,x,y);
    long long t=x;
    x=y;
    y=t-a/b*y;
    return r;
}

long long add_great(long long x, long long n){
	while(x < 0){
		 x += n;
	}
	return x;
}
int main(){
	long long  p,q;
	for(p  = 10000 ; ;p++){
		if(isiprime(p))
			break;
	}
	for(q  = p+5 ; ;q++){
		if(isiprime(q))
			break;
	}
	cout<<"p :" <<p <<"q : "<<q <<endl;
	long long phi = phi_prime(p,q);
	long long n = p*q;
	long long  e = 1000;
	for(;;++e ){
		if( gcd(e,phi) == 1)
			break;
	}
	long long d,y;
	exgcd(e , phi ,d,y);
	d = add_great(d,phi);
	cout<<"phi:"<<phi<<endl;
	cout<<"d :" <<d <<endl;
	long long input;
	cout<<"please input a number:"<<endl;
	cin>>input;
	long long cop = fast_exp(input,e,n);
	printf("加密前的明文为%d\n",input );
	printf("加密之后的明文为%d\n",cop);
	cout<<"d *e %:"<<(d*e)%phi <<endl;
	long long de_cop = fast_exp(cop,d,n);
	printf("解密后的明文为%d\n",de_cop);


}