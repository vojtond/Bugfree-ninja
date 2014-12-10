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
int z;
int i;
int j;
int k=0;
int op=-1;
int pocreductions=0;
int i123=0;
int i1234=0;
int i12345=0;
int sp123=0;
int sp1234=0;
int sp12345=0;

spom *spom1;
spom *spom2;
spom *spom3;
spom *spom4;
spom *spom5;

pomv *pomv1;
pomv *pomv2;
pomv *pomv3;

FILE *ptabletxt;


pomv *VYRAZ(tGlobSymbolTable *ST,Tridic *ridic){

    z=0;
    i=0;
    j=0;
    int konst=0;
    int tpom;

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
    if ((t>=TP_MUL)&&(t<=TP_NEQU)){
        printf("chyba pico, nemuzes dat operator jako prvni \n");
        error(ST,SEM_ERR,ridic);
    }else
    if (t==TP_LBRA){
        ptstack[1]=-1;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        countlevz++;
    }else
    if(t==TP_IDENT){
        ptstack[1]=-1;
        ptstack[2]=t;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);

    }
    if (t>=TP_INT && t<=TP_REAL){
        ptstack[1]=-1;
        ptstack[2]=TP_IDENT;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        printf("type %i\n",spom1->type);
        spom1->type=t;
        printf("konst %s\n",strGetStr(&(spom1->nazev)));
        printf("type %i\n",spom1->type);
    }

    if (t==TP_STRING){
        ptstack[1]=-1;
        ptstack[2]=TP_IDENT;
        sp=2;
        aktiv=2;
        loadid=1;
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        printf("type %i\n",spom1->type);
        spom1->type=t;
        printf("konst %s\n",strGetStr(&(spom1->nazev)));
        printf("type %i\n",spom1->type);
    }
    //printf("sdgdf %i \n",ptstack[0]);

    i=0;
    while (i<=sp){
      printf("zasobnik %i\n",ptstack[i]);
      i++;
    }
    //printf("zasobnik %i\n",ptstack[0]);

    while ((t=gtoken(ridic))!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN && t!=TP_COL){
        if ((t>=TP_INT && t<=TP_REAL) || t==TP_STRING){
            tpom=t;
            t=TP_IDENT;
            konst=1;
        }
        if (t==TP_IDENT){

            if (strCmpString(&(spom1->nazev),&tec)==0){
                strCopyString(&(spom1->nazev),&ridic->attr_token);
                if (konst==1){
                    spom1->type=tpom;
                    printf("nazev %s\n",strGetStr(&(spom1->nazev)));
                    printf("typ %i\n",spom1->type);
                    konst=0;
                }else{
                    spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                    printf("nazev %s\n",strGetStr(&(spom1->nazev)));
                    printf("typ %i\n",spom1->type);
                }
            }else{
                if (strCmpString(&(spom2->nazev),&tec)==0){
                    strCopyString(&(spom2->nazev),&ridic->attr_token);
                    if (konst==1){
                        spom2->type=tpom;
                        printf("nazev %s\n",strGetStr(&(spom2->nazev)));
                        printf("typ %i\n",spom2->type);
                        konst=0;
                    }else{
                        spom2->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                        printf("nazev %s\n",strGetStr(&(spom2->nazev)));
                        printf("typ %i\n",spom2->type);
                    }
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        strCopyString(&(spom3->nazev),&ridic->attr_token);
                        if (konst==1){
                            spom3->type=tpom;
                            printf("nazev %s\n",strGetStr(&(spom3->nazev)));
                            printf("typ %i\n",spom3->type);
                            konst=0;
                        }else{
                            spom3->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                            printf("nazev %s\n",strGetStr(&(spom3->nazev)));
                            printf("typ %i\n",spom3->type);
                        }
                    }else{
                        if (strCmpString(&(spom4->nazev),&tec)==0){
                            strCopyString(&(spom4->nazev),&ridic->attr_token);
                            if (konst==1){
                                spom4->type=tpom;
                                printf("nazev %s\n",strGetStr(&(spom4->nazev)));
                                printf("typ %i\n",spom4->type);
                                konst=0;
                            }else{
                                spom4->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                                printf("nazev %s\n",strGetStr(&(spom4->nazev)));
                                printf("typ %i\n",spom4->type);
                            }
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec)==0){
                                strCopyString(&(spom5->nazev),&ridic->attr_token);
                                if (konst==1){
                                    spom5->type=tpom;
                                    printf("nazev %s\n",strGetStr(&(spom5->nazev)));
                                    printf("typ %i\n",spom5->type);
                                    konst=0;
                                }else{
                                    spom5->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                                    printf("nazev %s\n",strGetStr(&(spom5->nazev)));
                                    printf("typ %i\n",spom5->type);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (t==TP_LBRA){
            countlevz++;
        }else
        if (t==TP_RBRA){
            countpravz++;
        }

        if (((t>=TP_MUL)&&(t<=TP_NEQU)) && (ptstack[sp]>=TP_MUL && ptstack[sp]<=TP_NEQU)){
            printf("2 operatory za sebou");
            error(ST,SEM_ERR,ridic);
        }
        switch(ptable[ptstack[aktiv]][t]){
            case 1:
            {
                shifting(ST,ridic);
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
                        reduction(ST,ridic,pomv1,pomv2,pomv3,spom1,spom2,spom3,spom4,spom5);
                }
                loadid=1;
                shifting(ST,ridic);
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
    if (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN || t==TP_COL){
        i=0;
        while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("active %i \n",ptstack[aktiv]);
        printf("token %i \n",t);
        printf("id  %i zavor %i\n",redukid,redukzavor);
        printf("\n");


        while (ptable[ptstack[aktiv]][TP_DOLL]==2){
            reduction(ST,ridic,pomv1,pomv2,pomv3,spom1,spom2,spom3,spom4,spom5);
        }


        i=0;
        while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("active %i \n",ptstack[aktiv]);
        printf("token %i \n",t);
        printf("id  %i zavor %i\n",redukid,redukzavor);
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

    if (aktiv == 0 && sp == 2 && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN || t==TP_COL)){
        ptstack[1]=ptstack[2];
        sp=1;
    }
    if ((ptstack[aktiv]==TP_DOLL)&&(t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN || t==TP_COL)){
        printf("Redukce kompletni \n");
    }
    //if ()

    i=0;
    while (i<=sp){
      printf("zasobnik %i\n",ptstack[i]);
      i++;
    }
    printf("\n");



    if (strCmpString(&(spom1->nazev),&tec) != 0){
        pomv1->type=spom1->type;
        strCopyString(&(pomv1->nazev),&(spom1->nazev));
        strCopyString(&(spom1->nazev),&tec);
    }

    printf("nazev konecny %s\n",strGetStr(&(pomv1->nazev)));
    printf("typ konecny %i\n",pomv1->type);

    printf("idpom1 %s\n",strGetStr(&spom1->nazev));
    printf("idpom2 %s\n",strGetStr(&spom2->nazev));
    printf("idpom3 %s\n",strGetStr(&spom3->nazev));
    printf("idpom4 %s\n",strGetStr(&spom4->nazev));
    printf("idpom5 %s\n",strGetStr(&spom5->nazev));


    return pomv1;
}

void reduction(tGlobSymbolTable *ST,Tridic *ridic, pomv *pomv1, pomv *pomv2, pomv *pomv3, spom *spom1, spom *spom2, spom *spom3, spom *spom4, spom *spom5){

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

    if ((ptstack[sp]>=TP_MUL && ptstack[sp]<=TP_NEQU) && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN || t==TP_COL)){
        printf("chyba pico, blby ukonceni \n");
        error(NULL,SEM_ERR,NULL);
    }

    redukpom=sp;
    while (ptstack[redukpom]!=-1){
        if (ptstack[redukpom]>=TP_MUL && ptstack[redukpom]<=TP_NEQU){
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
            //printf("operator %i \n",op);
        }
        //printf("operator %i \n",op);

        if (ptstack[redukpom]==123){
            i123++;
            sp123=redukpom;
        }

        if (ptstack[redukpom]==1234){
            i1234++;
            sp1234=redukpom;
        }

        if (ptstack[redukpom]==12345){
            i12345++;
            sp12345=redukpom;
        }


        if (op!=-1 && i123==2 && i1234==0){

            printf("prom1 + prom2 = v1 \n");
            generateVariable(&a);
            generateVariable(&b);
            /*printf("%s\n",strGetStr(&(pomv1->nazev)));
            printf("%s\n",strGetStr(&c));
            printf("%i\n",strCmpString(&(pomv1->nazev),&c));*/
            if (strCmpString(&(pomv1->nazev),&c)==0){
                generateVariable(&v1);
                strCopyString(&(pomv1->nazev),&v1);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                if (strCmpString(&(spom3->nazev),&tec)==0){
                    pomv1->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                    printf("typ op1 %i\n",spom1->type);
                    printf("typ op2 %i\n",spom2->type);
                    printf("typ vysledku %i\n",pomv1->type);
                    printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v1));
                    strCopyString(&(spom1->nazev),&tec);
                    strCopyString(&(spom2->nazev),&tec);
                }else{
                    if(strCmpString(&(spom4->nazev),&tec)==0){
                        pomv1->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                        printf("typ op1 %i\n",spom2->type);
                        printf("typ op2 %i\n",spom3->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v1));
                        strCopyString(&(spom2->nazev),&tec);
                        strCopyString(&(spom3->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom5->nazev),&tec)==0){
                            pomv1->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                            printf("typ op1 %i\n",spom3->type);
                            printf("typ op2 %i\n",spom4->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v1));
                            strCopyString(&(spom3->nazev),&tec);
                            strCopyString(&(spom4->nazev),&tec);
                        }else{
                            pomv1->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                            printf("typ op1 %i\n",spom4->type);
                            printf("typ op2 %i\n",spom5->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v1));
                            strCopyString(&(spom4->nazev),&tec);
                            strCopyString(&(spom5->nazev),&tec);
                        }
                    }
                }

                sp123=0;
                sp1234=0;
                sp12345=0;
            }else{
                if (strCmpString(&(pomv2->nazev),&c)==0){
                    generateVariable(&v2);
                    strCopyString(&(pomv2->nazev),&v2);
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        pomv2->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                        printf("typ op1 %i\n",spom1->type);
                        printf("typ op2 %i\n",spom2->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            pomv2->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                            printf("typ op1 %i\n",spom2->type);
                            printf("typ op2 %i\n",spom3->type);
                            printf("typ vysledku %i\n",pomv2->type);
                            printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec)==0){
                                pomv2->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                                printf("typ op1 %i\n",spom3->type);
                                printf("typ op2 %i\n",spom4->type);
                                printf("typ vysledku %i\n",pomv2->type);
                                printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv2->type=typecontrol(ST,ridic,op,spom4->type,spom5->type);
                                printf("typ op1 %i\n",spom4->type);
                                printf("typ op2 %i\n",spom5->type);
                                printf("typ vysledku %i\n",pomv2->type);
                                printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v2));
                                strCopyString(&(spom4->nazev),&tec);
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    if (strCmpString(&(pomv3->nazev),&c)==0){
                            //printf("%s\n",strGetStr(&(pomv1->nazev)));
                        generateVariable(&v3);
                        strCopyString(&(pomv3->nazev),&v3);
                        //printf("sdfsdfsdfsdfsdfdsfsdfsdfsdfsdf");
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            pomv3->type=typecontrol(ST,ridic,op,spom1->type,spom2->type);
                            printf("typ op1 %i\n",spom1->type);
                            printf("typ op2 %i\n",spom2->type);
                            printf("typ vysledku %i\n",pomv3->type);
                            printf("op %i, %s, %s, %sv3\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v3));
                            strCopyString(&(spom1->nazev),&tec);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                pomv3->type=typecontrol(ST,ridic,op,spom2->type,spom3->type);
                                printf("typ op1 %i\n",spom2->type);
                                printf("typ op2 %i\n",spom3->type);
                                printf("typ vysledku %i\n",pomv3->type);
                                printf("op %i, %s, %s, %sv3\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v3));
                                strCopyString(&(spom2->nazev),&tec);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if (strCmpString(&(spom5->nazev),&tec)==0){
                                    pomv3->type=typecontrol(ST,ridic,op,spom3->type,spom4->type);
                                    printf("typ op1 %i\n",spom3->type);
                                    printf("typ op2 %i\n",spom4->type);
                                    printf("typ vysledku %i\n",pomv3->type);
                                    printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom3->nazev),&tec);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv3->type=typecontrol(ST,ridic,op,spom4->type,spom5->type);
                                    printf("typ op1 %i\n",spom4->type);
                                    printf("typ op2 %i\n",spom5->type);
                                    printf("typ vysledku %i\n",pomv3->type);
                                    printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom4->nazev),&tec);
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                        sp123=0;
                        sp1234=0;
                        sp12345=0;
                    }
                }
            }
        }

        //printf("i1234 %i \n",i1234);
        if (op!=-1 && i123==0 && i1234==2){

            printf("v1 + v2 = v3 \n");
            /*printf("%s\n",strGetStr(&(pomv1->nazev)));
            printf("%s\n",strGetStr(&(pomv2->nazev)));
            printf("%s\n",strGetStr(&(pomv3->nazev)));
            printf("%c\n",strGetStr(&c));
            printf("%i\n",strCmpString(&(pomv3->nazev),&c));*/



            if (strCmpString(&(pomv3->nazev),&c)==0){
                /*printf("%s\n",strGetStr(&(pomv3->nazev)));
                printf("%c\n",strGetStr(&c));*/
                generateVariable(&v3);
                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                printf("typ op1 %i\n",pomv1->type);
                printf("typ op2 %i\n",pomv2->type);
                printf("typ vysledku %i\n",pomv1->type);

                printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                strCopyString(&(pomv1->nazev),&v3);
                printf("%s\n",strGetStr(&(pomv1->nazev)));
                strCopyString(&(pomv2->nazev),&c);
                printf("%s\n",strGetStr(&(pomv2->nazev)));
                sp123=0;
                sp1234=0;
                sp12345=0;
            }else{
                generateVariable(&v4);
                pomv2->type=typecontrol(ST,ridic,op,pomv2->type,pomv3->type);
                printf("typ op1 %i\n",pomv2->type);
                printf("typ op2 %i\n",pomv3->type);
                printf("typ vysledku %i\n",pomv2->type);

                printf("op %i, %sv2, %sv3, %sv4\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(pomv3->nazev)),strGetStr(&v4));
                strCopyString(&(pomv2->nazev),&v4);
                printf("%s\n",strGetStr(&(pomv1->nazev)));
                strCopyString(&(pomv3->nazev),&c);
                printf("%s\n",strGetStr(&(pomv2->nazev)));
                sp123=0;
                sp1234=0;
                sp12345=0;
            }


        }

        if (op!=-1 && i123==1 && i1234==1){

            printf("v1 + prom1 = v2 \n");
            generateVariable(&a);
            if (strCmpString(&(pomv3->nazev),&c)==0){
                generateVariable(&v2);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                if (sp123>sp1234){
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom1->type);
                        printf("typ op1 %i\n",pomv1->type);
                        printf("typ op2 %i\n",spom1->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom1->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom2->type);
                            printf("typ op1 %i\n",pomv1->type);
                            printf("typ op2 %i\n",spom2->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom3->type);
                                printf("typ op1 %i\n",pomv1->type);
                                printf("typ op2 %i\n",spom3->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom4->type);
                                    printf("typ op1 %i\n",pomv1->type);
                                    printf("typ op2 %i\n",spom4->type);
                                    printf("typ vysledku %i\n",pomv1->type);
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom5->type);
                                    printf("typ op1 %i\n",pomv1->type);
                                    printf("typ op2 %i\n",spom5->type);
                                    printf("typ vysledku %i\n",pomv1->type);
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v2));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        pomv1->type=typecontrol(ST,ridic,op,spom1->type,pomv1->type);
                        printf("typ op1 %i\n",spom1->type);
                        printf("typ op2 %i\n",pomv1->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            pomv1->type=typecontrol(ST,ridic,op,spom2->type,pomv1->type);
                            printf("typ op1 %i\n",spom2->type);
                            printf("typ op2 %i\n",pomv1->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                pomv1->type=typecontrol(ST,ridic,op,spom3->type,pomv1->type);
                                printf("typ op1 %i\n",spom3->type);
                                printf("typ op2 %i\n",pomv1->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    pomv1->type=typecontrol(ST,ridic,op,spom4->type,pomv1->type);
                                    printf("typ op1 %i\n",spom4->type);
                                    printf("typ op2 %i\n",pomv1->type);
                                    printf("typ vysledku %i\n",pomv1->type);
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv1->type=typecontrol(ST,ridic,op,spom5->type,pomv1->type);
                                    printf("typ op1 %i\n",spom5->type);
                                    printf("typ op2 %i\n",pomv1->type);
                                    printf("typ vysledku %i\n",pomv1->type);
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(&(pomv1->nazev),&v2);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
            }else{
                generateVariable(&v3);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                if (sp123>sp1234){
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom1->type);
                        printf("typ op1 %i\n",pomv2->type);
                        printf("typ op2 %i\n",spom1->type);
                        printf("typ vysledku %i\n",pomv2->type);
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(spom1->nazev)),strGetStr(&v3));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom2->type);
                            printf("typ op1 %i\n",pomv2->type);
                            printf("typ op2 %i\n",spom2->type);
                            printf("typ vysledku %i\n",pomv2->type);
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v3));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom3->type);
                                printf("typ op1 %i\n",pomv2->type);
                                printf("typ op2 %i\n",spom3->type);
                                printf("typ vysledku %i\n",pomv2->type);
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v3));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom4->type);
                                    printf("typ op1 %i\n",pomv2->type);
                                    printf("typ op2 %i\n",spom4->type);
                                    printf("typ vysledku %i\n",pomv2->type);
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,spom5->type);
                                    printf("typ op1 %i\n",pomv2->type);
                                    printf("typ op2 %i\n",spom5->type);
                                    printf("typ vysledku %i\n",pomv2->type);
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&a),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        pomv2->type=typecontrol(ST,ridic,op,spom1->type,pomv2->type);
                        printf("typ op1 %i\n",spom1->type);
                        printf("typ op2 %i\n",pomv2->type);
                        printf("typ vysledku %i\n",pomv2->type);
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            pomv2->type=typecontrol(ST,ridic,op,spom2->type,pomv2->type);
                            printf("typ op1 %i\n",spom2->type);
                            printf("typ op2 %i\n",pomv2->type);
                            printf("typ vysledku %i\n",pomv2->type);
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                pomv2->type=typecontrol(ST,ridic,op,spom3->type,pomv2->type);
                                printf("typ op1 %i\n",spom3->type);
                                printf("typ op2 %i\n",pomv2->type);
                                printf("typ vysledku %i\n",pomv2->type);
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    pomv2->type=typecontrol(ST,ridic,op,spom4->type,pomv2->type);
                                    printf("typ op1 %i\n",spom4->type);
                                    printf("typ op2 %i\n",pomv2->type);
                                    printf("typ vysledku %i\n",pomv2->type);
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    pomv2->type=typecontrol(ST,ridic,op,spom5->type,pomv2->type);
                                    printf("typ op1 %i\n",spom5->type);
                                    printf("typ op2 %i\n",pomv2->type);
                                    printf("typ vysledku %i\n",pomv2->type);
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(&(pomv2->nazev),&v3);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
            }

        }

        if (op!=-1 && i123==1 && i12345==1){
            printf("v3 + prom1 = v1 \n");
            generateVariable(&a);
            generateVariable(&v2);
            //printf("%s\n",strGetStr(&(pomv1->nazev)));
            if (sp123>sp12345){
                if (strCmpString(&(spom2->nazev),&tec)==0){
                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom1->type);
                    printf("typ op1 %i\n",pomv1->type);
                    printf("typ op2 %i\n",spom1->type);
                    printf("typ vysledku %i\n",pomv1->type);
                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom1->nazev)),strGetStr(&v2));
                    strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom2->type);
                        printf("typ op1 %i\n",pomv1->type);
                        printf("typ op2 %i\n",spom2->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom3->type);
                            printf("typ op1 %i\n",pomv1->type);
                            printf("typ op2 %i\n",spom3->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec)==0){
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom4->type);
                                printf("typ op1 %i\n",pomv1->type);
                                printf("typ op2 %i\n",spom4->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,spom5->type);
                                printf("typ op1 %i\n",pomv1->type);
                                printf("typ op2 %i\n",spom5->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(spom5->nazev)),strGetStr(&v2));
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                }
                sp123=0;
                sp1234=0;
                sp12345=0;
            }else{
                if (strCmpString(&(spom2->nazev),&tec)==0){
                    pomv1->type=typecontrol(ST,ridic,op,spom1->type,pomv1->type);
                    printf("typ op1 %i\n",spom1->type);
                    printf("typ op2 %i\n",pomv1->type);
                    printf("typ vysledku %i\n",pomv1->type);
                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                    strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        pomv1->type=typecontrol(ST,ridic,op,spom2->type,pomv1->type);
                        printf("typ op1 %i\n",spom2->type);
                        printf("typ op2 %i\n",pomv1->type);
                        printf("typ vysledku %i\n",pomv1->type);
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            pomv1->type=typecontrol(ST,ridic,op,spom3->type,pomv1->type);
                            printf("typ op1 %i\n",spom3->type);
                            printf("typ op2 %i\n",pomv1->type);
                            printf("typ vysledku %i\n",pomv1->type);
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec)==0){
                                pomv1->type=typecontrol(ST,ridic,op,spom4->type,pomv1->type);
                                printf("typ op1 %i\n",spom4->type);
                                printf("typ op2 %i\n",pomv1->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                pomv1->type=typecontrol(ST,ridic,op,spom5->type,pomv1->type);
                                printf("typ op1 %i\n",spom5->type);
                                printf("typ op2 %i\n",pomv1->type);
                                printf("typ vysledku %i\n",pomv1->type);
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v2));
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                }
                sp123=0;
                sp1234=0;
                sp12345=0;
            }
            strCopyString(&(pomv1->nazev),&v2);
            //printf("%s\n",strGetStr(&(pomv1->nazev)));
        }

        if (op!=-1 && i1234==1 && i12345==1){

            printf("v1 + v2 = v3 \n");
            //printf("%s\n",strGetStr(&(pomv1->nazev)));
            //printf("%s\n",strGetStr(&(pomv2->nazev)));
            if (strCmpString(&(pomv3->nazev),&c)==0)
            {
                generateVariable(&v3);
                if (sp1234>sp12345){
                    pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                    printf("typ op1 %i\n",pomv1->type);
                    printf("typ op2 %i\n",pomv2->type);
                    printf("typ vysledku %i\n",pomv1->type);
                    printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    pomv1->type=typecontrol(ST,ridic,op,pomv2->type,pomv1->type);
                    printf("typ op1 %i\n",pomv2->type);
                    printf("typ op2 %i\n",pomv1->type);
                    printf("typ vysledku %i\n",pomv1->type);
                    printf("op %i, %sv2, %sv1, %sv3\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(pomv1->nazev)),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(&(pomv1->nazev),&v3);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                strCopyString(&(pomv2->nazev),&c);
                //printf("%s\n",strGetStr(&(pomv2->nazev)));
            }else{
                generateVariable(&v4);
                if (sp1234>sp12345){
                    pomv2->type=typecontrol(ST,ridic,op,pomv2->type,pomv3->type);
                    printf("typ op1 %i\n",pomv2->type);
                    printf("typ op2 %i\n",pomv3->type);
                    printf("typ vysledku %i\n",pomv2->type);
                    printf("op %i, %sv2, %sv3, %sv4\n",op,strGetStr(&(pomv2->nazev)),strGetStr(&(pomv3->nazev)),strGetStr(&v4));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    pomv2->type=typecontrol(ST,ridic,op,pomv3->type,pomv2->type);
                    printf("typ op1 %i\n",pomv3->type);
                    printf("typ op2 %i\n",pomv2->type);
                    printf("typ vysledku %i\n",pomv2->type);
                    printf("op %i, %sv3, %sv2, %sv4\n",op,strGetStr(&(pomv3->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v4));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(&(pomv2->nazev),&v4);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                strCopyString(&(pomv3->nazev),&c);
                //printf("%s\n",strGetStr(&(pomv2->nazev)));
            }
        }

        if (op!=-1 && i12345==2){

            printf("v1 + v2 = v3 \n");
            //printf("%s\n",strGetStr(&(pomv1->nazev)));
            //printf("%s\n",strGetStr(&(pomv2->nazev)));
            if (strCmpString(&(pomv3->nazev),&c)==0)
            {
                generateVariable(&v3);
                pomv1->type=typecontrol(ST,ridic,op,pomv1->type,pomv2->type);
                printf("typ op1 %i\n",pomv1->type);
                printf("typ op2 %i\n",pomv2->type);
                printf("typ vysledku %i\n",pomv1->type);
                printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(&(pomv1->nazev)),strGetStr(&(pomv2->nazev)),strGetStr(&v3));
                sp123=0;
                sp1234=0;
                sp12345=0;
                strCopyString(&(pomv1->nazev),&v3);
                //printf("%s\n",strGetStr(&(pomv1->nazev)));
                strCopyString(&(pomv2->nazev),&c);
                //printf("%s\n",strGetStr(&(pomv2->nazev)));
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
    if (redukid==1 || redukzavor==1){
            printf("id %i \n",redukid);
        if (redukid==1){
            ptstack[sp]=-1;
            sp++;
            printf("1op %i \n",op);
            printf("1i123 %i \n",i123);
            printf("1i1234 %i \n",i1234);
            printf("1i12345 %i \n",i12345);
            if (i123 == 1 && op==-1){
                ptstack[sp]=123;
                i12345=0;
                i1234=0;
                i123=0;
            }else{
                printf("tttt %i \n",t);
                if (i123 == 0 && op==-1 && t!=11){
                    ptstack[sp]=123;
                    i12345=0;
                    i1234=0;
                    i123=0;
                }else{
                    if (i123 == 0 && op==-1 && t==11){
                        sp--;
                        ptstack[sp]=123;
                        i12345=0;
                        i1234=0;
                        i123=0;
                    }else{
                        if (i123 == 2 && op!=-1){
                            ptstack[sp]=1234;
                            i12345=0;
                            i1234=0;
                            i123=0;
                            op=-1;
                        }else{
                            if (i123 == 1 && i1234 == 1 && op!=-1){
                                ptstack[sp]=1234;
                                i12345=0;
                                i1234=0;
                                i123=0;
                                op=-1;
                            }else{
                                if (i1234 == 2 && op!=-1){
                                    ptstack[sp]=12345;
                                    i12345=0;
                                    i1234=0;
                                    i123=0;
                                    op=-1;
                                }else{
                                    if (i123 == 0 && op!=-1){
                                        ptstack[sp]=123;
                                        i12345=0;
                                        i1234=0;
                                        i123=0;
                                        op=-1;
                                    }else{
                                        if (i1234 == 0 && op!=-1){
                                            ptstack[sp]=1234;
                                            i12345=0;
                                            i1234=0;
                                            i123=0;
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
        if (redukzavor==1 && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN || t==TP_COL)){

            printf("2op %i \n",op);
            printf("2i123 %i \n",i123);
            printf("2i1234 %i \n",i1234);
            printf("2i12345 %i \n",i12345);
            printf("2i12345 %i \n",i12345);
            //printf("ctive %i\n",ptstack[aktiv]);
            if (i123 == 1 && op==-1){
                ptstack[sp]=123;
                i12345=0;
                i1234=0;
                i123=0;
            }else{
                if (i1234 == 1 && op==-1 && i12345==0){
                    ptstack[sp]=1234;
                    i12345=0;
                    i1234=0;
                    i123=0;
                }else{
                    if (i123 == 2 && op!=-1){
                        ptstack[sp]=1234;
                        i12345=0;
                        i1234=0;
                        i123=0;
                        op=-1;
                    }else{
                        if (i123 == 1 && i1234 == 1 && op!=-1){
                            ptstack[sp]=1234;
                            i12345=0;
                            i1234=0;
                            i123=0;
                            op=-1;
                        }else{
                            if (i1234 == 2 && op!=-1){
                                ptstack[sp]=12345;
                                i12345=0;
                                i1234=0;
                                i123=0;
                                op=-1;
                            }else{
                                if (i12345 == 1 && op==-1){
                                    ptstack[sp]=12345;
                                    i12345=0;
                                    i1234=0;
                                    i123=0;
                                    op=-1;
                                }else{
                                    if (i12345 == 1 && op!=-1){
                                        ptstack[sp]=12345;
                                        i12345=0;
                                        i1234=0;
                                        i123=0;
                                        op=-1;
                                    }else{
                                        if (i12345 == 2 && op!=-1){
                                            ptstack[sp]=12345;
                                            i12345=0;
                                            i1234=0;
                                            i123=0;
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
        if (t!=TP_RBRA){
                printf("3op %i \n",op);
            printf("3i123 %i \n",i123);
            printf("3i1234 %i \n",i1234);
            printf("3i12345 %i \n",i12345);
            aktiv=redukpom-1;
            /*printf("stack %i \n",ptstack[sp+2]);
            printf("reduk %i \n",ptstack[redukpom]);*/
            if (i123 == 1 && op==-1){
                ptstack[redukpom+1]=123;
                i12345=0;
                i1234=0;
                i123=0;
            }else{
                if (i1234 == 1 && op==-1 && ptstack[aktiv]!=13){
                    ptstack[redukpom+1]=1234;
                    i12345=0;
                    i1234=0;
                    i123=0;
                    //sp--;
                }else{
                    if (i12345 == 1 && op==-1){
                        ptstack[redukpom+1]=12345;
                        i12345=0;
                        i1234=0;
                        i123=0;
                    }else{
                        ptstack[redukpom+1]=1234;
                        i12345=0;
                        i1234=0;
                        i123=0;
                    }
                }
            }
            sp=sp+1;
            redukzavor=0;
        }
        else{
            printf("4op %i \n",op);
            printf("4i123 %i \n",i123);
            printf("4i1234 %i \n",i1234);
            printf("4i12345 %i \n",i12345);
            if (i123 == 1 && op==-1){
                ptstack[sp]=123;
                i12345=0;
                i1234=0;
                i123=0;
            }else{
                if (i123 == 0 && op==-1){
                    ptstack[sp]=1234;
                    i12345=0;
                    i1234=0;
                    i123=0;
                }else{
                    if (i123 == 2 && op!=-1){
                        ptstack[sp]=1234;
                        i12345=0;
                        i1234=0;
                        i123=0;
                        op=-1;
                    }else{
                        if (i123 == 1 && i1234 == 1 && op!=-1){
                            ptstack[sp]=1234;
                            i12345=0;
                            i1234=0;
                            i123=0;
                            op=-1;
                        }else{
                            if (i1234 == 2 && op!=-1){
                                ptstack[sp]=12345;
                                i12345=0;
                                i1234=0;
                                i123=0;
                                op=-1;
                            }else{
                                if (i1234 == 2 && op!=-1 && t!=11){
                                    ptstack[redukpom+1]=12345;
                                    i12345=0;
                                    i1234=0;
                                    i123=0;
                                    op=-1;
                                    sp++;
                                }else{
                                    if (i1234 == 2 && op!=-1 && t==11){
                                        ptstack[sp]=12345;
                                        i12345=0;
                                        i1234=0;
                                        i123=0;
                                        op=-1;
                                    }else{
                                        if (i12345 == 2 && op!=-1 && t!=11){
                                            ptstack[redukpom+1]=12345;
                                            i12345=0;
                                            i1234=0;
                                            i123=0;
                                            op=-1;
                                            sp++;
                                        }else{
                                            if (i12345 == 2 && op!=-1 && t==11){
                                                ptstack[sp]=12345;
                                                i12345=0;
                                                i1234=0;
                                                i123=0;
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
        printf("5op %i \n",op);
            printf("5i123 %i \n",i123);
            printf("5i1234 %i \n",i1234);
            printf("5i12345 %i \n",i12345);
        if (i123 == 1 && op==-1){
            ptstack[sp]=123;
            i12345=0;
            i1234=0;
            i123=0;
        }else{
            if (i123 == 0 && op==-1 && i1234 == 0){
                    ptstack[sp]=123;
                    i12345=0;
                    i1234=0;
                    i123=0;
                }else{
                    if (i1234 == 1 && op==-1 && i123 == 0){
                        ptstack[sp]=1234;
                        i12345=0;
                        i1234=0;
                        i123=0;
                        op=-1;
                    }else{
                        if (i123 == 2 && op!=-1 && t!=11){
                            ptstack[redukpom+1]=1234;
                            i12345=0;
                            i1234=0;
                            i123=0;
                            op=-1;
                            sp++;
                        }else{
                            if (i123 == 2 && op!=-1 && t==11){
                                ptstack[sp]=1234;
                                i12345=0;
                                i1234=0;
                                i123=0;
                                op=-1;
                            }else{
                                if (i123 == 1 && i1234 == 1 && op!=-1){
                                    ptstack[sp]=1234;
                                    i12345=0;
                                    i1234=0;
                                    i123=0;
                                    op=-1;
                                }else{
                                    if (i1234 == 2 && op!=-1 && t!=11){
                                        ptstack[redukpom+1]=12345;
                                        i12345=0;
                                        i1234=0;
                                        i123=0;
                                        op=-1;
                                        sp++;
                                    }else{
                                        if (i1234 == 2 && op!=-1 && t==11){
                                            ptstack[sp]=12345;
                                            i12345=0;
                                            i1234=0;
                                            i123=0;
                                            op=-1;
                                        }else{
                                            if (i12345 == 2 && op!=-1 && t!=11){
                                                ptstack[redukpom+1]=12345;
                                                i12345=0;
                                                i1234=0;
                                                i123=0;
                                                op=-1;
                                                sp++;
                                            }else{
                                                if (i12345 == 2 && op!=-1 && t==11){
                                                    ptstack[sp]=12345;
                                                    i12345=0;
                                                    i1234=0;
                                                    i123=0;
                                                    op=-1;
                                                }else{
                                                    ptstack[sp]=12345;
                                                    i12345=0;
                                                    i1234=0;
                                                    i123=0;
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
    if (ptstack[aktiv]==TP_DOLL && t!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN && t!=TP_COL && ptstack[1]!=-1){
        ptstack[2]=ptstack[1];
        ptstack[1]=-1;
        sp++;
    }

    while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("\n");
    /*printf("active %i \n",ptstack[aktiv]);
    printf("token %i \n",t);
    printf("id  %i zavor %i\n",redukid,redukzavor);*/
    return;
}

void shifting(tGlobSymbolTable *ST,Tridic *ridic){

    if (((t>=TP_MUL)&&(t<=TP_NEQU))&&(loadid==1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
        loadid=0;
    }else
    if (((t>=TP_MUL)&&(t<=TP_NEQU))&&(loadid==0)){
        printf("chyba pico, nemuzes dat operator za operator nebo hned za levou zavorku \n");
        error(NULL,SEM_ERR,NULL);
    }else
    if ((t==TP_RBRA)&&(loadid==1)){
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if ((t==TP_RBRA)&&(loadid==0)){
        printf("chyba pico, nemuzes dat pravou zavorku za operator \n");
        error(NULL,SEM_ERR,NULL);
    }else
    if (t==TP_LBRA){
        sp++;
        ptstack[sp]=-1;
        sp++;
        ptstack[sp]=t;
        aktiv=sp;
    }else
    if (t==TP_IDENT){
        sp++;
        ptstack[sp]=-1;
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




