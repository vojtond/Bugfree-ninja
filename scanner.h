#include "str.c"

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
#define TP_LBRA 10            //levá závorka
#define TP_RBRA 11            //pravá závorka
#define TP_PLUS 12            //+
#define TP_MINUS 13           //-
#define TP_MUL 14             //*
#define TP_MOD 15             //MODULO
#define TP_COL 16             //:
#define TP_SGNMNT 17          //:=
#define TP_CHAR 18            //#0..255
#define TP_STRING 19          //a..z A..Z
#define TP_KEY 20             //Kličová slova
#define TP_IDENT 21           //Identifikátor
#define TP_MORE 22             //>
#define TP_MOREEQ 23           //>=


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


#define DO			 	50
#define IF			 	51
#define END             53
#define VAR             54
#define ELSE            55
#define FIND            56
#define REAL            57
#define SORT            58
#define THEN            59
#define TRUE            60
#define BEGIN           61
#define FALSE           62
#define WHILE           63
#define WRITE           64
#define READLN          65
#define STRING          66
#define BOOLEAN         67
#define FORWARD         68
#define INTEGER         69
#define FUNCTION        70



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
int vojta();
