/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "vyraz.h"

int sp=0;
int aktiv;
int loadid=0;
int redukpom;
int redukid=0;
int redukzavor=0;
int countlevz=0;
int countpravz=0;
int t;
int ptstack[1000];
int ptable[14][14];
int c;
int i;
int j;
int k=0;
FILE *ptabletxt;


int VYRAZ(tGlobSymbolTable *ST,Tridic *ridic){

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

    ptstack[0]=13;
    switch (ridic->token){
        case 11:
        {
            printf("chyba pico, nemuzes dat pravou zavorku jako prvni \n");
            error(ST,SEM_ERR,ridic);
        }
        break;
        case TP_SEM:
        {
            printf("chyba pico, prazdny vyraz \n");
            error(ST,SEM_ERR,ridic);
        }
        break;
        case KEY_END:
        {
            printf("chyba pico, prazdny vyraz \n");
            error(ST,SEM_ERR,ridic);
        }
        break;
        case KEY_DO:
        {
            printf("chyba pico, prazdny vyraz \n");
            error(ST,SEM_ERR,ridic);
        }
        break;
        case KEY_THEN:
        {
            printf("chyba pico, prazdny vyraz \n");
            error(ST,SEM_ERR,ridic);
        }
        break;
    }
    t=ridic->token;
    if ((t>=0)&&(t<=9)){
        printf("chyba pico, nemuzes dat operator jako prvni \n");
        error(ST,SEM_ERR,ridic);
    }else
    if (t==10){
        ptstack[1]=-1;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        countlevz++;
    }else
    if(t==12){
        ptstack[1]=-1;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        loadid=1;
    }
    //printf("sdgdf %i \n",ptstack[0]);

    i=0;
    while (i<=sp){
      printf("zasobnik %i\n",ptstack[i]);
      i++;
    }
    //printf("zasobnik %i\n",ptstack[0]);

    while ((t=gtoken(ridic))!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN){
        if (t==10){
            countlevz++;
        }else
        if (t==11){
            countpravz++;
        }

        if (((t>=0)&&(t<=9)) && (ptstack[sp]>=0 && ptstack[sp]<=9)){
            printf("2 operatory za sebou");
            error(ST,SEM_ERR,ridic);
        }
        switch(ptable[ptstack[aktiv]][t]){
            case 1:
            {
                shifting();
                i=0;
                while (i<=sp){
                    printf("zasobnik1 %i\n",ptstack[i]);
                    i++;
                }
                printf("\n");
            }
            break;
            case 2:
            {
                while (ptable[ptstack[aktiv]][t]==2){
                        reduction();
                }
                loadid=1;
                shifting();
                i=0;
                while (i<=sp){
                    printf("zasobnik2 %i\n",ptstack[i]);
                    i++;
                }
                printf("\n");
            }
            break;
            case 3:
            {
                sp++;
                ptstack[sp]=t;
                aktiv=sp;
            }
            break;
            case 4:
            {
                printf("chyba pico, blby ukonceni \n");
                error(ST,SEM_ERR,ridic);
            }
            break;
        }
    }
    if (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN){
        i=0;
        while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("active %i \n",ptstack[aktiv]);
        printf("\n");


        while (ptable[ptstack[aktiv]][13]==2){
            reduction();
        }


        i=0;
        while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("active %i \n",ptstack[aktiv]);
        printf("\n");
    }
    if (countlevz > countpravz){
        printf("chyba pico, levych zavorek je vic nez pravych \n");
        error(ST,SEM_ERR,ridic);
    }else
    if  (countlevz < countpravz){
        printf("chyba pico, pravych zavorek je vic nez levych \n");
        error(ST,SEM_ERR,ridic);
    }else
    if  (countlevz = countpravz){
        printf("pocet zavorek souhlasi \n");
    }

    if (aktiv == 0 && sp == 2 && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){
        ptstack[1]=ptstack[2];
        sp=1;
    }
    if ((ptstack[aktiv]==13)&&(t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){
        printf("Redukce kompletni \n");
    }
    //if ()

    i=0;
    while (i<=sp){
      printf("zasobnik %i\n",ptstack[i]);
      i++;
    }
    printf("\n");
    return 1;

return 0;
}

void reduction(){

    if ((ptstack[sp]>=0 && ptstack[sp]<=9) && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){
        printf("chyba pico, blby ukonceni \n");
        error(NULL,SEM_ERR,NULL);
    }

    redukpom=sp;
    while (ptstack[redukpom]!=-1){
        if (ptstack[redukpom]==12){
            redukid=1;
        }
        if (ptstack[redukpom]==10){
            redukzavor=1;
        }
        redukpom--;
    }
    sp=redukpom;
    if (redukid==1 || redukzavor==1){
            printf("id %i   zavor %i token %i\n",redukid,redukzavor,t);
        if (redukid==1){
            ptstack[sp]=-1;
            sp++;
                ptstack[sp]=1024;
            redukid=0;
            aktiv=redukpom-1;
        }else
        if (redukzavor==1 && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){

            ptstack[sp]=1024;
            aktiv=redukpom-1;
        }else
        if (t!=11){
            aktiv=redukpom-1;
            ptstack[redukpom+1]=1111;
            sp=sp+1;
        }
        else{
            ptstack[sp]=10245;
            aktiv=redukpom-1;
        }
    }else {
        ptstack[sp]=2048;
        aktiv=redukpom-1;
    }
    i=0;
    if (ptstack[aktiv]==13 && t!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN && ptstack[1]!=-1){
        ptstack[2]=ptstack[1];
        ptstack[1]=-1;
        sp++;
    }
    while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("\n");
    printf("active %i \n",ptstack[aktiv]);
    return;
}

void shifting(){

    if (((t>=0)&&(t<=9))&&(loadid==1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
        loadid=0;
    }else
    if (((t>=0)&&(t<=9))&&(loadid==0)){
        printf("chyba pico, nemuzes dat operator za operator nebo hned za levou zavorku \n");
        error(NULL,SEM_ERR,NULL);
    }else
    if ((t==11)&&(loadid==1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if ((t==11)&&(loadid==0)){
        printf("chyba pico, nemuzes dat pravou zavorku za operator \n");
        error(NULL,SEM_ERR,NULL);
    }else
    if (t==10){
        sp++;
        ptstack[sp]=-1;
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if (t==12){
        sp++;
        ptstack[sp]=-1;
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
        loadid=1;
    }
    return;

}


/*
ZADANE FCE LENGTH COPY FIND SORT
jak rozlisit identifikator od zadanych fci? mara vraci ve string....asi se ptat na string

*/




