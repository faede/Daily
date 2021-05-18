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
			//Paser_Statement();
			break;
	}

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
			//Paser_Statement();
			break;
	}

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
			//Paser_Statement();
			break;
	}
	Paser_Statement();
}

void Paser_ProcedureDeclaration(){
	// {procedure <id> ; <分程序>;}
	while(look_n() == PROCEDURE){
		// procedure
		read_n();

		// id
		if(look_n() != NAME){
			printf("Line %d ,define need a id \n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}

		// ;
		if(look_n() != COMMA){
			printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}

		// <分程序>
		Paser_Block();

		// ;
		if(look_n() != COMMA){
			printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}
	}
}

void Paser_ConstDeclaration(){
	// 分程序 -> const <常量定义>  {, <常量定义> } ; 

	// const 
	read_n();

	// <常量定义>
	if(look_n() != NAME){
		printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
	}else{
		read_n();
	}
	
	if(look_n() != EQUAL){
		printf("Line %d ,define need a '='\n", Lex_Tokens_Line[Paser_Token_Index]);
	}else{
		read_n();
	}

	if(look_n() != NUMBER){
		printf("Line %d ,define need a number\n", Lex_Tokens_Line[Paser_Token_Index]);
	}else{
		read_n();
	}

	// [{, <常量定义>} ; ]
	while(look_n() == COMMA){
		read_n();
		if(look_n() != NAME){
			printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}
	
		if(look_n() != EQUAL){
			printf("Line %d ,define need a '='\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}

		if(look_n() != NUMBER){
			printf("Line %d ,define need a number\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}
	}


	// ;
	if(look_n() != SEMI){
		printf("Line %d ,missing ';' after define\n", Lex_Tokens_Line[Paser_Token_Index]); 
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
		printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
	}else{
		read_n();
	}

	// [{, < 变量定义>} ; ]
	while(look_n() == COMMA){
		read_n();
		if(look_n() != NAME){
			printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}
	}

	// ;
	if(look_n() != SEMI){
		printf("Line %d ,missing ';' after define\n", Lex_Tokens_Line[Paser_Token_Index]); 
	}else{
		read_n();
	}
}

void Paser_Statement(){
	int num = look_n();
	switch(num){
		case IF:
			{
				// if
				read_n();

				Paser_Condition();

				if(look_n() != THEN){
					printf("Line %d ,'if' must continue with 'then'\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				Paser_Statement();
			}
			break;
		case WHILE:
			{
				// while
				read_n();

				Paser_Condition();

				if(look_n() != DO){
					printf("Line %d ,'while' must continue with 'do'\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				Paser_Statement();
			}
			break;
		case CALL:
			{
				// call
				read_n();

				// id
				if(look_n() != NAME){
					printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}
			}
			break;
		case READ:
			{
				// read
				read_n();

				// '('
				if(look_n() != LPAR){
					printf("Line %d ,missing '(' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				// id
				if(look_n() != NAME){
					printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				while(look_n() == COMMA){
					// ,
					read_n();

					// id
					if(look_n() != NAME){
						printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
					}else{
						read_n();
					}
				}

				// ')'
				if(look_n() != LPAR){
					printf("Line %d ,missing ')' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

			}
			break;
		case WRITE:
			{
				// read
				read_n();

				// '('
				if(look_n() != LPAR){
					printf("Line %d ,missing '(' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				// exp
				Paser_Expression();

				while(look_n() == COMMA){
					// ,
					read_n();

					// exp
					Paser_Expression();
				}

				// ')'
				if(look_n() != LPAR){
					printf("Line %d ,missing ')' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}
			}
			break;
		case BEGIN:
			{
				// read
				read_n();

				// 'begin'
				if(look_n() != BEGIN){
					printf("Line %d ,missing 'begin' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

				// state
				Paser_Statement();
				
				while(look_n() == SEMI){
					// ,
					read_n();

					// state
					Paser_Statement();
				}

				// 'end'
				if(look_n() != END){
					printf("Line %d ,missing 'end' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
				}else{
					read_n();
				}

			}
			break;
		default:
			return ;
	}
}

void Paser_Condition(){
	// odd
	if(look_n() == ODD){

		// odd
		read_n();

		Paser_Expression();
	}else{

		Paser_Expression(); 

		int t = look_n();
		if(t == EQUAL || t == NOTEQUAL || t == LESS || t == LESSEQUAL || t == GREATER || t == GREATEREQUAL){
			read_n();
		}else{
			printf("Line %d ,missing symbol after exp\n", Lex_Tokens_Line[Paser_Token_Index]);
		}

		Paser_Expression();

	}
}

void Paser_Expression(){

	// [+ / -]
	if(look_n() == PLUS || look_n() == MINUS){
		read_n();
	}

	Paser_Factor();

	while(look_n() == PLUS || look_n() == MINUS){
		// [+ / -]
		read_n();

		Paser_Factor();
	}
}

void Paser_Term(){
	Paser_Factor();

	while(look_n() == STAR || look_n() == SLASH){
		// * / /
		read_n();

		Paser_Factor();
	}
}

void Paser_Factor(){

	if(look_n() == NAME){
		read_n();
	}
	else if(look_n() == NUMBER){
		read_n();
	}else{
		// '('
		if(look_n() != LPAR){
			printf("Line %d ,missing '(' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}

		// exp
		Paser_Expression();

		// ')'
		if(look_n() != LPAR){
			printf("Line %d ,missing ')' after read\n", Lex_Tokens_Line[Paser_Token_Index]);
		}else{
			read_n();
		}
		
	}
}

void Paser(){
	Paser_Block();
	if(look_n() != PGEND){
		printf("Line %d ,ERROR, Program must end with '.' \n", Lex_Tokens_Line[Paser_Token_Index]);
	} 

}

int main(){
	lex();

}