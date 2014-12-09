#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lin.seznam.h"

void trojinsert(int i, string *op1, string *op2, string *result);  /* Funkce pro vlo�en� nov�ho prvku */
void trojfindpoz(int pozice);   /* Funkce pro hled�n� pozice */
void generatelabel(tTroj *pom);     /* Funkce pro generov�n� n�v�t� */
void PushS();       /* Funkce pro ulo�en� do z�sobn�ku */
void PopTopS();     /* Funkce pro vybr�n� ze z�sobn�ku */

int pozice;     /* Prom�nn� pro ulo�en� pozice */
int Pomlabel=0; /* Prom�nn� pro n�v�t� */
int Pomlabelx=0;    /* Prom�nn� pro n�v�t� */
int ifelse=0;   /* Prom�nn� pro zano�en� do else v�tve */

void trojinit(){
    Trfirst=NULL;
    Trlast=NULL;
}

void trojinsert(int i, string *op1, string *op2, string *result){
    tTroj *pom;    /* Prom�nn� ukazuj�c� na seznam */



    pom=(tTroj*) malloc(sizeof(tTroj ));    /* Alokov�n� nov�ho prvku */
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

    if (Trlast!=NULL){  /* Pokud existuje posledn� prvek, p�id� se nov� vytvo�en� prvek */

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
    tTroj *pom; /* Prom�nn� ukazuj�c� na seznam */
    pom=Trfirst;
    while (pom!=NULL){  /* Proch�zen� cel�ho seznamu a vypisov�n� prvk� seznamu */
        printf("%i %s %s %s ",pom->data.inst, strGetStr(&(pom->data.op1)), strGetStr(&(pom->data.op2)), strGetStr(&(pom->data.result)));
        if (pom->data.label!=0) printf("->L%i",pom->data.label); printf("\n");
        pom=pom->next;
    }
}

void trojfindpoz(int pozice){
    tTroj *pom; /* Prom�nn� ukazuj�c� na seznam */
    pom=Trfirst;
    while (pom!=NULL){  /* Proch�zen� cel�ho seznamu a hled�n� pozice prvku */
        if (pom->data.pozice == pozice){
                Pomlabelx++;        /* O�et�en� kdy� je v IF i ELSE v�tev */
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
    tTroj *pom; /* Prom�nn� ukazuj�c� na seznam */
    pom=Trfirst;
    while (pom!=NULL){  /* Proch�zen� cel�ho seznamu a hled�n� n�zvu funkce */
/*        if (pom->data.op1->str == fce->str){
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1->str, pom->data.op2->str, pom->data.result->str, pom->data.pozice, pom->data.label);
            return pom->data.pozice;
            break;
        }
        pom=pom->next;*/
    }
return 0;
}

int trojfindlab(string o){
    tTroj *pom;     /* Prom�nn� ukazuj�c� na seznam */
    pom=Trfirst;

    int vysl=0;     /* P�e�ten� hodnoty a zji�t�n� kam se m� sko�it */
    if ((o.str[3]>='0')&&(o.str[3]<='9')){  /* Pro hodnoty v�t�� jak 100 */
        int f=o.str[3];
        f-=48;
        vysl+=100*f;
    }
    else if ((o.str[2]>='0')&&(o.str[2]<='9')){ /* Pro hodnoty v�t�� jak 10 */
        int f=o.str[2];
        f-=48;
        vysl+=10*f;
    }
    else if ((o.str[1]>='0')&&(o.str[1]<='9')){ /* Pro hodnoty men�� jak 10 */
        int f=o.str[1];
        f-=48;
        vysl+=f;
    }

    while ( pom!=NULL ){    /* Proch�zen� cel�ho seznamu a hled�n� n�v�t� */
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
    strAddChar(&pom->data.op1,'L'); /* Generov�n� pomocn�ho labelu kam sko�it nap�->"L1","L33" */
        if (Pomlabelx>99){      /* Generov�n� pro label v�t�� jak 100 */
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
        }else if(Pomlabelx>9){     /* Generov�n� pro label v�t�� jak 10 */
            char z = 48;
            char p = Pomlabelx;
            while (p>9){z++; p-=10;}
                strAddChar(&pom->data.op1,z);
            p=p+48;
            strAddChar(&pom->data.op1,p);
        }else{      /* Generov�n� pro label men�� jak 10 */
            char c=Pomlabelx+48;
            strAddChar(&pom->data.op1,c);
        }
}

void PushS(){
    SKOK *pom;  /* Ukazatel na z�sobn�k */
    pom=(SKOK*) malloc(sizeof(SKOK));   /* Alokace pro novou prom�nnou */
    pom->Pomlabel=Pomlabel;     /* Ulo�en� hodnot do z�sobn�ku */
    pom->Pomlabelx=Pomlabelx;
    pom->next=Tfirst;
    Tfirst=pom;
}

void PopTopS(){
    SKOK *pom;  /* Ukazatel na z�sobn�k */
    if (Tfirst!=NULL){
        pom=Tfirst;
        Tfirst=Tfirst->next;
        Pomlabel=pom->Pomlabel; /* V�b�r hodnot ze z�sobn�ku */
        Pomlabelx=pom->Pomlabelx;
        free(pom);     /* Uvoln�n� prom�nn� */
    }
}

void Generate(int Ginst, string *Gop1, string *Gop2, string *Gresult)
{
        trojinsert(Ginst, Gop1, Gop2, Gresult); /* Zapsan� prvku do seznamu */

}
