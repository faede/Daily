#include<iostream>
using namespace std;
int gcd(int a,int b){
	if(b==0)
		return a;
	else {
		cout << a << " =  "<<b <<" * " <<a/b <<" + "<<a%b<<endl;
		int t =  gcd(b,a%b);
		
		return t;
		//cout << t<<endl;
	}
	//return b == 0 ? a : gcd(b,a%b);
}
int main(){
	cout<<gcd(669081,693270);
	cout<<endl; 
	cout<<120%7
	;
}