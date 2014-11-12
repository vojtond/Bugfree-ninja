#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "scanner.h"

#define TEXT "text.txt"
/*struct na token*/
/*funkce: gettoken, body, tìlo, while atd.*/
/*rekurzivní postup*/
int main(){
    hlavni:int;
    SToken *token;
    FILE *soubor;
    token=malloc(sizeof(SToken));
    token->stri=malloc(sizeof(string));
    token->type=-1;
    soubor = fopen(TEXT, "r");
    hlavni:get_token(soubor,token);
return 1;
}
