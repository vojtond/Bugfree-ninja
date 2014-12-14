#include "lin.seznam.h"

typedef struct zasobnik     /* Struktura pro zásobník */
{
  sRamec *Pomramec;
  struct zasobnik *next;
} ZASOBNIK;
ZASOBNIK*Zfirst;


void Interpret(tGlobSymbolTable *ST);
