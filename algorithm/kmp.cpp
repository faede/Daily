#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 100;
int next_array[maxn];
int f[maxn];
//char a[maxn];
string a;
string b;
int n;
void get_next(){
	next_array[1] = 0;
	for(int i = 2, j = 0; i <= n; ++i){
		while(j > 0 && a[i] != a[j+1]){
			j = next_array[j];
		}
		if(a[i] == a[j+1]){
			++j;
		}
		next_array[i] = j;
	}


	for(int i = 0; i <= n; ++i){
		cout<< next_array[i] <<" ";
	}
	cout<<endl;
}
void get_next_zero(){
	next_array[0] = -1;
	for(int i = 0, j = -1; i < n; ++i){
		if(j == -1 || a[i] == a[j]){
			i++;
			j++;
			next_array[i] = j;
		}else{
			j = next_array[i];
		}
	}


	for(int i = 0; i < n; ++i){
		cout<< next_array[i] <<" ";
	}
	cout<<endl;
}
void get_f(){
	for(int i = 1 ,j = 0; i <= n; ++i){
		while(j > 0 && b[i] != a[j+1]){
			j = next_array[j];
		}
		if(b[i] == a[j+1]){
			++j;
		}
		f[i] = j;
		// f[i] == n 就是出现
	}

	for(int i = 0; i <= n; ++i){
		cout<< f[i] <<" ";
	}
	cout<<endl;

}

int get_f_zero(){
	int i = 0 ,j = 0;
	while(i < b.length() && j < a.length()){
		if( j == -1 || b[i] == a[j]){
			i++;
			j++;
		}
		else{
			j = next_array[j];
		}
		f[i] = j;
	}

	if(j >= a.length())
		return i - a.length();
	return -1;

}




int main(){
	//cin>>a;
	a = "0abababaac";
	n = a.length()-1;
	get_next();
	a = "abababaac";
	get_next_zero();
}