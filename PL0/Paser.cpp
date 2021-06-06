#include <algorithm>
#include "Lexer.cpp"
#include <iomanip>
using namespace std;



string name,value;

int look_n(){
    return Lex_Tokens[Paser_Token_Index];
}

void read_n(){
    Paser_Token_Index++;
}

void Paser_Block(){
    printf("Pasering Block\n");

    switch(look_n()){
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

    switch(look_n()){
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

    switch(look_n()){
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

    printf("Pasering Block End , No error\n");
}

void Paser_ProcedureDeclaration(){
    printf("Pasering procedure\n");
    // {procedure <id> ; <分程序>;}
    while(look_n() == PROCEDURE){
        // procedure
        read_n();

        // id
        if(look_n() != NAME){
            printf("Line %d ,define need a id \n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            name =  Lex_Tokens_Rel[Paser_Token_Index];
            Symbol_Table[name] = make_pair("procedure", "0");
            read_n();
        }

        // ;
        if(look_n() != SEMI){
            printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }

        // <分程序>
        Paser_Block();

        // ;
        if(look_n() != SEMI){
            printf("Line %d ,missing ';' in define\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }
    }

    printf("Pasering procedure End , No error\n");
}

void Paser_ConstDeclaration(){
    printf("Pasering Declaration\n");
    // 分程序 -> const <常量定义>  {, <常量定义> } ;

    // const
    read_n();


    // <常量定义>
    if(look_n() != NAME){
        printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
    }else{
        name =  Lex_Tokens_Rel[Paser_Token_Index];
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
        value = Lex_Tokens_Rel[Paser_Token_Index];
        Symbol_Table[name] = make_pair("const", value);
        read_n();
    }

    // [{, <常量定义>} ; ]
    while(look_n() == COMMA){
        read_n();
        if(look_n() != NAME){
            printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            name =  Lex_Tokens_Rel[Paser_Token_Index];
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
            value = Lex_Tokens_Rel[Paser_Token_Index];
            Symbol_Table[name] = make_pair("const", value);
            read_n();
        }
    }


    // ;
    if(look_n() != SEMI){
        printf("Line %d ,missing ';' after define\n", Lex_Tokens_Line[Paser_Token_Index]);
    }else{
        read_n();
    }

    printf("Pasering ConstDeclaration End , No error\n");
}

void Paser_VarDeclaration(){
    printf("Pasering Var\n");
    // 分程序 -> var <变量定义> {, <变量定义> } ;

    // var
    read_n();

    // <变量定义>
    if(look_n() != NAME){
        printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
    }else{
        name =  Lex_Tokens_Rel[Paser_Token_Index];
        Symbol_Table[name] = make_pair("var", "0");
        read_n();
    }

    // [{, < 变量定义>} ; ]
    while(look_n() == COMMA){
        read_n();
        if(look_n() != NAME){
            printf("Line %d ,define need a id\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            name =  Lex_Tokens_Rel[Paser_Token_Index];
            Symbol_Table[name] = make_pair("var", "0");
            read_n();
        }
    }

    // ;
    if(look_n() != SEMI){
        printf("Line %d ,missing ';' after define\n", Lex_Tokens_Line[Paser_Token_Index]);
    }else{
        read_n();
    }

    printf("Pasering VarDeclaration End , No error\n");
}

void Paser_Statement(){
    printf("Pasering Statement\n");
    //int num = look_n();
    switch(look_n()){
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
            Paser_Expression();

            while(look_n() == COMMA){
                // ,
                read_n();

                // exp
                Paser_Expression();
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
            Paser_Statement();

            while(look_n() == SEMI){
                // ;
                read_n();

                // state
                Paser_Statement();
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

            Paser_Expression();
        }
        default:
            return ;
    }

    printf("Pasering Statement End , No error\n");
}

void Paser_Condition(){
    printf("Pasering Condition\n");
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
    printf("Pasering Condition End , No error\n");
}

void Paser_Expression(){
    printf("Pasering Expression\n");
    // [+ / -]
    if(look_n() == PLUS || look_n() == MINUS){
        read_n();
    }

    Paser_Term();

    while(look_n() == PLUS || look_n() == MINUS){
        // [+ / -]
        read_n();

        Paser_Term();
    }

    printf("Pasering Expression End , No error\n");
}

void Paser_Term(){
    printf("Pasering Term\n");

    Paser_Factor();

    while(look_n() == STAR || look_n() == SLASH){
        // * / /
        read_n();

        Paser_Factor();
    }

    printf("Pasering Term End , No error\n");
}

void Paser_Factor(){
    printf("Pasering Factor\n");
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
        Paser_Expression();

        // ')'
        if(look_n() != RPAR){
            printf("Line %d ,missing ')' after '(' exp\n", Lex_Tokens_Line[Paser_Token_Index]);
        }else{
            read_n();
        }

    }

    printf("Pasering Factor End , No error\n");
}

void Paser(){
    Paser_Block();
    if(look_n() != PGEND){
        printf("Line %d ,ERROR, Program must end with '.' \n", Lex_Tokens_Line[Paser_Token_Index]);
    }

}

int main(){
    lex();
    vector<int>();
    printf("\nPaser begin:\n");
    Paser();
    cout << std::left << setfill('-') << setw(21) << "|";
    cout << std::left << setfill('-') << setw(21) << "|";
    cout << std::left << setfill('-') << setw(21) << "|";
    cout <<"|" << endl;
    //cout <<"|" << std::left << setfill('-') << setw(20) << " ";
    //cout <<"|" << std::left << setfill('-') << setw(20) << " ";
    //cout <<"|" << std::left << setfill('-') << setw(20) << " ";
    //cout <<"|" << endl;

    cout <<"|" << std::left << setfill(' ') << setw(20) << "Symbol Name";
    cout <<"|" << std::left << setfill(' ') << setw(20) << "Type";
    cout <<"|" << std::left << setfill(' ') << setw(20) << "Value";
    cout <<"|" << endl;

    cout << std::left << setfill('-') << setw(21) << "|";
    cout << std::left << setfill('-') << setw(21) << "|";
    cout << std::left << setfill('-') << setw(21) << "|";
    cout <<"|" << endl;

    for(auto i : Symbol_Table){
        cout <<"|" << std::left << setfill(' ') << setw(20) << i.first;
        cout <<"|" << std::left << setfill(' ') << setw(20) << i.second.first;
        cout <<"|" << std::left << setfill(' ') << setw(20) << i.second.second;
        cout <<"|" << endl;

        cout << std::left << setfill('-') << setw(21) << "|";
        cout << std::left << setfill('-') << setw(21) << "|";
        cout << std::left << setfill('-') << setw(21) << "|";
        cout <<"|" << endl;
    }

}