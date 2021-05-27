#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int main(){
    int n;
    //cin >> n;
   int a[] = {84, 104, 101, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 105, 115, 58, 32, 101, 110, 97, 109, 97, 97, 98, 100, 115, 115, 114, 103};
   for(auto i : a){
       char c = i;
       cout << c;
   }
}
