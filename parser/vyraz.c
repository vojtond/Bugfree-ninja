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

    printf("sdfsdf %i\n",token);
    c=0;
    i=0;
    j=0;

    ptabletxt = fopen("ptable.txt", "r");

    while ((c = fgetc(ptabletxt)) != EOF)
    {
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
    j=0;

    for (i=0;i<=13;i++)
    {
        for (j=0;j<=13;j++)
        {
            printf("%d",ptable[i][j]);
        }
        printf("\n");
    }

    ptstack[0]=53;
    ptstack[1]=token;
    sppom=1;
    sp++;

    while ((t=gtoken(ridic))!=53)
    {
        printf("tabulka %i\n",ptable[ptstack[sp]][t]);
        switch(ptable[ptstack[sp]][t])
        {
            case 1:
            {
                ptstack[sp+1]=t;
                sp++;
            }
            break;
            case 2:
            {
                ptstack[sppom]=2048;
                sppom++;
                sp=sppom;
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
        printf("abcd %i\n",ptstack[k]);
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




