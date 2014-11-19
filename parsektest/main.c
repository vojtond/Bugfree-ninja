#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"
FILE *soubor;
  SToken *token;
int main()
{

    token=malloc(sizeof(SToken));
    token->stri=malloc(sizeof(string));
    token->type=-1;


  /*  while (token->type != 3)
    {
        if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvoøit øetìzec\n");
        }

        get_token(soubor,token);
        printf("\nJe to typ: %i\n",token->type);
        printf("Charnum je: %f\n",token->charnum);
        printf("String je: %s\n",strGetStr(token->stri));
        printf("**************************************\n");
        strFree(token->stri);
        //printf("String je: %s\n",token->stri);
    }

    fclose(soubor);*/
    soubor = fopen("text.txt", "r");
    if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvoøit øetìzec\n");
        }
    printf ("%i",START());
    free(token);
    fclose(soubor);

    return 4;
}
int START (){
    int je;

     get_token(soubor,token);

    printf("\nsd\n");
    if ((token->charnum == BEGIN) || (token->charnum == VAR) || (token->charnum == FUNCTION)) {
        if (SLOZ()) {
            printf("\nsd3\n");
            strFree(token->stri);
            get_token(soubor,token);

            token->type==TP_DOT;
            return 1;
        }

    }
printf("\nfgfg\n");
return 0;

}
int SLOZ (){

    printf("\nsd3\n");
     if (token->charnum == BEGIN){


       get_token(soubor,token);


       if (token->charnum == 53.0){
        printf("\nsd2\n");
        return 1;
       }

     }
return 0;
}
