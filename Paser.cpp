#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
// #include "/Users/zyy/Documents/GitHub/Daily/define.cpp"
#include "/Users/zyy/Documents/GitHub/Daily/Lexer.cpp"
using namespace std;


// TODO: add error line 

int look_n(){
	// TODO: read next token  return token number
	return Lex_Tokens[Paser_Token_Index];
}

void read_n(){
	// TODO: read and move
	Paser_Token_Index++;
}

void Paser_Block(){
	int num = look_n();
	switch(num){
		case CONST:
			Paser_ConstDeclaration();
			break;
		case VAR:
			Paser_VarDeclaration();
			break;
		case PROCEDURE:
			Paser_ProcedureDeclaration();
			break;
		default:
			Paser_Statement();
			break;
	}
}

void Paser_ProcedureDeclaration(){

}

void Paser_ConstDeclaration(){
	// 分程序 -> const <常量定义>  {, <常量定义> } ; 


	// const 
	read_n();

	// <常量定义>
	if(look_n() != NAME){
		printf("define need a id\n");
	}else{
		read_n();
	}
	
	if(look_n() != EQUAL){
		printf("define need a '='\n");
	}else{
		read_n();
	}

	if(look_n() != NUMBER){
		printf("define need a number\n");
	}else{
		read_n();
	}

	// [{, <常量定义>} ; ]
	while(look_n() == COMMA){
		read_n();
		if(look_n() != NAME){
			printf("define need a id\n");
		}else{
			read_n();
		}
	
		if(look_n() != EQUAL){
			printf("define need a '='\n");
		}else{
			read_n();
		}

		if(look_n() != NUMBER){
			printf("define need a number\n");
		}else{
			read_n();
		}
	}


	// ;
	if(look_n() != SEMI){
		printf("missing ';' after define\n"); 
	}else{
		read_n();
	}
}

void Paser_VarDeclaration(){
	// 分程序 -> var <变量定义> {, <变量定义> } ; 

	// var 
	read_n();

	// <变量定义>
	if(look_n() != NAME){
		printf("define need a id\n");
	}else{
		read_n();
	}

	// [{, < 变量定义>} ; ]
	while(look_n() == COMMA){
		read_n();
		if(look_n() != NAME){
			printf("define need a id\n");
		}else{
			read_n();
		}
	}

	// ;
	if(look_n() != SEMI){
		printf("missing ';' after define\n"); 
	}else{
		read_n();
	}
}

void Paser_Statement(){

}

void	Paser_Condition(){

}

void Paser_Expression(){

}

void Paser_Term(){

}

void Paser_Factor(){

}

void Paser(){
	Paser_Block();
	if(look_n() != PGEND){
		printf("ERROR, Program must end with '.' \n");
	} 

}

int main(){
	lex();

}