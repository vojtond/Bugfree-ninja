#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int pom;
int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu){
struct    GlobTabSymbolu GlobTabulka;
    strInit(&(GlobTabulka.nazev));
    pom=strCopyString(&(GlobTabulka.nazev) , NazevTokenu);
     printf("nazevf: %s\n",strGetStr(NazevFunkce));
    printf("String je: %s\n",strGetStr(&(GlobTabulka.nazev)));
     printf("typ je: %i\n",TypTokenu);
    return 1;

}
