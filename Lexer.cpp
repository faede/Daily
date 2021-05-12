#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/zyy/Documents/GitHub/Daily/define.cpp"
using namespace std;


string Tokens[50];
void init(){
    //Tokens[]
    Tokens[0] = "PLUS";
    Tokens[1] = "MINUS";
    Tokens[2] = "STAR";
    Tokens[3] = "SLASH";
    Tokens[4] = "LESS";
    Tokens[5] = "GREATER";
    Tokens[6] = "EQUAL";
    Tokens[7] = "PERCENT";
    Tokens[8] = "BACKQUOTE";
    Tokens[9] = "LBRACE";
    Tokens[10] = "RBRACE";
    Tokens[11] = "LESSEQUAL";
    Tokens[12] = "GREATEREQUAL";
    Tokens[13] = "TILDE";
    Tokens[14] = "CIRCUMFLEX";
    Tokens[15] = "LEFTSHIFT";
    Tokens[16] = "RIGHTSHIFT";
    Tokens[17] = "DOUBLESTAR";
    Tokens[18] = "PLUSEQUAL";
    Tokens[19] = "MINEQUAL";
    Tokens[20] = "STAREQUAL";
    Tokens[21] = "SLASHEQUAL";
    Tokens[22] = "LPAR";
    Tokens[23] = "RPAR";
    Tokens[24] = "LSQB";
    Tokens[25] = "RSQB";
    Tokens[26] = "COLON";
    Tokens[27] = "COMMA";
    Tokens[28] = "SEMI";
    Tokens[29] = "PGEND";
    Tokens[30] = "NOTEQUAL";
    Tokens[31] = "VBAR";
    Tokens[32] = "AMPER";
    Tokens[33] = "NAME";
    Tokens[34] = "NUMBER";
    Tokens[35] = "STRING";
    Tokens[36] = "OP";
    Tokens[37] = "KEYWORD";
    Tokens[38] = "ASSIGN";
}

string KeyWord[13] = {"if", "then", "var", "const", "procedure", "begin", "end", \
				 "odd", "call", "while", "do", "read", "write"};

// judge alphabet
bool ISALPHABET(char c){
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

// judge digital
bool ISDIGITAL(char c){
    return c >= '0' && c <= '9';
}

bool find_key(string s){
    bool find  = false;
    for (int i = 0; i < 13; i++){
        if(KeyWord[i] == s){
            find = true;
            break;
        }
    }
    return find;
}

int
PL0_Token_OneChar(char c)
{
    switch (c) {
        case '(':	return LPAR;
        case ')':	return RPAR;
        case '[':	return LSQB;
        case ']':	return RSQB;
        case ':':	return COLON;
        case ',':	return COMMA;
        case ';':	return SEMI;
        case '+':	return PLUS;
        case '-':	return MINUS;
        case '*':	return STAR;
        case '/':	return SLASH;
        case '|':	return VBAR;
        case '&':	return AMPER;
        case '<':	return LESS;
        case '>':	return GREATER;
        case '=':	return EQUAL;
        case '.':	return PGEND;
        case '%':	return PERCENT;
        case '`':	return BACKQUOTE;
        case '{':	return LBRACE;
        case '}':	return RBRACE;
        case '^':	return CIRCUMFLEX;
        case '~':	return TILDE;
        case '#':   return NOTEQUAL;
        default:	return CANT_TOKEN;
    }
}
int
PL0_TwoChars(char c1, char c2)
{
    switch (c1) {
        case ':':
            switch (c2) {
                case '=':	return ASSIGN;
            }
            break;
        case '<':
            switch (c2) {
                case '>':	return NOTEQUAL;
                case '=':	return LESSEQUAL;
                case '<':	return LEFTSHIFT;
            }
            break;
        case '>':
            switch (c2) {
                case '=':	return GREATEREQUAL;
                case '>':	return RIGHTSHIFT;
            }
            break;
        case '+':
            switch (c2) {
                case '=':	return PLUSEQUAL;
            }
            break;
        case '-':
            switch (c2) {
                case '=':	return MINEQUAL;
            }
            break;
        case '*':
            switch (c2) {
                case '*':	return DOUBLESTAR;
                case '=':	return STAREQUAL;
            }
            break;
        case '/':
            switch (c2) {
                case '=':	return SLASHEQUAL;
            }
            break;
    }
    return CANT_TOKEN;
}

int token(FILE * fstream, char & ch){
    //char ch;
    bool last_is_alp = false;
    string buf = "";
    bool all_is_digit = true;
    bool exist_digit = false;
    bool exist_alp = false;
    bool exist_op = false;
    while( ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF){
        //printf("%c",ch);
        //cout <<"22222" << endl;
        if(ISDIGITAL(ch)){
            // must fitst check
            if(exist_op)
                break;
            exist_digit = true;
        }else if (ISALPHABET(ch)){
            if(exist_op)
                break;
            all_is_digit = false;
            exist_alp = true;
        }else {
            if(exist_alp || exist_digit)
                break;
            exist_op = true;
            all_is_digit = false;
            //switch (ch){
            //	case ',': 1;

            //	break;

            //};
        }
        buf += ch;

        // get next
        ch = getc(fstream);
    }
    //cout <<"1111" << endl;

    if(exist_digit && all_is_digit){
        //cout << "get buff:  " << buf << " 			";
        return NUMBER;
    }else if(exist_alp){
        // if first letter is digit , error
        if(ISDIGITAL(buf[0])){
            printf("ERROR, name must begin with alphabet\n");
            exit(NAME_DEFINE_ERROR);
        }


        // over  length
        if(buf.length() > MAX_LENGTH_NAME){
            exit(NAME_OVER_LIMIT_ERROR);
        }

        //cout << "get buff:  " << buf << " 			";
        if(find_key(buf)){

            return KEYWORD;
        }else{
            return NAME;
        }
    }else{
        // TODO: test error
        //cout <<" to op" << endl;
        int check;
        if(buf.length() == 1){
            check =  PL0_Token_OneChar(buf[0]);
        }else if(buf.length() == 2){
            //cout << "get two !!!  :    " << buf[0] <<"  " << buf[1]<<"    ";
            check =  PL0_TwoChars(buf[0], buf[1]);
        }
        if(check == CANT_TOKEN){
            //cout << "get buff:  " << buf[0]<< " 			";
            fseek(fstream,-1, SEEK_CUR);
            ch = buf[1];
            return  PL0_Token_OneChar(buf[0]);
        }else{
            //cout << "get buff:  " << buf<< " 			";
            //cout << "get buff:  " << buf << "size : " <<buf.length()<<" 			";
            return  check;
        }



    }
    return -1;
}
int main(){
    //string file = "/Users/zyy/Documents/GitHub/Daily/test.txt";
    init();
    FILE * fstream ;
    fstream =  fopen("/Users/zyy/Documents/GitHub/Daily/test.txt","r");
    // = fopen(file,"a+");
    //将标准输出重定向到 out.txt文件
    freopen("/Users/zyy/Documents/GitHub/Daily/out.txt", "w", stdout);
    char ch;
    if(fstream == NULL)
    {
        printf("Read File Failed!\n");
        exit(READ_FILE_ERROR);
    }
    ch = getc(fstream);
    while(ch  != EOF){
        if(ch == ' ' || ch == '\t' || ch == '\n'){
            ch = getc(fstream);
            continue;
        }
        cout << Tokens[token(fstream, ch) ]<<"  " ;
        //if(ISALPHABET(ch) || ISALPHABET(ch)){
        //    ch = getc(fstream);
        //}
        //cout <<"333333" << endl;
    }
    //token( file)

}