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

void Paser_Block(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Block\n");
    #endif
    fa = PL0_AddChild(fa, Block, "Block", Lex_Tokens_Lineo[Paser_Token_Index]);

    switch(look_n()){
        case CONST:
            Paser_ConstDeclaration(fa);
            break;
        case VAR:
            Paser_VarDeclaration(fa);
            break;
        case PROCEDURE:
            Paser_ProcedureDeclaration(fa);
            break;
        default:
            //Paser_Statement();
            break;
    }

    switch(look_n()){
        case CONST:
            Paser_ConstDeclaration(fa);
            break;
        case VAR:
            Paser_VarDeclaration(fa);
            break;
        case PROCEDURE:
            Paser_ProcedureDeclaration(fa);
            break;
        default:
            //Paser_Statement();
            break;
    }

    switch(look_n()){
        case CONST:
            Paser_ConstDeclaration(fa);
            break;
        case VAR:
            Paser_VarDeclaration(fa);
            break;
        case PROCEDURE:
            Paser_ProcedureDeclaration(fa);
            break;
        default:
            //Paser_Statement();
            break;
    }
    Paser_Statement(fa);

    #if DEBUG_MODE == 1
    printf("Pasering Block End , No error\n");
    #endif
}

void Paser_ProcedureDeclaration(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering procedure\n");
    #endif

    //
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
        if(look_n() != SEMI){
            printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }

        node *fa2 = PL0_AddChild(fa, 0, "procedure", Lex_Tokens_Lineo[Paser_Token_Index]);
        // <分程序>
        Paser_Block(fa2);

        // ;
        if(look_n() != SEMI){
            printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }
    }
    #if DEBUG_MODE == 1
    printf("Pasering procedure End , No error\n");
    #endif
}

void Paser_ConstDeclaration(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Declaration\n");
    #endif
    // 分程序 -> const <常量定义>  {, <常量定义> } ;

    // const
    read_n();

    node * fa2 = PL0_AddChild(fa, 0, Lex_Tokens_Rel[Paser_Token_Index], Lex_Tokens_Lineo[Paser_Token_Index]);
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
    	fa2 = PL0_AddChild(fa, 0, Lex_Tokens_Rel[Paser_Token_Index], Lex_Tokens_Lineo[Paser_Token_Index]);
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
    fa = fa2

    // ;
    if(look_n() != SEMI){
        printf("Line %d ,missing ';' after define\n", Lex_Tokens_Line[Paser_Token_Index]);
    }else{
        read_n();
    }

    #if DEBUG_MODE == 1
    printf("Pasering ConstDeclaration End , No error\n");
    #endif
}

void Paser_VarDeclaration(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Var\n");
    #endif
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

    #if DEBUG_MODE == 1
    printf("Pasering VarDeclaration End , No error\n");
    #endif
}

void Paser_Statement(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Statement\n");
    #endif
    //int num = look_n();
    switch(look_n()){
        case IF:
        {
            // if
            read_n();

            Paser_Condition(fa);

            if(look_n() != THEN){
                printf("Line %d ,'if' must continue with 'then'\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

            Paser_Statement(fa);
        }
            break;
        case WHILE:
        {
            // while
            read_n();

            Paser_Condition(fa);

            if(look_n() != DO){
                printf("Line %d ,'while' must continue with 'do'\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

            Paser_Statement(fa);
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
            if(look_n() != RPAR){
                printf("Line %d ,missing ')' after read '('\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

        }
            break;
        case WRITE:
        {
            // read write
            read_n();

            // '('
            if(look_n() != LPAR){
                printf("Line %d ,missing '(' after write\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

            // exp
            Paser_Expression(fa);

            while(look_n() == COMMA){
                // ,
                read_n();

                // exp
                Paser_Expression(fa);
            }

            // ')'
            if(look_n() != RPAR){
                printf("Line %d ,missing ')' after write '('\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }
        }
            break;
        case BEGIN:
        {
            // read begin
            read_n();

            // state
            Paser_Statement(fa);

            while(look_n() == SEMI){
                // ;
                read_n();

                // state
                Paser_Statement(fa);
            }
            // 'end'
            if(look_n() != END){
                printf("Line %d ,missing 'end' after begin\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

        }
            break;
        case NAME:
        {
            // read id
            read_n();

            if(look_n() != ASSIGN){
                printf("Line %d ,missing '=' in assign\n", Lex_Tokens_Line[Paser_Token_Index]);
            }else{
                read_n();
            }

            Paser_Expression(fa);
        }
        default:
            return ;
    }

    #if DEBUG_MODE == 1
    printf("Pasering Statement End , No error\n");
    #endif
}

void Paser_Condition(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Condition\n");
    #endif
    // odd
    if(look_n() == ODD){

        // odd
        read_n();

        Paser_Expression(fa);
    }else{

        Paser_Expression(fa);

        int t = look_n();
        if(t == EQUAL || t == NOTEQUAL || t == LESS || t == LESSEQUAL || t == GREATER || t == GREATEREQUAL){
            read_n();
        }else{
            printf("Line %d ,missing symbol after exp\n", Lex_Tokens_Line[Paser_Token_Index]);
        }

        Paser_Expression(fa);

    }

    #if DEBUG_MODE == 1
    printf("Pasering Condition End , No error\n");
    #endif
}

void Paser_Expression(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Expression\n");
    #endif
    // [+ / -]
    if(look_n() == PLUS || look_n() == MINUS){
        read_n();
    }

    Paser_Term(fa);

    while(look_n() == PLUS || look_n() == MINUS){
        // [+ / -]
        read_n();

        Paser_Term(fa);
    }
    #if DEBUG_MODE == 1
    printf("Pasering Expression End , No error\n");
    #endif
}

void Paser_Term(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Term\n");
    #endif
    Paser_Factor(fa);

    while(look_n() == STAR || look_n() == SLASH){
        // * / /
        read_n();

        Paser_Factor(fa);
    }

    #if DEBUG_MODE == 1
    printf("Pasering Term End , No error\n");
    #endif
}

void Paser_Factor(ndoe * fa){
	#if DEBUG_MODE == 1
    printf("Pasering Factor\n");
    #endif

    if(look_n() == NAME){
        read_n();
    }
    else if(look_n() == NUMBER){
        read_n();
    }else{
        // '('
        if(look_n() != LPAR){
            printf("Line %d ,missing '(' before exp\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }

        // exp
        Paser_Expression(fa);

        // ')'
        if(look_n() != RPAR){
            printf("Line %d ,missing ')' after '(' exp\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }

    }

    #if DEBUG_MODE == 1
    printf("Pasering Factor End , No error\n");
    #endif
}

void Paser(ndoe * fa){
    Paser_Block();
    if(look_n() != PGEND){
        printf("Line %d ,ERROR, Program must end with '.' \n", Lex_Tokens_Line[Paser_Token_Index]);
    }

}

int main(){
    lex();
    #if DEBUG_MODE == 1
    printf("\nPaser begin:\n");
    #endif

    Paser_tree P_t ;
    Paser(P_t.root);
}