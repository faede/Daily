#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/zyy/Documents/GitHub/Daily/define.cpp"
using namespace std;




// judge alphabet
bool ISALPHABET(char c){
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

// judge digital
bool ISDIGITAL(char c){
    return c >= '0' && c <= '9';
}

bool find_key(string s, int & index){
    bool find  = false;
    for (int i = 0; i < 13; i++){
        if(KeyWord[i] == s){
        	index = i + KEY_SHIFT;
            find = true;
            break;
        }
    }
    return find;
}

char getc_and_record(FILE * fstream){
	char ch;
	ch = getc(fstream);
	if(ch == '\n'){
		LINE_NUMBER++;
	}
	return ch;
}
int PL0_Token_OneChar(char c)
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
        default:	return UNDEFINE_CHAR;
    }
}
int PL0_TwoChars(char c1, char c2)
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
    bool last_is_alp = false;
    string buf = "";
    bool all_is_digit = true;
    bool exist_digit = false;
    bool exist_alp = false;
    bool exist_op = false;
    while( ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF){
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
        }
        buf += ch;

        // get next
        ch = getc_and_record(fstream);
    }

    if(exist_digit && all_is_digit){
    	Lex_Tokens_Rel.push_back(buf);
        return NUMBER;
    }else if(exist_alp){
        // if first letter is digit , error
        if(ISDIGITAL(buf[0])){
            printf("ERROR in line %lld, name must begin with alphabet\n", LINE_NUMBER);
            exit(NAME_DEFINE_ERROR);
        }


        // over  length
        if(buf.length() > MAX_LENGTH_NAME){
        	printf("ERROR in line %lld, name length must less than 128\n", LINE_NUMBER);
            exit(NAME_OVER_LIMIT_ERROR);
        }

        int index;
        if(find_key(buf, index)){
        	Lex_Tokens_Rel.push_back(buf);
            return index;
        }else{
        	Lex_Tokens_Rel.push_back(buf);
            return NAME;
        }
    }else{
        int check;
        if(buf.length() == 1){
            check =  PL0_Token_OneChar(buf[0]);
        }else if(buf.length() == 2){
            check =  PL0_TwoChars(buf[0], buf[1]);
        }else{
        	// buf.length() >= 3
        	check = PL0_Token_OneChar(buf[0]);
        	if(check == UNDEFINE_CHAR){
        		printf("ERROR in line %lld, Undefine Char\n", LINE_NUMBER);
        		exit(UNDEFINE_CHAR_ERROR);
        	}
        	long int shift = - (buf.length() - 1);
        	fseek(fstream, shift, SEEK_CUR);
            ch = buf[1];
        }
        if(check == UNDEFINE_CHAR){
        	printf("ERROR in line %lld, Undefine Char\n", LINE_NUMBER);
        	exit(UNDEFINE_CHAR_ERROR);
        }
        else if(check == CANT_TOKEN){
            fseek(fstream, -1, SEEK_CUR);
            ch = buf[1];
            string ts;
            ts.push_back(buf[0]);
            Lex_Tokens_Rel.push_back(ts);
            return  PL0_Token_OneChar(buf[0]);
        }else{
        	Lex_Tokens_Rel.push_back(buf);
            return  check;
        }



    }
    return -1;
}

int lex(){
	init();
    FILE * fstream ;
    fstream =  fopen(INPUT_FILE,"r");
    freopen(OUTPUT_FILE, "w", stdout);
    char ch;
    if(fstream == NULL)
    {
        printf("Read File Failed!\n");
        exit(READ_FILE_ERROR);
    }
    ch = getc_and_record(fstream);
    while(ch  != EOF){
        if(ch == ' ' || ch == '\t' || ch == '\n'){
            ch = getc_and_record(fstream);
            continue;
        }
        int token_index = token(fstream, ch);
        string temp = Tokens[token_index];
        Lex_Tokens.push_back(token_index);
        Lex_Tokens_Line.push_back(LINE_NUMBER);
        cout << temp;
        if(temp == "SEMI"){
        	cout << endl;
        }else{
        	cout << " ";
        }
    }
    return 0;
}
/* int main(){
    init();
    FILE * fstream ;
    fstream =  fopen(INPUT_FILE,"r");
    freopen(OUTPUT_FILE, "w", stdout);
    char ch;
    if(fstream == NULL)
    {
        printf("Read File Failed!\n");
        exit(READ_FILE_ERROR);
    }
    ch = getc_and_record(fstream);
    while(ch  != EOF){
        if(ch == ' ' || ch == '\t' || ch == '\n'){
            ch = getc_and_record(fstream);
            continue;
        }
        int token_index = token(fstream, ch);
        string temp = Tokens[token_index];
        Lex_Tokens.push_back(token_index);
        cout << temp;
        if(temp == "SEMI"){
        	cout << endl;
        }else{
        	cout << " ";
        }
    }
    return 0;

}

*/
