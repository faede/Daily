#include<iostream>
#include<cstring>
using namespace std;
int x[100+5];
int vis[100+5];
int n,deep;
bool dfs(int step){
	if(step > deep){
		if(x[deep] == n)
			return 1;
		return 0;
	}
	for(int i = step - 1; i >= 1; i--)
	{
		for(int j = i; j >= 1; j--){
			if(x[i] + x[j] > n){//优化
				continue;
			}
			if(!vis[x[i]+x[j]]){//优化
				if(x[i] + x[j] <= x[step - 1])//单调
				 	return 0;
				vis[x[i]+x[j]] = 1;
				x[step] = x[i] + x[j];
				if(dfs(step + 1))
					return 1;
				vis[x[i]+x[j]] = 0;
			}
		}
	}
}
int main(){

	while(cin>>n && n != 0){
		if(n == 1)
		{
			cout<<"1"<<endl;
			continue;
		}
		if(n == 2){
			cout<<"1 2"<<endl;
			continue;
		}

		x[1] = 1;
		x[2] = 2;
		for(deep = 3; !dfs(3) ; ++deep){
			memset(vis,0,sizeof(vis));
		}
		for(int i = 1; i <= deep; ++i){
			cout<<x[i]<<" ";
		}
		cout<<endl;
	}

}