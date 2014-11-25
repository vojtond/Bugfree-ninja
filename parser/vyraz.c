/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int sp=0;
int ptstack[1000];
int ptable[14][14];
int c;
int i;
int j;
FILE *ptabletxt;


int VYRAZ(){

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

    gtoken();
    return 1;



return 0;
}


/*
ZADANE FCE LENGTH COPY FIND SORT
jak rozlisit identifikator od zadanych fci? mara vraci ve string....asi se ptat na string

*/




