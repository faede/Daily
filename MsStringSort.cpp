#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

/*
 * Windows Apps Win32 API The Windows Shell Shlwapi.h StrCmpLogicalW function
 *
 * https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-strcmplogicalw
 * https://docs.microsoft.com/en-us/dotnet/api/microsoft.visualbasic.compilerservices.stringtype.strcmp?view=net-6.0
 *
 * StrCmpLogicalW --- call ---> StrCmp --- call ---> (without regard to case sensitivity.)
 *
 * */
// (12asd13d) -> (12, asd, 13, d)
shared_ptr<vector<shared_ptr<string>>> SplitStringToVector(shared_ptr<string> str){
	unsigned len = str->length();
	if(len == 0)
		return nullptr;
	unsigned int index = 0;
	shared_ptr<vector<shared_ptr<string>>> lists = make_shared< vector<shared_ptr<string>> >();
	string buf = "";
	int flag = 0;
    int judge = -2;
	for(; index < len; ++index){
        judge = isdigit((*str)[index])? 1 : -1; // TODO
		if(flag == 0 || flag == judge){
            buf += (*str)[index];

		}else if(flag == -judge){
		    lists->push_back(make_shared<string>(buf));
            buf = "";
            buf += (*str)[index];
		}else{
		    // TODO
		    // never
		    cout << "error!" <<endl;
		    return nullptr;
		}
        flag = judge;
	}
    if(buf != "")
        lists->push_back(make_shared<string>(buf));
    return lists;
}
bool cmp_string(shared_ptr<string> left, shared_ptr<string> right){
    int tag_left = isdigit((*left)[0]);
    int tag_right = isdigit((*right)[0]);
    if(tag_left && tag_right){
        return stoi(*left) < stoi(*right);
    }else if(tag_left == 0 && tag_right == 0){
        return *left < *right;
    }else
        return tag_left > tag_right;
}

bool cmp_vec_splited(shared_ptr<vector<shared_ptr<string>>> left, shared_ptr<vector<shared_ptr<string>>> right){
    unsigned index = 0;
    while(index < left->size()){
        if(index >= right->size())
            return false;
        if(cmp_string( (*left)[index], (*right)[index]) != cmp_string( (*right)[index], (*left)[index])){
            return cmp_string( (*left)[index], (*right)[index]);
        }
        index++;
    }
    return true;
}

bool cmp_vec(shared_ptr<string> left, shared_ptr<string> right){
    auto left_splited = SplitStringToVector(left);
    auto right_splited = SplitStringToVector(right);
    return cmp_vec_splited(left_splited, right_splited);
}

int main(){
    /*shared_ptr<string> str = make_shared<string>("123asd132");
    shared_ptr<vector<shared_ptr<string>>> res = SplitStringToVector(str);
    for(auto a : *res){
        cout << *a <<endl;
    }
    sort(res->begin(), res->end(), cmp_string);
    for(auto a: *res){
        cout << *a <<endl;
    }*/
    vector<string> need = {"2string", "3string", "20string", "st2ring", "st3ring",
                            "st20ring", "string2", "string3", "string20"};
    for(auto str : need){
        cout << str <<endl;
    }
    shared_ptr<vector<shared_ptr<string>>> ptrs = make_shared<vector<shared_ptr<string>>>();
    cout << "before sort :" << endl;
    for(auto str : need){
        ptrs->push_back(make_shared<string>(str));
    }
    for(auto str : *ptrs){
        cout << *str <<endl;
    }
    sort(ptrs->begin(), ptrs->end(), cmp_vec);
    cout << "after sort :" <<endl;
    for(auto str : *ptrs){
        cout << *str <<endl;
    }
}
