#include<iostream>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int r=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-a/b*y;
    return r;
}
bool linear_equation(int a,int b,int c,int &x,int &y)
{
    int d=exgcd(a,b,x,y);
    if(c%d)
        return false;
    int k=c/d;
    x*=k; y*=k;    //求得的只是其中一组解
    return true;
}
int main(){
	int a = 60;
	int b = 7;
	int x,y;
	exgcd(a,b,x,y);

	cout<<"x: "<<x<<"y: "<<y;
}