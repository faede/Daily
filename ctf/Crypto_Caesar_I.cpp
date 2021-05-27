#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
    string s;
    getline(cin, s);
    //cin >> s;
    cout << s;
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < s.length(); j++){
            char c;
            if(s[j] != ' ')
                c =  (s[j] - 'A' - i + 26) % 26 + 'A';
            else
             
                c = ' ';
            cout << c;
        }
        cout << endl;
      //  cout << endl;
    }

}
