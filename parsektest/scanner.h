#include "str.h"

#define TP_INT 0             //0..9
#define TP_REAL_EXP 1        //0..9 . 0..9 +-E 0..9
#define TP_REAL 2            //0..9 . 0..9
#define TP_EOF 3             //EOF
#define TP_EOL 4             //EOL
#define TP_SEM 5             //;
#define TP_LESS 6            //<
#define TP_NEQU 7            //<>
#define TP_LESSEQ 8          //<=
#define TP_DOT 9             //.
#define TP_LBRA 10           //levá závorka
#define TP_RBRA 11           //pravá závorka
#define TP_PLUS 12           //+
#define TP_MINUS 13          //-
#define TP_MUL 14            //*
#define TP_MOD 15            //MODULO
#define TP_COL 16            //:
#define TP_SGNMNT 17         //:=
#define TP_CHAR 18           //#0..255
#define TP_STRING 19         //a..z A..Z

#define TP_IDENT 21          //Identifikátor
#define TP_MORE 22           //>
#define TP_MOREEQ 23         //>=
#define TP_COMMA 24          //,

#define ST_START 30
#define	ST_NUMBER 31
#define	ST_REAL_EXP 32
#define	ST_REAL 33
#define	ST_KOMENT 34
#define	ST_IDENT_KEY 35
#define	ST_GREATER 36
#define	ST_STRING 37
#define	ST_CHAR 38
#define	ST_SEM 39
#define	ST_LESS 40
#define	ST_COLONS 41
#define	ST_MORE 42


#define KEY_DO			 	50
#define KEY_IF			 	51
#define KEY_END             53
#define KEY_VAR             54
#define KEY_ELSE            55
#define KEY_FIND            56
#define KEY_REAL            57
#define KEY_SORT            58
#define KEY_THEN            59
#define KEY_TRUE            60
#define KEY_BEGIN           61
#define KEY_FALSE           62
#define KEY_WHILE           63
#define KEY_WRITE           64
#define KEY_READLN          65
#define KEY_STRING          66
#define KEY_BOOLEAN         67
#define KEY_FORWARD         68
#define KEY_INTEGER         69
#define KEY_FUNCTION        70



typedef struct {
	int type;
	int error;
	int next_state;
	int line;
	double charnum;
	string *stri;
	//TExp_tree *last_tree;
	//my_string name;
} SToken;
int get_token(FILE *F, SToken *token );
