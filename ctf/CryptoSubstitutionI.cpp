#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
char tran(char c, int n ){
    if(c == ' ')
        return c;
    return ((c - 'a') - n + 26) % 26 + 'a';
}
char tran2(char c){
    if(c == 'n')
        return 'w';
    if(c == 'w')
        return 'n';
    if(c == 'a')
        return 't';
    if(c == 't')
        return 'a';
    if(c == 'i')
        return 'x';
    if(c == 'x')
        return 'i';
    return c;
}
int main(){
    string s = "ru gjh pzvsijgu idy udt xpb khpy gjse vu mkshby s pv svckheehy nhku ahzz ydbh udtk edztgsdb whu se kcivmkxxphdr gjse zsggzh xjpzzhbih ape bdg gdd jpky ape sg";
    for(int i = 0; i == 0; i++){
        for(int j = 0; j < s.length(); j++){
            cout << tran(s[j],i);
        }
        cout << endl;
    }

    cout <<"rrrrrrrrrrrrrrrrrrrrr:" << endl;
    for(int i = 0; i == 0; i++){
        for(int j = 0; j < s.length(); j++){
            cout << tran2(s[j]);
        }
        cout << endl;
    }

}
