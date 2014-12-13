/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "vyraz.h"

int sp=0;           /*stack pointer zasobniku*/
int aktiv;          /*pomocna promenna pro aktivni prvek na zasobniku*/
int loadid=0;       /*pomocna promenna pro zjisteni zda se nacetl identifikator*/
int redukpom;       /*pomocna promenna pro urceni co se ma redukovat na zasobniku*/
int redukid=0;      /*pomocna promenna pro zjisteni zda se zredukoval identifikator*/
int redukzavor=0;   /*pomocna promenna pro zjisteni zda se zredukovala prava zavorka*/
int countlevz=0;    /*promenna pro pocitani levych zavorek ve vyrazu*/
int countpravz=0;   /*promenna pro pocitani praych zavorek ve vyrazu*/
int t;              /*pomocna promenna pro ulozeni tokenu*/
int ptstack[1000];  /*zasobnik pomoci pole*/
int ptable[14][14]; /*precedencni tabulka pomoci dvourozmerneho pole*/
int z;              /*pomocna promenna pro cteni prvku z textoveho souboru*/
int i;              /*pomocna promenna pro cyklus for*/
int j;              /*pomocna promenna pro cyklus for*/
int op=-1;          /*pomocna promenna pro zjisteni zda se redukuje operator*/
int countE1=0;      /*promenna pro pocitani zredukovanych identifikatoru*/
int countE2=0;      /*promenna pro pocitani zredukovanych operaci s identifikatory*/
int countE3=0;      /*promenna pro pocitani zredukovanych vysledku z operaci s identifikatory*/
int spE1=0;         /*stack pointer pro promennou E1*/
int spE2=0;         /*stack pointer pro promennou E1*/
int spE3=0;         /*stack pointer pro promennou E2*/
int E1=123;         /*pridani konstanty do promenne E1*/
int E2=1234;        /*pridani konstanty do promenne E2*/
int E3=12345;       /*pridani konstanty do promenne E3*/
int zarazka=-1;     /*promena pro vlozeni zarazky na zasobnik*/

spom *spom1;        /*struktury pro ulozeni pomocnych vysledku...*/
spom *spom2;
spom *spom3;
spom *spom4;
spom *spom5;        /*...struktury pro ulozeni pomocnych vysledku*/

pomv *pomv1;        /*struktury pro ulozeni vysledku...*/
pomv *pomv2;
pomv *pomv3;        /*...struktury pro ulozeni vysledku*/

FILE *ptabletxt;    /*promenna pro praci s textovym souborem*/

/*fce vyraz je volana pri detekci libovolneho vyrazu v kodu*/
/*fce vyraz nasledne zredukuje na jedinny vysledek a vraci nazev prmenne, ve ktere je hodnota vysledku, a take vrac� jej� typ*/
/*fce v prubehu vola fci, ktera generuje 3 adresny kod pro vypocet vyrazu*/
pomv *VYRAZ(tGlobSymbolTable *ST,Tridic *ridic, int druh, int *konstanta){


    countlevz=0;
    countpravz=0;

    z=0;
    i=0;
    j=0;
    int konst=0;
    int tpom;
    int pombool=0;

    spom1 = (spom*) malloc(sizeof(spom));
    spom2 = (spom*) malloc(sizeof(spom));
    spom3 = (spom*) malloc(sizeof(spom));
    spom4 = (spom*) malloc(sizeof(spom));
    spom5 = (spom*) malloc(sizeof(spom));

    strInit(&(spom1->nazev));
    strInit(&(spom2->nazev));
    strInit(&(spom3->nazev));
    strInit(&(spom4->nazev));
    strInit(&(spom5->nazev));

    strAddChar(&(spom1->nazev),'.');
    strAddChar(&(spom2->nazev),'.');
    strAddChar(&(spom3->nazev),'.');
    strAddChar(&(spom4->nazev),'.');
    strAddChar(&(spom5->nazev),'.');


    pomv1 = (pomv*) malloc(sizeof(pomv));
    pomv2 = (pomv*) malloc(sizeof(pomv));
    pomv3 = (pomv*) malloc(sizeof(pomv));

    strInit(&(pomv1->nazev));
    strInit(&(pomv2->nazev));
    strInit(&(pomv3->nazev));

    strAddChar(&(pomv1->nazev),'N');
    strAddChar(&(pomv2->nazev),'N');
    strAddChar(&(pomv3->nazev),'N');



    string tec;
    strInit(&tec);
    strAddChar(&tec,'.');

    ptabletxt = fopen("ptable.txt", "r");

    while ((z = fgetc(ptabletxt)) != EOF){
      z=z-48;
      if (z>0)
      {
          ptable[i][j]=z;
          j++;
      }
      else
        {
            i++;
            j=0;
        }
    }
    fclose(ptabletxt);


    ptstack[0]=TP_DOLL;
    switch (ridic->token){
        case TP_RBRA:
        {
            error(ST,SYN_ERR,ridic);
        }
        break;
        case TP_SEM:
        {
            error(ST,SYN_ERR,ridic);
        }
        break;
        case KEY_END:
        {
            error(ST,SYN_ERR,ridic);
        }
        break;
        case KEY_DO:
        {
            error(ST,SYN_ERR,ridic);
        }
        break;
        case KEY_THEN:
        {
            error(ST,SYN_ERR,ridic);
        }
        break;
    }
    t=ridic->token;

    if (t == KEY_TRUE || t == KEY_FALSE){
        strCopyString(&(pomv1->nazev),&(ridic->attr_token));
        pomv1->type=BOOLEAN;
        gtoken(ridic);
        printf("nazev konecny %s\n",strGetStr(&(pomv1->nazev)));
    printf("typ konecny %i\n",pomv1->type);
        *konstanta=1;

        return pomv1;
    }

    if ((t >= TP_MUL) && (t <= TP_NEQU)){
        error(ST,SYN_ERR,ridic);
    }else
    if (t == TP_LBRA){
        ptstack[1]=zarazka;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        countlevz++;
    }else
    if(t == TP_IDENT){
        ptstack[1]=zarazka;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);

    }
    if (t >= TP_INT && t <= TP_REAL){
        ptstack[1]=zarazka;
        ptstack[2]=TP_IDENT;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        spom1->type=t;
        *konstanta=1;
    }

    if (t == TP_STRING){
        ptstack[1]=zarazka;
        ptstack[2]=TP_IDENT;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        spom1->type=t;
        *konstanta=1;
    }

    while ((t=gtoken(ridic))!=TP_SEM && t!= KEY_END && t!= KEY_DO && t!= KEY_THEN && t!= TP_COMMA){
        if (pombool == 1 && t!= TP_RBRA){
            error(ST,SYN_ERR,ridic);
        }

        if (t == KEY_TRUE || t == KEY_FALSE){
            strCopyString(&(pomv1->nazev),&(ridic->attr_token));
            pomv1->type=BOOLEAN;
            pombool=1;
        }

        if ((t >= TP_INT && t <= TP_REAL) || t == TP_STRING){
            tpom=t;
            t=TP_IDENT;
            konst=1;
        }
        if (t == TP_IDENT){

            if (strCmpString(&(spom1->nazev),&tec) == 0){
                strCopyString(&(spom1->nazev),&ridic->attr_token);
                if (konst == 1){
                    spom1->type=tpom;
                    konst=0;
                }else{
                    spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                }
            }else{
                if (strCmpString(&(spom2->nazev),&tec) == 0){
                    strCopyString(&(spom2->nazev),&ridic->attr_token);
                    if (konst == 1){
                        spom2->type=tpom;
                        konst=0;
                    }else{
                        spom2->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                    }
                }else{
                    if (strCmpString(&(spom3->nazev),&tec) == 0){
                        strCopyString(&(spom3->nazev),&ridic->attr_token);
                        if (konst == 1){
                            spom3->type=tpom;
                            konst=0;
                        }else{
                            spom3->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                        }
                    }else{
                        if (strCmpString(&(spom4->nazev),&tec) == 0){
                            strCopyString(&(spom4->nazev),&ridic->attr_token);
                            if (konst == 1){
                                spom4->type=tpom;
                                konst=0;
                            }else{
                                spom4->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                            }
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec) == 0){
                                strCopyString(&(spom5->nazev),&ridic->attr_token);
                                if (konst == 1){
                                    spom5->type=tpom;
                                    konst=0;
                                }else{
                                    spom5->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (t == TP_LBRA){
            countlevz++;
        }else
        if (t == TP_RBRA){
            countpravz++;
        }

        if (((t >= TP_MUL) && (t <= TP_NEQU)) && (ptstack[sp] >= TP_MUL && ptstack[sp] <= TP_NEQU)){
            error(ST,SYN_ERR,ridic);
        }
        switch(ptable[ptstack[aktiv]][t]){
            case 1:
            {
                shifting(ST,ridic);
            }
            break;
            case 2:
            {
                *konstanta=0;
                while (ptable[ptstack[aktiv]][t] == 2){
                        reduction(ST,ridic,pomv1,pomv2,pomv3,spom1,spom2,spom3,spom4,spom5,konstanta);
                }
                loadid=1;
                shifting(ST,ridic);
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
                error(ST,SYN_ERR,ridic);
            }
            break;
        }
    }
    if (t == TP_SEM || t == KEY_END || t == KEY_DO || t == KEY_THEN || t == TP_COMMA){

        while (ptable[ptstack[aktiv]][TP_DOLL] == 2){
            reduction(ST,ridic,pomv1,pomv2,pomv3,spom1,spom2,spom3,spom4,spom5,konstanta);
        }
    }

    if  ((countlevz+1 == countpravz) && druh == 1){
        printf("jde o fci \n");
    }else{
        if ((countlevz > countpravz) && druh == 0){
            printf("chyba pico, levych zavorek je vic nez pravych \n");
            error(ST,SYN_ERR,ridic);
        }else{
            if ((countlevz < countpravz) && druh == 0){
                printf("chyba pico, pravych zavorek je vic nez levych \n");
                error(ST,SYN_ERR,ridic);
            }else{
                if  ((countlevz < countpravz) && druh == 1){
                    printf("chyba pico, pravych zavorek je vic nez levych fce\n");
                    error(ST,SYN_ERR,ridic);
                }else{
                    if  ((countlevz > countpravz) && druh == 1){
                        printf("chyba pico, chybi prava zavorka  fce\n");
                        error(ST,SYN_ERR,ridic);
                    }else{
                        if  ((countlevz == countpravz) && druh == 1){
                            printf("chyba pico, chybi prava zavorka \n");
                            error(ST,SYN_ERR,ridic);
                        }else{
                            printf("pocet zavorek souhlasi \n");
                        }
                    }
                }
            }
        }
    }

    if (aktiv == 0 && sp == 2 && (t == TP_SEM || t == KEY_END || t == KEY_DO || t == KEY_THEN || t == TP_COMMA)){
        ptstack[1]=ptstack[2];
        sp=1;
    }
    if ((ptstack[aktiv] == TP_DOLL) && (t == TP_SEM || t == KEY_END || t == KEY_DO || t == KEY_THEN || t == TP_COMMA)){
        printf("Redukce kompletni \n");
    }

    if (strCmpString(&(spom1->nazev),&tec) != 0){
        pomv1->type=spom1->type;
        strCopyString(&(pomv1->nazev),&(spom1->nazev));
        strCopyString(&(spom1->nazev),&tec);
    }

    printf("nazev konecny %s\n",strGetStr(&(pomv1->nazev)));
    printf("typ konecny %i\n",pomv1->type);

    return pomv1;
}

void reduction(tGlobSymbolTable *ST,Tridic *ridic, pomv *pomv1, pomv *pomv2, pomv *pomv3, spom *spom1, spom *spom2, spom *spom3, spom *spom4, spom *spom5, int *konstanta){

    string a;
    string b;
    string v1;
    string v2;
    string v3;
    string v4;
    string c;
    string tec;

    strInit(&c);
    strAddChar(&c,'N');

    strInit(&tec);
    strAddChar(&tec,'.');

    if ((ptstack[sp] >= TP_MUL && ptstack[sp] <= TP_NEQU) && (t == TP_SEM || t == KEY_END || t == KEY_DO || t == KEY_THEN || t == TP_COMMA)){
        error(NULL,SYN_ERR,NULL);
    }

    redukpom=sp;
    while (ptstack[redukpom]!= zarazka){
        if (ptstack[redukpom] >= TP_MUL && ptstack[redukpom] <= TP_NEQU){
            switch (ptstack[redukpom]){
                case 0: op=TP_MUL;
                break;
                case 1: op=TP_MOD;
                break;
                case 2: op=TP_PLUS;
                break;
                case 3: op=TP_MINUS;
                break;
                case 4: op=TP_LESS;
                break;
                case 5: op=TP_MORE;
                break;
                case 6: op=TP_LESSQ;
                break;
                case 7: op=TP_MOREQ;
                break;
                case 8: op=TP_EQU;
                break;
                case 9: op=TP_NEQU;
                break;
            }
        }

        if (ptstack[redukpom] == E1){
            countE1++;
            spE1=redukpom;
        }

        if (ptstack[redukpom] == E2){
            countE2++;
            spE2=redukpom;
        }

        if (ptstack[redukpom] == E3){
            countE3++;
            spE3=redukpom;
        }


        if (op!= -1 && countE1 == 2 && countE2 == 0){

            generateVariable(&a);
            generateVariable(&b);
            if (strCmpString(&(pomv1->nazev),&c) == 0){
                generateVariable(&v1);
                strCopyString(&(pomv1->nazev),&v1);
                if (strCmpString(&(spom3->nazev),&tec) == 0){
                    pomv1->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                    Generate(op,&(spom1->nazev),&(spom2->nazev),&v1);
                    strCopyString(&(spom1->nazev),&tec);
                    strCopyString(&(spom2->nazev),&tec);
                }else{
                    if(strCmpString(&(spom4->nazev),&tec) == 0){
                        pomv1->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                        Generate(op,&(spom2->nazev),&(spom3->nazev),&v1);
                        strCopyString(&(spom2->nazev),&tec);
                        strCopyString(&(spom3->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom5->nazev),&tec) == 0){
                            pomv1->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                            Generate(op,&(spom3->nazev),&(spom4->nazev),&v1);
                            strCopyString(&(spom3->nazev),&tec);
                            strCopyString(&(spom4->nazev),&tec);
                        }else{
                            pomv1->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                            Generate(op,&(spom4->nazev),&(spom5->nazev),&v1);
                            strCopyString(&(spom4->nazev),&tec);
                            strCopyString(&(spom5->nazev),&tec);
                        }
                    }
                }

                spE1=0;
                spE2=0;
                spE3=0;
            }else{
                if (strCmpString(&(pomv2->nazev),&c) == 0){
                    generateVariable(&v2);
                    strCopyString(&(pomv2->nazev),&v2);
                    if (strCmpString(&(spom3->nazev),&tec) == 0){
                        pomv2->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                        Generate(op,&(spom1->nazev),&(spom2->nazev),&v2);
                        strCopyString(&(spom1->nazev),&tec);
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec) == 0){
                            pomv2->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                            Generate(op,&(spom2->nazev),&(spom3->nazev),&v2);
                            strCopyString(&(spom2->nazev),&tec);
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec) == 0){
                                pomv2->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                                Generate(op,&(spom3->nazev),&(spom4->nazev),&v2);
                                strCopyString(&(spom3->nazev),&tec);
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv2->type=typecontrol(ST,ridic,op,spom4->type,spom5->type);
                                Generate(op,&(spom4->nazev),&(spom5->nazev),&v2);
                            }
                        }
                    }
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }else{
                    if (strCmpString(&(pomv3->nazev),&c) == 0){
                        generateVariable(&v3);
                        strCopyString(&(pomv3->nazev),&v3);
                        if (strCmpString(&(spom3->nazev),&tec) == 0){
                            pomv3->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                            Generate(op,&(spom1->nazev),&(spom2->nazev),&v3);
                            strCopyString(&(spom1->nazev),&tec);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec) == 0){
                                pomv3->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                                Generate(op,&(spom2->nazev),&(spom3->nazev),&v3);
                                strCopyString(&(spom2->nazev),&tec);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if (strCmpString(&(spom5->nazev),&tec) == 0){
                                    pomv3->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                                    Generate(op,&(spom3->nazev),&(spom4->nazev),&v3);
                                    strCopyString(&(spom3->nazev),&tec);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv3->type=typecontrol(ST,ridic,op,spom4->type,spom5->type);
                                    Generate(op,&(spom4->nazev),&(spom5->nazev),&v3);
                                    strCopyString(&(spom4->nazev),&tec);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                        spE1=0;
                        spE2=0;
                        spE3=0;
                    }
                }
            }
        }
        if (op!= -1 && countE1 == 0 && countE2 == 2){
            if (strCmpString(&(pomv3->nazev),&c) == 0){
                generateVariable(&v3);
                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                Generate(op,&(pomv1->nazev),&(pomv2->nazev),&v3);
                strCopyString(&(pomv1->nazev),&v3);
                strCopyString(&(pomv2->nazev),&c);
                spE1=0;
                spE2=0;
                spE3=0;
            }else{
                generateVariable(&v4);
                pomv2->type=typecontrol(ST,ridic,op,pomv2->type,pomv3->type);
                Generate(op,&(pomv2->nazev),&(pomv3->nazev),&v4);
                strCopyString(&(pomv2->nazev),&v4);
                strCopyString(&(pomv3->nazev),&c);
                spE1=0;
                spE2=0;
                spE3=0;
            }


        }

        if (op!= -1 && countE1 == 1 && countE2 == 1){
            generateVariable(&a);
            if (strCmpString(&(pomv3->nazev),&c) == 0){
                generateVariable(&v2);
                if (spE1>spE2){
                    if (strCmpString(&(spom2->nazev),&tec) == 0){
                        pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom1->type);
                        Generate(op,&(pomv1->nazev),&(spom1->nazev),&v2);
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec) == 0){
                            pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom2->type);
                            Generate(op,&(pomv1->nazev),&(spom2->nazev),&v2);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec) == 0){
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom3->type);
                                Generate(op,&(pomv1->nazev),&(spom3->nazev),&v2);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec) == 0){
                                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom4->type);
                                    Generate(op,&(pomv1->nazev),&(spom4->nazev),&v2);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom5->type);
                                    Generate(op,&(pomv1->nazev),&(spom5->nazev),&v2);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }else{
                    if (strCmpString(&(spom2->nazev),&tec) == 0){
                        pomv1->type=typecontrol(ST,ridic,op,spom1->type,pomv1->type);
                        Generate(op,&(spom1->nazev),&(pomv1->nazev),&v2);
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec) == 0){
                            pomv1->type=typecontrol(ST,ridic,op,spom2->type,pomv1->type);
                            Generate(op,&(spom2->nazev),&(pomv1->nazev),&v2);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec) == 0){
                                pomv1->type=typecontrol(ST,ridic,op,spom3->type,pomv1->type);
                                Generate(op,&(spom3->nazev),&(pomv1->nazev),&v2);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec) == 0){
                                    pomv1->type=typecontrol(ST,ridic,op,spom4->type,pomv1->type);
                                    Generate(op,&(spom4->nazev),&(pomv1->nazev),&v2);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv1->type=typecontrol(ST,ridic,op,spom5->type,pomv1->type);
                                    Generate(op,&(spom5->nazev),&(pomv1->nazev),&v2);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }
                strCopyString(&(pomv1->nazev),&v2);
            }else{
                generateVariable(&v3);
                if (spE1>spE2){
                    if (strCmpString(&(spom2->nazev),&tec) == 0){
                        pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom1->type);
                        Generate(op,&(pomv2->nazev),&(spom1->nazev),&v3);
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec) == 0){
                            pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom2->type);
                            Generate(op,&(pomv2->nazev),&(spom2->nazev),&v3);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec) == 0){
                                pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom3->type);
                                Generate(op,&(pomv2->nazev),&(spom3->nazev),&v3);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec) == 0){
                                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom4->type);
                                    Generate(op,&(pomv2->nazev),&(spom4->nazev),&v3);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom5->type);
                                    Generate(op,&(pomv2->nazev),&(spom5->nazev),&v3);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }else{
                    if (strCmpString(&(spom2->nazev),&tec) == 0){
                        pomv2->type=typecontrol(ST,ridic,op,spom1->type,pomv2->type);
                        Generate(op,&(spom1->nazev),&(pomv2->nazev),&v3);
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec) == 0){
                            pomv2->type=typecontrol(ST,ridic,op,spom2->type,pomv2->type);
                            Generate(op,&(spom2->nazev),&(pomv2->nazev),&v3);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec) == 0){
                                pomv2->type=typecontrol(ST,ridic,op,spom3->type,pomv2->type);
                                Generate(op,&(spom3->nazev),&(pomv2->nazev),&v3);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec) == 0){
                                    pomv2->type=typecontrol(ST,ridic,op,spom4->type,pomv2->type);
                                    Generate(op,&(spom4->nazev),&(pomv2->nazev),&v3);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv2->type=typecontrol(ST,ridic,op,spom5->type,pomv2->type);
                                    Generate(op,&(spom5->nazev),&(pomv2->nazev),&v3);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }
                strCopyString(&(pomv2->nazev),&v3);
            }

        }

        if (op!= -1 && countE1 == 1 && countE3 == 1){
            generateVariable(&a);
            generateVariable(&v2);
            if (spE1>spE3){
                if (strCmpString(&(spom2->nazev),&tec) == 0){
                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom1->type);
                    Generate(op,&(pomv1->nazev),&(spom1->nazev),&v2);
                    strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec) == 0){
                        pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom2->type);
                        Generate(op,&(pomv1->nazev),&(spom2->nazev),&v2);
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec) == 0){
                            pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom3->type);
                            Generate(op,&(pomv1->nazev),&(spom3->nazev),&v2);
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec) == 0){
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom4->type);
                                Generate(op,&(pomv1->nazev),&(spom4->nazev),&v2);
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom5->type);
                                Generate(op,&(pomv1->nazev),&(spom5->nazev),&v2);
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                }
                spE1=0;
                spE2=0;
                spE3=0;
            }else{
                if (strCmpString(&(spom2->nazev),&tec) == 0){
                    pomv1->type=typecontrol(ST,ridic,op,spom1->type,pomv1->type);
                    Generate(op,&(spom1->nazev),&(pomv1->nazev),&v2);
                    strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec) == 0){
                        pomv1->type=typecontrol(ST,ridic,op,spom2->type,pomv1->type);
                        Generate(op,&(spom2->nazev),&(pomv1->nazev),&v2);
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec) == 0){
                            pomv1->type=typecontrol(ST,ridic,op,spom3->type,pomv1->type);
                            Generate(op,&(spom3->nazev),&(pomv1->nazev),&v2);
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec) == 0){
                                pomv1->type=typecontrol(ST,ridic,op,spom4->type,pomv1->type);
                                Generate(op,&(spom4->nazev),&(pomv1->nazev),&v2);
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv1->type=typecontrol(ST,ridic,op,spom5->type,pomv1->type);
                                Generate(op,&(spom5->nazev),&(pomv1->nazev),&v2);
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                }
                spE1=0;
                spE2=0;
                spE3=0;
            }
            strCopyString(&(pomv1->nazev),&v2);
        }

        if (op!= -1 && countE2 == 1 && countE3 == 1){
            if (strCmpString(&(pomv3->nazev),&c) == 0){
                generateVariable(&v3);
                if (spE2>spE3){
                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                    Generate(op,&(pomv1->nazev),&(pomv2->nazev),&v3);
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }else{
                    pomv1->type=typecontrol(ST,ridic,op,pomv2->type,pomv1->type);
                    Generate(op,&(pomv2->nazev),&(pomv1->nazev),&v3);
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }
                strCopyString(&(pomv1->nazev),&v3);
                strCopyString(&(pomv2->nazev),&c);
            }else{
                generateVariable(&v4);
                if (spE2>spE3){
                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,pomv3->type);
                    Generate(op,&(pomv2->nazev),&(pomv3->nazev),&v4);
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }else{
                    pomv2->type=typecontrol(ST,ridic,op,pomv3->type,pomv2->type);
                    Generate(op,&(pomv3->nazev),&(pomv2->nazev),&v4);
                    spE1=0;
                    spE2=0;
                    spE3=0;
                }
                strCopyString(&(pomv2->nazev),&v4);
                strCopyString(&(pomv3->nazev),&c);
            }
        }

        if (op!= -1 && countE3 == 2){
            if (strCmpString(&(pomv3->nazev),&c) == 0){
                generateVariable(&v3);
                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                Generate(op,&(pomv1->nazev),&(pomv2->nazev),&v3);
                spE1=0;
                spE2=0;
                spE3=0;
                strCopyString(&(pomv1->nazev),&v3);
                strCopyString(&(pomv2->nazev),&c);
            }
        }

        if (ptstack[redukpom]==TP_IDENT){
            redukid=1;
        }
        if (ptstack[redukpom]==TP_RBRA){
            redukzavor=1;
        }
        redukpom--;
    }
    sp=redukpom;
    if (redukid == 1 || redukzavor == 1){
        if (redukid == 1){
            ptstack[sp]=zarazka;
            sp++;
            if (countE1 == 1 && op == -1){
                ptstack[sp]=E1;
                countE3=0;
                countE2=0;
                countE1=0;
            }else{
                if (countE1 == 0 && op == -1 && t!= 11){
                    ptstack[sp]=E1;
                    countE3=0;
                    countE2=0;
                    countE1=0;
                }else{
                    if (countE1 == 0 && op == -1 && t == 11){
                        sp--;
                        ptstack[sp]=E1;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                    }else{
                        if (countE1 == 2 && op!= -1){
                            ptstack[sp]=E2;
                            countE3=0;
                            countE2=0;
                            countE1=0;
                            op=-1;
                        }else{
                            if (countE1 == 1 && countE2 == 1 && op!= -1){
                                ptstack[sp]=E2;
                                countE3=0;
                                countE2=0;
                                countE1=0;
                                op=-1;
                            }else{
                                if (countE2 == 2 && op!= -1){
                                    ptstack[sp]=E3;
                                    countE3=0;
                                    countE2=0;
                                    countE1=0;
                                    op=-1;
                                }else{
                                    if (countE1 == 0 && op!= -1){
                                        ptstack[sp]=E1;
                                        countE3=0;
                                        countE2=0;
                                        countE1=0;
                                        op=-1;
                                    }else{
                                        if (countE2 == 0 && op!= -1){
                                            ptstack[sp]=E2;
                                            countE3=0;
                                            countE2=0;
                                            countE1=0;
                                            op=-1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            redukid=0;
            aktiv=redukpom-1;
        }else
        if (redukzavor == 1 && (t == TP_SEM || t == KEY_END || t == KEY_DO || t == KEY_THEN || t == TP_COMMA)){
            if (countE1 == 1 && op== -1){
                ptstack[sp]=E1;
                countE3=0;
                countE2=0;
                countE1=0;
                *konstanta=1;
            }else{
                if (countE2 == 1 && op== -1 && countE3 == 0){
                    ptstack[sp]=E2;
                    countE3=0;
                    countE2=0;
                    countE1=0;
                }else{
                    if (countE1 == 2 && op!= -1){
                        ptstack[sp]=E2;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                        op=-1;
                    }else{
                        if (countE1 == 1 && countE2 == 1 && op!= -1){
                            ptstack[sp]=E2;
                            countE3=0;
                            countE2=0;
                            countE1=0;
                            op=-1;
                        }else{
                            if (countE2 == 2 && op!= -1){
                                ptstack[sp]=E3;
                                countE3=0;
                                countE2=0;
                                countE1=0;
                                op=-1;
                            }else{
                                if (countE3 == 1 && op == -1){
                                    ptstack[sp]=E3;
                                    countE3=0;
                                    countE2=0;
                                    countE1=0;
                                    op=-1;
                                }else{
                                    if (countE3 == 1 && op!= -1){
                                        ptstack[sp]=E3;
                                        countE3=0;
                                        countE2=0;
                                        countE1=0;
                                        op=-1;
                                    }else{
                                        if (countE3 == 2 && op!= -1){
                                            ptstack[sp]=E3;
                                            countE3=0;
                                            countE2=0;
                                            countE1=0;
                                            op=-1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            aktiv=redukpom-1;
        }else
        if (t!= TP_RBRA){
            aktiv=redukpom-1;
            if (countE1 == 1 && op == -1){
                ptstack[redukpom+1]=E1;
                countE3=0;
                countE2=0;
                countE1=0;
            }else{
                if (countE2 == 1 && op == -1 && ptstack[aktiv]!= TP_DOLL){
                    ptstack[redukpom+1]=E2;
                    countE3=0;
                    countE2=0;
                    countE1=0;
                }else{
                    if (countE3 == 1 && op == -1){
                        ptstack[redukpom+1]=E3;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                    }else{
                        ptstack[redukpom+1]=E2;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                    }
                }
            }
            sp=sp+1;
            redukzavor=0;
        }
        else{
            if (countE1 == 1 && op == -1){
                ptstack[sp]=E1;
                countE3=0;
                countE2=0;
                countE1=0;
            }else{
                if (countE1 == 0 && op == -1){
                    ptstack[sp]=E2;
                    countE3=0;
                    countE2=0;
                    countE1=0;
                }else{
                    if (countE1 == 2 && op!= -1){
                        ptstack[sp]=E2;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                        op=-1;
                    }else{
                        if (countE1 == 1 && countE2 == 1 && op!= -1){
                            ptstack[sp]=E2;
                            countE3=0;
                            countE2=0;
                            countE1=0;
                            op=-1;
                        }else{
                            if (countE2 == 2 && op!= -1){
                                ptstack[sp]=E3;
                                countE3=0;
                                countE2=0;
                                countE1=0;
                                op=-1;
                            }else{
                                if (countE2 == 2 && op!= -1 && t!= 11){
                                    ptstack[redukpom+1]=E3;
                                    countE3=0;
                                    countE2=0;
                                    countE1=0;
                                    op=-1;
                                    sp++;
                                }else{
                                    if (countE2 == 2 && op!= -1 && t == 11){
                                        ptstack[sp]=E3;
                                        countE3=0;
                                        countE2=0;
                                        countE1=0;
                                        op=-1;
                                    }else{
                                        if (countE3 == 2 && op!= -1 && t!= 11){
                                            ptstack[redukpom+1]=E3;
                                            countE3=0;
                                            countE2=0;
                                            countE1=0;
                                            op=-1;
                                            sp++;
                                        }else{
                                            if (countE3 == 2 && op!= -1 && t == 11){
                                                ptstack[sp]=E3;
                                                countE3=0;
                                                countE2=0;
                                                countE1=0;
                                                op=-1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            aktiv=redukpom-1;
        }
    }else {
        if (countE1 == 1 && op == -1){
            ptstack[sp]=E1;
            countE3=0;
            countE2=0;
            countE1=0;
        }else{
            if (countE1 == 0 && op == -1 && countE2 == 0){
                    ptstack[sp]=E1;
                    countE3=0;
                    countE2=0;
                    countE1=0;
                }else{
                    if (countE2 == 1 && op == -1 && countE1 == 0){
                        ptstack[sp]=E2;
                        countE3=0;
                        countE2=0;
                        countE1=0;
                        op=-1;
                    }else{
                        if (countE1 == 2 && op!= -1 && t!= 11){
                            ptstack[redukpom+1]=E2;
                            countE3=0;
                            countE2=0;
                            countE1=0;
                            op=-1;
                            sp++;
                        }else{
                            if (countE1 == 2 && op!= -1 && t == 11){
                                ptstack[sp]=E2;
                                countE3=0;
                                countE2=0;
                                countE1=0;
                                op=-1;
                            }else{
                                if (countE1 == 1 && countE2 == 1 && op!= -1){
                                    ptstack[sp]=E2;
                                    countE3=0;
                                    countE2=0;
                                    countE1=0;
                                    op=-1;
                                }else{
                                    if (countE2 == 2 && op!= -1 && t!= 11){
                                        ptstack[redukpom+1]=E3;
                                        countE3=0;
                                        countE2=0;
                                        countE1=0;
                                        op=-1;
                                        sp++;
                                    }else{
                                        if (countE2 == 2 && op!= -1 && t == 11){
                                            ptstack[sp]=E3;
                                            countE3=0;
                                            countE2=0;
                                            countE1=0;
                                            op=-1;
                                        }else{
                                            if (countE3 == 2 && op!= -1 && t!= 11){
                                                ptstack[redukpom+1]=E3;
                                                countE3=0;
                                                countE2=0;
                                                countE1=0;
                                                op=-1;
                                                sp++;
                                            }else{
                                                if (countE3 == 2 && op!= -1 && t == 11){
                                                    ptstack[sp]=E3;
                                                    countE3=0;
                                                    countE2=0;
                                                    countE1=0;
                                                    op=-1;
                                                }else{
                                                    ptstack[sp]=E3;
                                                    countE3=0;
                                                    countE2=0;
                                                    countE1=0;
                                                    op=-1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        aktiv=redukpom-1;
    }
    i=0;
    if (ptstack[aktiv] == TP_DOLL && t!= TP_SEM && t!= KEY_END && t!= KEY_DO && t!= KEY_THEN && t!= TP_COMMA && ptstack[1]!= zarazka){
        ptstack[2]=ptstack[1];
        ptstack[1]=zarazka;
        sp++;
    }
    return;
}

void shifting(tGlobSymbolTable *ST,Tridic *ridic){

    if (((t >= TP_MUL)&&(t <= TP_NEQU))&&(loadid == 1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
        loadid=0;
    }else
    if (((t >= TP_MUL)&&(t <= TP_NEQU)) && (loadid == 0)){
        error(NULL,SYN_ERR,NULL);
    }else
    if ((t == TP_RBRA) && (loadid == 1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if ((t == TP_RBRA) && (loadid == 0)){
        error(NULL,SYN_ERR,NULL);
    }else
    if (t == TP_LBRA){
        sp++;
        ptstack[sp]=zarazka;
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if (t == TP_IDENT){
        sp++;
        ptstack[sp]=zarazka;
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
        loadid=1;
    }
    return;
}

int typecontrol(tGlobSymbolTable *ST,Tridic *ridic, int op, int oper1, int oper2){

    switch (op){
        case 0:
            {
                if (oper1 == TP_INT && oper2 == TP_INT){
                    return TP_INT;
                }else{
                    if (oper1 == TP_REAL && oper2 == TP_REAL){
                        return TP_REAL;
                    }else{
                        if (oper1 == TP_INT && oper2 == TP_REAL){
                            return TP_REAL;
                        }else{
                            if (oper1 == TP_REAL && oper2 == TP_INT){
                                return TP_REAL;
                            }else{
                                error(ST,SEM_ERR,ridic);
                            }
                        }
                    }
                }
           }
        break;
        case 1:
            {
                if (oper1 == TP_INT && oper2 == TP_INT){
                    return TP_REAL;
                }else{
                    if (oper1 == TP_REAL && oper2 == TP_REAL){
                        return TP_REAL;
                    }else{
                        if (oper1 == TP_INT && oper2 == TP_REAL){
                            return TP_REAL;
                        }else{
                            if (oper1 == TP_REAL && oper2 == TP_INT){
                                return TP_REAL;
                            }else{
                                error(ST,SEM_ERR,ridic);
                            }
                        }
                    }
                }
            }
        break;
        case 2:
            {
                if (oper1 == TP_INT && oper2 == TP_INT){
                    return TP_INT;
                }else{
                    if (oper1 == TP_REAL && oper2 == TP_REAL){
                        return TP_REAL;
                    }else{
                        if (oper1 == TP_STRING && oper2 == TP_STRING){
                            return TP_STRING;
                        }else{
                            if (oper1 == TP_INT && oper2 == TP_REAL){
                                return TP_REAL;
                            }else{
                                if (oper1 == TP_REAL && oper2 == TP_INT){
                                    return TP_REAL;
                                }else{
                                    error(ST,SEM_ERR,ridic);
                                }
                            }
                        }
                    }
                }
            }
        break;
        case 3:
            {
                if (oper1 == TP_INT && oper2 == TP_INT){
                    return TP_INT;
                }else{
                    if (oper1 == TP_REAL && oper2 == TP_REAL){
                        return TP_REAL;
                    }else{
                        if (oper1 == TP_INT && oper2 == TP_REAL){
                            return TP_REAL;
                        }else{
                            if (oper1 == TP_REAL && oper2 == TP_INT){
                                return TP_REAL;
                            }else{
                                error(ST,SEM_ERR,ridic);
                            }
                        }
                    }
                }
            }
        break;
        default:
            {
                if (oper1 == TP_INT && oper2 == TP_INT){
                    return BOOLEAN;
                }else{
                    if (oper1 == TP_REAL && oper2 == TP_REAL){
                        return BOOLEAN;
                    }else{
                        if (oper1 == BOOLEAN && oper2 == BOOLEAN){
                            return BOOLEAN;
                        }else{
                            if (oper1 == TP_STRING && oper2 == TP_STRING){
                                return BOOLEAN;
                            }else{
                                error(ST,SEM_ERR,ridic);
                            }
                        }
                    }
                }
            }
        break;
    }
    return 0;
}


/*
ZADANE FCE LENGTH COPY FIND SORT
jak rozlisit identifikator od zadanych fci? mara vraci ve string....asi se ptat na string

*/




