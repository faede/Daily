#include <iostream>
using namespace std;
const int maxn = 100;
int a[maxn];
int t[maxn];
long long cnt;
void nxd(int l,int r){
	int i,j,temp;
	if(r > l){
		int mid = (l + r)/2;
		nxd(l,mid);
		nxd(mid + 1,r);
		temp = 1;
		for( i = l ,j = mid + 1; i <= mid && j <= r;){
			if(a[i]>a[j]){
				t[temp++] = a[j++];
				cnt += mid - i + 1;
			}else{
				t[temp++] = a[i++];
			}
		}
		for(; i <= mid;)
			t[temp++] = a[i++];
		for(; j <= r;)
			t[temp++] = a[j++];
		for(i = l; i <= r; i++){
			a[i] = t[i];
		}
	}
}
int main(){
	int n,t;
    while(scanf("%d",&n) !=EOF){
        cnt=0;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        nxd(0,n-1);
        cout<<cnt<<endl;
    }
    return 0;
}