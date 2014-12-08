#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lin.seznam.h"

void trojfindpoz(int pozice);
void generatelabel(tTroj *pom);
void PushS();
void PopTopS();

int pozice;
int Pomlabel=0;
int Pomlabelx=0;
int ifelse=0;

void trojinit(){
    Trfirst=NULL;
    Trlast=NULL;

}
void trojinsert(int i, string op1, string op2, string result){
     tTroj *pom;

    pom=(tTroj*) malloc(sizeof(tTroj ));
    pom->data.inst=i;
    pom->data.op1=op1;
    pom->data.op2=op2;
    pom->data.result=result;
    pom->next=NULL;

    if (Trlast!=NULL){
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
/* ***************** IF_END **************** */
    if (pom->data.inst == 41){
        PopTopS();
        Pomlabel++;
        pom->data.label=Pomlabel;
    }
/* ***************** IF_BEGIN **************** */
    if (pom->data.inst == 40){
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        PushS();
        Pomlabel+=4;
        Pomlabelx+=3;
    }
/* ***************** ELSE_BEGIN **************** */
    if (pom->data.inst == 42){
            if (ifelse>0) Pomlabel++;
        ifelse++;
        pom->data.label=Pomlabel;
        int pompoz = pom->data.pozice-1;
        trojfindpoz(pompoz);
        PushS();
        pom->data.inst=40;
    }
/* ***************** ELSE_END **************** */
    if (pom->data.inst == 43){
        ifelse--;
        PopTopS();
        Pomlabel++;
        pom->data.label=Pomlabel;
        pom->data.inst=40;
    }
/* ***************** WHILE_BEGIN **************** */
    if (pom->data.inst == 45){
        Pomlabelx++;
        if (ifelse>0) Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        PushS();
        Pomlabel++;
        Pomlabelx++;
        pom->data.inst=41;
    }

/* ***************** WHILE_BEGIN_LAB **************** */
    if (pom->data.inst == 44){
        if (ifelse>0) Pomlabel++;
        Pomlabel++;
    if (ifelse>0) Pomlabel++;
        pom->data.label=Pomlabel+1;
        pom->data.inst=40;
    }
/* ***************** WHILE_END **************** */
    if (pom->data.inst == 46){
        PopTopS();
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
    }
/* ***************** WHILE_END_LAB **************** */
     if (pom->data.inst == 47){
        Pomlabel++;
        pom->data.label=Pomlabel-1;
        pom->data.inst=40;
    }
/* ***************** FCE_LAB **************** */
    if (pom->data.inst == 48){
        pom->data.inst=40;
    }
/* ***************** FCE_CALL **************** */
    if (pom->data.inst == 49){
        pom->data.inst=43;
    }

}

void trojvypis(){
    tTroj *pom;
    pom=Trfirst;
    while (pom!=NULL){
        printf("%i %s %s %s ",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str);
        if (pom->data.label!=0) printf("->L%i",pom->data.label); printf("\n");
        pom=pom->next;
    }
}

void trojfindpoz(int pozice){
    tTroj *pom;
    pom=Trfirst;
    while (pom!=NULL){
        if (pom->data.pozice == pozice){
                Pomlabelx++;
                strInit(&pom->data.op1);
                generatelabel(pom);
                pom->data.label=0;
                pom->data.inst=42;
            break;
        } pom=pom->next;
    }
}

int trojfindfce(string fce){
    tTroj *pom;
    pom=Trfirst;
    while (pom!=NULL){
        if (pom->data.op1.str == fce.str){
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str, pom->data.pozice, pom->data.label);
            return pom->data.pozice;
            break;
        }
        pom=pom->next;
    }
}

int trojfindlab(string o){
    tTroj *pom;
    pom=Trfirst;

    int vysl=0;
    if ((o.str[3]>='0')&&(o.str[3]<='9')){
    int f=o.str[3];
    f-=48;
    vysl+=100*f;
    }
    else if ((o.str[2]>='0')&&(o.str[2]<='9'))
    {
    int f=o.str[2];
    f-=48;
    vysl+=10*f;
    }
    else if ((o.str[1]>='0')&&(o.str[1]<='9'))
    {
    int f=o.str[1];
    f-=48;
    vysl+=f;
    }

    while ( pom!=NULL ){
        if (pom->data.label == vysl ){
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str, pom->data.pozice, pom->data.label);
            return pom->data.pozice;
            break;
        }
        pom=pom->next;
    }
}
/* ************ GENERATE_LABEL ************* */
void generatelabel(tTroj *pom)
{
    strAddChar(&pom->data.op1,'L');
        if (Pomlabelx>99){
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
        }else if(Pomlabelx>9){
            char z = 48;
            char p = Pomlabelx;
            while (p>9){z++; p-=10;}
            strAddChar(&pom->data.op1,z);
            p=p+48;
            strAddChar(&pom->data.op1,p);
        }else{
        char c=Pomlabelx+48;
        strAddChar(&pom->data.op1,c);
        }
}

void PushS(){
    SKOK *pom;
    pom=(SKOK*) malloc(sizeof(SKOK));
    pom->Pomlabel=Pomlabel;
    pom->Pomlabelx=Pomlabelx;
    pom->next=Tfirst;
    Tfirst=pom;
}
void PopTopS(){
    SKOK *pom;
    if (Tfirst!=NULL){
        pom=Tfirst;
        Tfirst=Tfirst->next;
        Pomlabel=pom->Pomlabel;
        Pomlabelx=pom->Pomlabelx;
        printf("pop:%i,%i",Pomlabel ,Pomlabelx);
        free(pom);
    }

}
