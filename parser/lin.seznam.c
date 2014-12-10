#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lin.seznam.h"

void trojinsert(int i, string *op1, string *op2, string *result);  /* Funkce pro vložení nového prvku */
void trojfindpoz(int pozice);   /* Funkce pro hledání pozice */
void generatelabel(tTroj *pom);     /* Funkce pro generování návìští */
void PushS();       /* Funkce pro uložení do zásobníku */
void PopTopS();     /* Funkce pro vybrání ze zásobníku */

int pozice;     /* Promìnná pro uložení pozice */
int Pomlabel=0; /* Promìnná pro návìští */
int Pomlabelx=0;    /* Promìnná pro návìští */
int ifelse=0;   /* Promìnná pro zanoøení do else vìtve */

void trojinit(){
    Trfirst=NULL;
    Trlast=NULL;
}

void trojinsert(int i, string *op1, string *op2, string *result){
    tTroj *pom;    /* Promìnná ukazující na seznam */

    pom=(tTroj*) malloc(sizeof(tTroj ));    /* Alokování nového prvku */
    pom->data.inst=i;
    strInit(&(pom->data.op1));
    strInit(&(pom->data.op2));
    strInit(&(pom->data.result));
    if (op1!=NULL)
        strCopyString(&(pom->data.op1),op1);
    if (op2!=NULL)
        strCopyString(&(pom->data.op2),op2);
    if (result!=NULL)
        strCopyString(&(pom->data.result),result);

    pom->next=NULL;

    if (Trlast!=NULL){  /* Pokud existuje poslední prvek, pøidá se novì vytvoøený prvek */

        Trlast->next=pom;
        pozice++;
        pom->data.pozice=pozice;

    }
    else{
        Trfirst=pom;
        pozice = 1;
        pom->data.pozice=pozice;

    }
    Trlast=pom;

    /* ***************** IF_BEGIN **************** */
    if (pom->data.inst == IF_BEGIN){
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        PushS();
        Pomlabel+=4;
        Pomlabelx+=3;
        pom->data.inst=41;
    }
/* ***************** IF_END **************** */
    else if (pom->data.inst == IF_END){
        PopTopS();
        Pomlabel++;
        pom->data.label=Pomlabel;
        pom->data.inst=40;
    }
/* ***************** ELSE_BEGIN **************** */
    else if (pom->data.inst == ELSE_BEGIN){
        if (ifelse>0) Pomlabel++;
        ifelse++;
        pom->data.label=Pomlabel;
        int pompoz = pom->data.pozice-1;
        trojfindpoz(pompoz);
        PushS();
        pom->data.inst=40;
    }
/* ***************** ELSE_END **************** */
    else if (pom->data.inst == ELSE_END){
        ifelse--;
        PopTopS();
        Pomlabel++;
        pom->data.label=Pomlabel;
        pom->data.inst=40;
    }
/* ***************** WHILE_BEGIN_LAB **************** */
    else if (pom->data.inst == WHILE_BEGINLAB){
        if (ifelse>0) Pomlabel++;
        Pomlabel++;
        if (ifelse>0) Pomlabel++;
        pom->data.label=Pomlabel+1;
        pom->data.inst=40;
    }
/* ***************** WHILE_BEGIN **************** */
    else if (pom->data.inst == WHILE_BEGIN){
        Pomlabelx++;
        if (ifelse>0) Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        PushS();
        Pomlabel++;
        Pomlabelx++;
        pom->data.inst=41;
    }
/* ***************** WHILE_END **************** */
    else if (pom->data.inst == WHILE_END){
        PopTopS();
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        pom->data.inst=42;
    }
/* ***************** WHILE_END_LAB **************** */
     else if (pom->data.inst == WHILE_ENDLAB){
        Pomlabel++;
        pom->data.label=Pomlabel-1;
        pom->data.inst=40;
    }
/* ***************** FCE_CALL **************** */
    else if (pom->data.inst == 48){
        pom->data.inst=43;
    }
/* ***************** FCE_BEGIN **************** */
    else if (pom->data.inst == FUNCTION_BEGIN){
        pom->data.inst=44;
    }
/* ***************** FCE_END **************** */
    else if (pom->data.inst == FUNCTION_END){
        pom->data.inst=45;
    }
}

void trojvypis(){
    tTroj *pom; /* Promìnná ukazující na seznam */
    pom=Trfirst;

    while (pom!=NULL){  /* Procházení celého seznamu a vypisování prvkù seznamu */
        printf("%i %s %s %s ",pom->data.inst, strGetStr(&(pom->data.op1)), strGetStr(&(pom->data.op2)), strGetStr(&(pom->data.result)));
        if (pom->data.label!=0) printf("->L%i",pom->data.label); printf("\n");
        pom=pom->next;
    }
}

void trojfindpoz(int pozice){
    tTroj *pom; /* Promìnná ukazující na seznam */
    pom=Trfirst;

    while (pom!=NULL){  /* Procházení celého seznamu a hledání pozice prvku */
        if (pom->data.pozice == pozice){
                Pomlabelx++;        /* Ošetøení když je v IF i ELSE větev */
                strInit(&pom->data.op1);
                generatelabel(pom);
                pom->data.label=0;
                pom->data.inst=42;
            break;
        }
        pom=pom->next;
    }
}

int trojfindfce(string fce){
    tTroj *pom; /* Promìnná ukazující na seznam */
    pom=Trfirst;

    while (pom!=NULL){  /* Procházení celého seznamu a hledání názvu funkce */
        if (strGetStr(&(pom->data.op1)) == strGetStr(&(fce))){
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1->str, pom->data.op2->str, pom->data.result->str, pom->data.pozice, pom->data.label);
            return pom->data.pozice;
            break;
        }
        pom=pom->next;
    }
return 0;
}

int trojfindlab(string o){
    tTroj *pom;     /* Promìnná ukazující na seznam */
    pom=Trfirst;
   char *Pomo = strGetStr(&(o));

    int vysl=0;     /* Pøeètení hodnoty a zjištìní kam se má skoèit */
    if ((Pomo[3]>='0')&&(Pomo[3]<='9')){  /* Pro hodnoty vìtší jak 100 */
        int f=Pomo[3];
        f-=48;
        vysl+=100*f;
    }
    else if ((Pomo[2]>='0')&&(Pomo[2]<='9')){ /* Pro hodnoty vìtší jak 10 */
        int f=Pomo[2];
        f-=48;
        vysl+=10*f;
    }
    else if ((Pomo[1]>='0')&&(Pomo[1]<='9')){ /* Pro hodnoty menší jak 10 */
        int f=Pomo[1];
        f-=48;
        vysl+=f;
    }

    while ( pom!=NULL ){    /* Procházení celého seznamu a hledání návìští */
        if (pom->data.label == vysl ){
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1->str, pom->data.op2->str, pom->data.result->str, pom->data.pozice, pom->data.label);
            return pom->data.pozice;
            break;
        }
        pom=pom->next;
    }
return 0;
}

/* ************ GENERATE_LABEL ************* */
void generatelabel(tTroj *pom)
{
    strAddChar(&pom->data.op1,'L'); /* Generování pomocného labelu kam skoèit napø->"L1","L33" */
        if (Pomlabelx>99){      /* Generování pro label vìtší jak 100 */
            char z = 48;
            char z1 = 48;
            char p1 = Pomlabelx;
            while (p1>99){z1++; p1-=100;}
                strAddChar(&pom->data.op1,z1);
            char p = p1;
            while (p>9){z++; p-=10;}
                strAddChar(&pom->data.op1,z);
            p=p+48;
            strAddChar(&pom->data.op1,p);
        }else if(Pomlabelx>9){     /* Generování pro label vìtší jak 10 */
            char z = 48;
            char p = Pomlabelx;
            while (p>9){z++; p-=10;}
                strAddChar(&pom->data.op1,z);
            p=p+48;
            strAddChar(&pom->data.op1,p);
        }else{      /* Generování pro label menší jak 10 */
            char c=Pomlabelx+48;
            strAddChar(&pom->data.op1,c);
        }
}

void PushS(){
    SKOK *pom;  /* Ukazatel na zásobník */
    pom=(SKOK*) malloc(sizeof(SKOK));   /* Alokace pro novou promìnnou */
    pom->Pomlabel=Pomlabel;     /* Uložení hodnot do zásobníku */
    pom->Pomlabelx=Pomlabelx;
    pom->next=Tfirst;
    Tfirst=pom;
}

void PopTopS(){
    SKOK *pom;  /* Ukazatel na zásobník */

    if (Tfirst!=NULL){
        pom=Tfirst;
        Tfirst=Tfirst->next;
        Pomlabel=pom->Pomlabel; /* Výbìr hodnot ze zásobníku */
        Pomlabelx=pom->Pomlabelx;
        free(pom);     /* Uvolnìní promìnné */
    }
}

void Generate(int Ginst, string *Gop1, string *Gop2, string *Gresult)
{
        trojinsert(Ginst, Gop1, Gop2, Gresult); /* Zapsaní prvku do seznamu */
}
