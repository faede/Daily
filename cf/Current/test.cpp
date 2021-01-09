#include<iostream>
#include<cstring>
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
struct Point{
    int x,y;
    Point(int x,int y):x(x),y(y){};
};
struct Seg{
    int _L,_R;
    Seg():_L(0x3f3f3f3f),_R(0){};
};
queue<Point> SeQ;
Seg Li[505];
int a[505][505];
int v[505][505];
int dp[505];
int main(){
    //_in.open("D:\\workspace\\homeworks\\testdata.in");
    memset(a,0x7f,sizeof(a));
    memset(dp,0x7f,sizeof(dp));
    memset(v,-1,sizeof(v));
    int m,n;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m;i++){
        SeQ.push(Point(1,i));
        v[1][i]=i;
        while(!SeQ.empty()){
            Point Tmp=SeQ.front();
            SeQ.pop();
            if(Tmp.x==n){
                Li[i]._L=min(Li[i]._L,Tmp.y);
                Li[i]._R=max(Li[i]._R,Tmp.y);
            }
            if(v[Tmp.x+1][Tmp.y]!=i&&a[Tmp.x][Tmp.y]>a[Tmp.x+1][Tmp.y]){
                SeQ.push(Point(Tmp.x+1,Tmp.y));
                v[Tmp.x+1][Tmp.y]=i;
            }
            if(v[Tmp.x-1][Tmp.y]!=i&&a[Tmp.x][Tmp.y]>a[Tmp.x-1][Tmp.y]){
                SeQ.push(Point(Tmp.x-1,Tmp.y));
                v[Tmp.x-1][Tmp.y]=i;
            }
            if(v[Tmp.x][Tmp.y+1]!=i&&a[Tmp.x][Tmp.y]>a[Tmp.x][Tmp.y+1]){
                SeQ.push(Point(Tmp.x,Tmp.y+1));
                v[Tmp.x][Tmp.y+1]=i;
            }
            if(v[Tmp.x][Tmp.y-1]!=i&&a[Tmp.x][Tmp.y]>a[Tmp.x][Tmp.y-1]){
                SeQ.push(Point(Tmp.x,Tmp.y-1));
                v[Tmp.x][Tmp.y-1]=i;
            }
            //cout<<v[SeQ.front().x][SeQ.front().y]<<" ";
        }
        //cout<<"!"<<i<<endl;
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(v[n][i]==-1) cnt++;
    }
    if(cnt==0){
        dp[1]=1;
        dp[0]=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=Li[i]._R;j++){
                dp[j]=min(dp[j],dp[Li[i]._L-1]+1);
            }
        }
        printf("1\n%d",dp[m]);
    }
    else{
        printf("0\n%d",cnt);
    }
    return 0;
}