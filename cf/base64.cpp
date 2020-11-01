#include <iostream>
#include <fstream>
#include <ostream>
#include <streambuf>
#include <string>
using namespace std;
//  author: zyy
//
//  base64
//  use 64 printable char to represent binary file
//
//  algotirhm principle : 
//  since for 6bits each bit have 2 chooce 0 or 1,so total have 2^6 = 64 situtaions , 
//  and we have  4 * (6 bits)= 24  bits= 3 * (8 bits) =  3 bytes
//  so for each 3 bytes we can use 4 char to present them


//code

// preasent just support txt
string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64(string &str, ofstream &out){
	long long num_of_bytes = str.length();
	long long num_of_symbols = num_of_bytes / 3;
	int res_bytes = num_of_bytes % 3;

	string base64_str;
	register int sym_0, sym_1, sym_2, sym_3;
	for(long long i = 0; i < num_of_symbols; ++i){

		sym_0 = str[i * 3 + 0]>>2;
		sym_1 = ((str[i * 3 + 0]&3)<<4)|(str[i * 3 + 1]>>4);
		sym_2 = ((str[i * 3 + 1]&0xF)<<2)|(str[i * 3 + 2]>>6); 
		sym_3 = str[i * 3 + 2]&63;

		base64_str += base[sym_0];
		base64_str += base[sym_1];
		base64_str += base[sym_2];
		base64_str += base[sym_3];

	}
	sym_0 = str[num_of_symbols * 3];
	if(res_bytes == 1){
		sym_1 = ((str[num_of_symbols * 3 + 0]&3)<<4);

		base64_str += base[sym_0];
		base64_str += base[sym_1];
	}
	else{
		sym_1 = ((str[num_of_symbols * 3 + 0]&3)<<4)|(str[num_of_symbols * 3 + 1]>>4);
		sym_2 = (str[num_of_symbols * 3 + 1]&7)<<2;

		base64_str += base[sym_0];
		base64_str += base[sym_1];
		base64_str += base[sym_2];
	}

	out<<base64_str;
	
}


// code 
int main(){
	//string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	// typedef std::basic_fstream<char> fstream
	//fstream read_binary_file("test.txt",ios::binary| ios::in | ios::out);
	//char read_3_bytes [3];
	//read_binary_file.read((char *)&read_binary_file,3);
	ifstream file("/Users/zyy/Documents/GitHub/Daily/cf/test.txt");
	ofstream out_file("/Users/zyy/Documents/base64.txt");
	//ifstream file("/Users/zyy/Documents/test.jpg");
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>() );
	//cout<<str;
	base64(str,out_file);


}