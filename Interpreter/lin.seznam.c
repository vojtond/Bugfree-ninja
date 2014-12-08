#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "lin.seznam.h"

int pozice;
int Pomlabel=0;
int Pomlabelx=0;
int ifbeg=0;

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

    if (pom->data.inst == 40){
        Pomlabel++;
        pom->data.label=Pomlabel;
        /*ifbeg--;
        if(ifbeg>0)
        {
            Pomlabelx-=2;
            Pomlabel-=2;
        }*/
    }

if (pom->data.inst == 48){
        Pomlabel++;
        pom->data.label=Pomlabel;
        pom->data.inst=40;
        /*ifbeg--;
        if(ifbeg>0)
        {
            if(ifbeg>1) Pomlabel--;
            Pomlabelx-=3;
            Pomlabel-=4;
        }*/
    }

    if (pom->data.inst == 41){
        /*if(ifbeg>0)
        {   if(ifbeg>1) Pomlabel++;
            Pomlabelx++;
            Pomlabel++;
        }*/
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);

        //ifbeg++;
    }
/* ***************** WHILE_BEGIN **************** */
    if (pom->data.inst == 49){
        if(ifbeg>0)
        {
            Pomlabelx++;
        }
        ifbeg++;
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        pom->data.inst=41;
    }
/* ***************** WHILE_END **************** */
    if (pom->data.inst == 42){
        Pomlabelx++;
        strInit(&pom->data.op1);
        generatelabel(pom);
        ifbeg--;
        if(ifbeg>0)
        {
            Pomlabelx-=3;
        }

    }
/* ***************** WHILE_BEGIN_LAB **************** */
    if (pom->data.inst == 43){
        if(ifbeg>0)
        {
            Pomlabel++;
        }
        Pomlabel++;
        pom->data.label=Pomlabel+1;
        pom->data.inst=40;
    }
/* ***************** WHILE_END_LAB **************** */
     if (pom->data.inst == 44){
        Pomlabel++;
        pom->data.label=Pomlabel-1;
        if(ifbeg>0)
        {
            Pomlabel-=3;
        }
        pom->data.inst=40;
    }

    if (pom->data.inst == 45){
        /*if(ifbeg>0)
        {
            Pomlabelx+=2;
            Pomlabel+=3;
            ifbeg++;
        }*/
        pom->data.label=Pomlabel;
        pom->data.inst=40;
        int pompoz = pom->data.pozice-1;
        trojfindpoz(pompoz);

    }
    if (pom->data.inst == 46){
        pom->data.inst=40;
    }
    if (pom->data.inst == 47){
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
            //printf("%i %s %s %s %i %i\n",pom->data.inst, pom->data.op1.str, pom->data.op2.str, pom->data.result.str, pom->data.pozice, pom->data.label);
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
