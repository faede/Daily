#include<iostream>
using namespace std;
int PARTITION(int *,int, int);
void QUICKSORT(int *A, int p, int r){
    if(p < r){
        int q = PARTITION(A, p, r);
        QUICKSORT(A, p, q - 1);
        QUICKSORT(A, q + 1, r);
    }
}
int PARTITION(int *A, int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++){
        if(A[j] <= x){
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i + 1;
}
int HOARE_PARTITION(int *A,int p,int r){
    int x = A[p];
    int i = p - 1;
    int j = r + 1;
    while(true){
        do{
            j--;
        }while(A[j] <= x);

        do{
            i++;
        }while(A[i] >= x)
        if(i < j){
            swap(A[i], A[j]);
        }
        else{
            return j;
        }
    }
}
int n = 8;
void print(int *a){
    for(int i = 0; i < n; i++)
        cout << a[i] <<" ";
    cout << endl;
}
int main(){
    int a[] = {1, 2, 6, 2, 4, 1, 3, 1 };
    print(a);
    QUICKSORT(a, 0,n - 1);
    print(a);
}
