#include <iostream>
#include <algorithm>
#include <cstdio>
#include <regex>

using namespace std;
int main(){
    regex exp2("^$");
    regex exp("^wechall4?.(ext|jpg|gif|tiff|bmp|png)$");
    if(regex_match("wechall4.tiff", exp) )
        cout << "String:literal => matched\n";
    if(regex_match("wechall.png", exp))
        cout << "match 2\n";

}
