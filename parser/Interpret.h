#include "lin.seznam.h"

typedef struct zasobnik     /* Struktura pro z�sobn�k */
{
  sRamec *Pomramec;
  struct zasobnik *next;
} ZASOBNIK;
ZASOBNIK*Zfirst;


void Interpret(tGlobSymbolTable *ST);
