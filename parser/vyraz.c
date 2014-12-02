/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int sp=0;
int sppom=0;
int t;
int ptstack[1000];
int ptable[14][14];
int c;
int i;
int j;
int k=0;
FILE *ptabletxt;


int VYRAZ(tGlobSymbolTable *ST,Tridic *ridic){
    printf("token %i\n",ridic->token);
    c=0;
    i=0;
    j=0;

    ptabletxt = fopen("ptable.txt", "r");

    while ((c = fgetc(ptabletxt)) != EOF){
      c=c-48;
      if (c>0)
      {
          ptable[i][j]=c;
          j++;
      }
      else
        {
            i++;
            j=0;
        }
    }
    fclose(ptabletxt);
    //j=0;

   /* for (i=0;i<=13;i++)                   //vypis precedencni tabulky
    {
        for (j=0;j<=13;j++)
        {
            printf("%d",ptable[i][j]);
        }
        printf("\n");
    }*/

    ptstack[0]=13;
    switch (ridic->token){
        case 11:
        {
            printf("chyba pico, nemuzes dat pravou zavorku jako prvni");
            return;
        }
    }
    ptstack[1]=ridic->token;
    sppom=1;
    sp++;
    printf("zasobnik %i\n",ptstack[0]);

    while ((t=gtoken(ridic))!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN){
        /*printf("token %i\n",ridic->token);
        printf("tabulka %i\n",ptable[ptstack[sp]][t]);*/
        switch(ptable[ptstack[sp]][t]){
            case 1:
            {
                ptstack[sp+1]=t;
                sp++;
                printf("shift");
            }
            break;
            case 2:
            {
                ptstack[sppom]=2048;
                sppom++;
                sp=sppom;
                printf("redukce");
            }
            break;
            case 3:
            {

            }
            break;
            case 4:
            {
                printf("FUCK YOU BITCHES");
            }
            break;
        }
        printf("zasobnik %i\n",ptstack[k]);
        k++;
    }
    /*gtoken(ridic);
    printf("sdfsdfsdf %i\n", token);
    gtoken(ridic);
    printf("sdfsdfsdf %i\n", token);
    gtoken(ridic);
    printf("sdfsdfsdf %i\n", token);*/
    return 1;



return 0;
}


/*
ZADANE FCE LENGTH COPY FIND SORT
jak rozlisit identifikator od zadanych fci? mara vraci ve string....asi se ptat na string

*/




