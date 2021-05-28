#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;
int main(){
    string s = "oWdnreuf.lY uoc nar ae dht eemssga eaw yebttrew eh nht eelttre sra enic roertco drre . Ihtni koy uowlu dilekt  oes eoyrup sawsro don:wi ihfpncagci.d";
    for(int k = 2; k == 2 ;k ++){
        for(int i = 0; i < s.length(); i+=2){
            cout << s[i+1] << s[i];
        }
        cout << endl;
    }
}
