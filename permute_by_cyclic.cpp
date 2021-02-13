#include<iostream>
#include<random>
#include<chrono>

// a[i] 放在位置j的概率是1/n,就是均匀随机排列是错误的， 如下反例：
using namespace std;
int * PERMUTE_BY_CYCLIC(int A[],int len){
    int n = len;
    int * B = new int[n];

    // seed from the system clock
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 engine(seed);
    uniform_int_distribution<int> dist(1, n);
    int offset = dist(engine);
    cout << "chose offset : "<< offset << endl;
    for(int i = 0; i < n; i++){
        int dest = i + offset;
        if(dest > n - 1){
            dest -= n;
        }
        B[dest] = A[i];
        
    }
    return B;
}

// 比较简单的随机排：
void  RANDOMIZE_PLACE(int A[], int len){
    // seed from the system clock
    int n = len;
    for(int i = 0; i < n; i++){
        int rd = rand()%(n - i) + i;
        swap(A[i],A[rd]);
    }

}
void print(int *a ,int len){
    for(int i = 0 ; i < len; i++){
        cout << a[i] << " " ;
    }
    cout << endl;
}
int main(){
    int a[] = {1, 2 ,3 ,2 , 1, 6, 1};
    int n = 7;
    cout <<"n: " << n << endl;
    print(a,n);
    int * b = PERMUTE_BY_CYCLIC(a,n);
    print(b, n);
    cout <<"shuffle : " << endl;
    RANDOMIZE_PLACE(a,n);
    print(a, n);
}
