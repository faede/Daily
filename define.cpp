#define PLUS 		0		// +
#define MINUS		1		// -
#define STAR		2		// *
#define SLASH		3		// /
#define LESS		4		// <
#define GREATER		5		// >
#define EQUAL		6		// =
#define PERCENT		7 		// %
#define BACKQUOTE	8		// `
#define LBRACE		9 		// {        left brace
#define RBRACE		10		// }		right brace
#define LESSEQUAL	11		// <=
#define GREATEREQUAL	12	// >=
#define TILDE		13		// ~
#define CIRCUMFLEX	14		// ^
#define LEFTSHIFT	15		// <<
#define RIGHTSHIFT	16		// >>
#define DOUBLESTAR	17		// **
#define PLUSEQUAL	18		// +=
#define MINEQUAL	19		// -=
#define STAREQUAL	20		// *=
#define SLASHEQUAL	21		// /=
#define LPAR		22		// (	open parenthesis
#define RPAR		23		// )	close parenthesis
#define LSQB		24		// [    left square bracket
#define RSQB		25		// ]
#define COLON		26		// :
#define COMMA		27		// ,
#define SEMI		28		// ;

#define PGEND		29		// .

#define NOTEQUAL	30		// #
#define VBAR        31      // |
#define AMPER       32      // &
#define NAME		33
#define NUMBER		34
#define STRING		35
#define OP 			36
#define KEYWORD 	37
#define ASSIGN 		38		// :=

#define CANT_TOKEN 		39
#define UNDEFINE_CHAR 	40

#define KEY_SHIFT 41


#define BEGIN		41
#define CALL		42
#define CONST		43
#define DO			44
#define END			45
#define IF			46
#define ODD			47
#define PROCEDURE	48
#define READ		49
#define THEN		50
#define VAR			51
#define WHILE		52
#define WRITE		53




// MAX length
#define MAX_LENGTH_NAME 128


// ERROR CODE
#define READ_FILE_ERROR 		1
#define NAME_DEFINE_ERROR 		2
#define NAME_OVER_LIMIT_ERROR	3
#define UNDEFINE_CHAR_ERROR		4

#define INPUT_FILE "/Users/zyy/Documents/GitHub/Daily/test.txt"
#define OUTPUT_FILE "/Users/zyy/Documents/GitHub/Daily/out.txt"


#include <string>
#include <vector>
using namespace std;
vector<int> Lex_Tokens;
vector<int> Lex_Tokens_Line;
string Tokens[80];
long long LINE_NUMBER = 0;
int Paser_Token_Index = 0;
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

    // Keyword
    Tokens[41] = "BEGIN";
    Tokens[42] = "CALL";
    Tokens[43] = "CONST";
    Tokens[44] = "DO";
    Tokens[45] = "END";
    Tokens[46] = "IF";
    Tokens[47] = "ODD";
    Tokens[48] = "PROCEDURE";
    Tokens[49] = "READ";
    Tokens[50] = "THEN";
    Tokens[51] = "VAR";
    Tokens[52] = "WHILE";
    Tokens[53] = "WRITE";
}

string KeyWord[13] = {"begin", "call", "const", "do", "end", "if", "odd", \
				"procedure", "read", "then", "var", "while", "write"};

bool ISALPHABET(char c);
bool ISDIGITAL(char c);
bool find_key(string s, int & index);
char getc_and_record(FILE * fstream);
int PL0_Token_OneChar(char c);
int PL0_TwoChars(char c1, char c2);
int token(FILE * fstream, char & ch);


int lex();


int look_n();
void read_n();
void Paser_Block();
void Paser_ProcedureDeclaration();
void Paser_ConstDeclaration();
void Paser_VarDeclaration();
void Paser_Statement();
void Paser_Condition();
void Paser_Term();
void Paser_Factor();
void Paser();
void Paser_Expression();
