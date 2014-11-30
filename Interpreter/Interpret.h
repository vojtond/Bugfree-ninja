#include <string.h>
#include <stdbool.h>

typedef enum
{
/* *** Numerické operace *** */
I_ADD,		// +
I_SUB,		// -
I_MUL,		// *
I_DIV,		// /
I_POW,		// ^
I_ASSIGN,	// :=

/* *** Logické operace *** */
I_MORE,		// >
I_LESS,		// <
I_MORE_EQUAL,	// >=
I_LESS_EQUAL,	// <=
I_EQUAL,		// =
I_NOT_EQUAL,	// !=

/* *** Vestavìné funkce*** */
I_FIND,		// find
I_SORT,		// sort
I_LENGTH,		// délka
I_COPY,		// copy

/* *** Skoky *** */
I_LABEL,		// návìstí
I_GOTO,		// skok
I_JUMP,
I_FJUMP,
I_TJUMP,
// I_FCEGOTO
} tOperation;

typedef enum
{
T_Double,
T_Bool,
T_String,
} tTyp;

typedef struct
{
double d;
bool b;
char *s;
} tValue;

typedef struct
{
tTyp Typ;
tValue value;
}tOperator;

void Interpret();
