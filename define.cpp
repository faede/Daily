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

#define CANT_TOKEN 39
/*
#define WHILE 		0
#define CONST 		1
#define VAR	   		2
#define PROCEDURE 	3
#define BEGIN		4
#define END			5
#define ODD			6
#define IF			7
#define THEN 		8
#define CALL 		9
#define WHILE 		10
#define DO			11
#define READ		12
#define WRITE		13
*/



// MAX length
#define MAX_LENGTH_NAME 128


// ERROR CODE
#define READ_FILE_ERROR 		1
#define NAME_DEFINE_ERROR 		2
#define NAME_OVER_LIMIT_ERROR	3