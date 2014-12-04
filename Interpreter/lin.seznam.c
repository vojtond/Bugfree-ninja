#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lin.seznam.h"

int pozice;
int Pomlabel=0;
int Pomlabelx=0;

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

    if (pom->data.inst == 21){
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        //pom->data.pozice=trojfind()Pomlabel;
    }

    if (pom->data.inst == 20){
        Pomlabel++;
        pom->data.label=Pomlabel;
    }

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
}


void trojvypis(){
    tTroj *pom;
    pom=Trfirst;
    while (pom!=NULL){
        printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str, pom->data.pozice, pom->data.label);
        pom=pom->next;
    }
}


void trojfind(string o){
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
            printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str, pom->data.pozice, pom->data.label);
            break;
        }
        pom=pom->next;
    }
}
/////* ************************* *///////////
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
