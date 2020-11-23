#include <iostream>
using namespace std;
int a[20];
void chai(int n,int pos,int temp_sum,int last){
	if(temp_sum == n){
		cout<<n<<"=";
		cout<<a[1];
		for(int i = 2; i < pos ; ++i){
			cout<<"+"<<a[i];
		}
		cout<<endl;
		return;
	}
	for(int i = last; i != n && i <= n - temp_sum ; ++i){
		a[pos] = i;
		chai(n,pos+1,temp_sum + i,i);
	}

}
int main(){
	int n;
	cin>>n;
	chai(n,1,0,1);
}
