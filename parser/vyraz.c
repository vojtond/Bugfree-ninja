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

string pomv1;
string pomv2;
string pomv3;
FILE *ptabletxt;


int VYRAZ(tGlobSymbolTable *ST,Tridic *ridic){

    c=0;
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



    string tec;
    strInit(&tec);
    strAddChar(&tec,'.');

    strInit(&pomv1);
    strAddChar(&pomv1,'N');
    //printf("%s\n",strGetStr(&pomv1));
    strInit(&pomv2);
    strAddChar(&pomv2,'N');
    //printf("%s\n",strGetStr(&pomv2));
    strInit(&pomv3);
    strAddChar(&pomv3,'N');
    //printf("%s\n",strGetStr(&pomv3));
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
        strCopyString(&(spom1->nazev),&ridic->attr_token);
        spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);
        printf("typ %i",spom1->type);
        return;
    }
    if (t>=14 && t<=16){
        ptstack[1]=-1;
        ptstack[2]=12;
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

    while ((t=gtoken(ridic))!=TP_SEM && t!=KEY_END && t!=KEY_DO && t!=KEY_THEN){
        if (t>=14 && t<=16){
            tpom=t;
            t=12;
            konst=1;
        }
        if (t==12){

            if (strCmpString(&(spom1->nazev),&tec)==0){
                strCopyString(&(spom1->nazev),&ridic->attr_token);
                if (konst==1){
                    spom1->type=tpom;
                }else{
                    spom1->type=tableSearch(ST,&ridic->attr_token,0,ridic);
                    printf("typ %i",spom1->type);
                    return;
                }
            }else{
                if (strCmpString(&(spom2->nazev),&tec)==0){
                    strCopyString(&(spom2->nazev),&ridic->attr_token);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        strCopyString(&(spom3->nazev),&ridic->attr_token);
                    }else{
                        if (strCmpString(&(spom4->nazev),&tec)==0){
                            strCopyString(&(spom4->nazev),&ridic->attr_token);
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec)==0){
                            strCopyString(&(spom5->nazev),&ridic->attr_token);
                            }
                        }
                    }
                }
            }
        }
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
                        reduction(ST,ridic,&pomv1,&pomv2,&pomv3,spom1,spom2,spom3,spom4,spom5);
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
    if (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN){
        i=0;
        while (i<=sp){
            printf("zasobnik %i\n",ptstack[i]);
            i++;
        }
        printf("active %i \n",ptstack[aktiv]);
        printf("token %i \n",t);
        printf("id  %i zavor %i\n",redukid,redukzavor);
        printf("\n");


        while (ptable[ptstack[aktiv]][13]==2){
            reduction(ST,ridic,&pomv1,&pomv2,&pomv3,spom1,spom2,spom3,spom4,spom5);
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

    printf("idpom1 %s\n",strGetStr(&spom1->nazev));
    printf("idpom2 %s\n",strGetStr(&spom2->nazev));
    printf("idpom3 %s\n",strGetStr(&spom3->nazev));
    printf("idpom4 %s\n",strGetStr(&spom4->nazev));
    printf("idpom5 %s\n",strGetStr(&spom5->nazev));

    return 1;

return 0;
}

void reduction(tGlobSymbolTable *ST,Tridic *ridic, string *pomv1, string *pomv2, string *pomv3, spom *spom1, spom *spom2, spom *spom3, spom *spom4, spom *spom5){

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

    if ((ptstack[sp]>=0 && ptstack[sp]<=9) && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){
        printf("chyba pico, blby ukonceni \n");
        error(NULL,SEM_ERR,NULL);
    }

    redukpom=sp;
    while (ptstack[redukpom]!=-1){
        if (ptstack[redukpom]>=0 && ptstack[redukpom]<=9){
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
            /*printf("%s\n",strGetStr(pomv1));
            printf("%s\n",strGetStr(&c));
            printf("%i\n",strCmpString(pomv1,&c));*/
            if (strCmpString(pomv1,&c)==0){
                generateVariable(&v1);
                strCopyString(pomv1,&v1);
                //printf("%s\n",strGetStr(pomv1));
                if (strCmpString(&(spom3->nazev),&tec)==0){
                    printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v1));
                    strCopyString(&(spom1->nazev),&tec);
                    strCopyString(&(spom2->nazev),&tec);
                }else{
                    if(strCmpString(&(spom4->nazev),&tec)==0){
                        printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v1));
                        strCopyString(&(spom2->nazev),&tec);
                        strCopyString(&(spom3->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom5->nazev),&tec)==0){
                            printf("op %i, %s, %s, %sv1\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v1));
                            strCopyString(&(spom3->nazev),&tec);
                            strCopyString(&(spom4->nazev),&tec);
                        }else{
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
                if (strCmpString(pomv2,&c)==0){
                    generateVariable(&v2);
                    strCopyString(pomv2,&v2);
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if (strCmpString(&(spom5->nazev),&tec)==0){
                                printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
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
                    if (strCmpString(pomv3,&c)==0){
                            //printf("%s\n",strGetStr(pomv1));
                        generateVariable(&v3);
                        strCopyString(pomv3,&v3);
                        //printf("sdfsdfsdfsdfsdfdsfsdfsdfsdfsdf");
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            printf("op %i, %s, %s, %sv3\n",op,strGetStr(&(spom1->nazev)),strGetStr(&(spom2->nazev)),strGetStr(&v3));
                            strCopyString(&(spom1->nazev),&tec);
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                printf("op %i, %s, %s, %sv3\n",op,strGetStr(&(spom2->nazev)),strGetStr(&(spom3->nazev)),strGetStr(&v3));
                                strCopyString(&(spom2->nazev),&tec);
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if (strCmpString(&(spom5->nazev),&tec)==0){
                                    printf("op %i, %s, %s, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(&(spom4->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom3->nazev),&tec);
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
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
            /*printf("%s\n",strGetStr(pomv1));
            printf("%s\n",strGetStr(pomv2));
            printf("%s\n",strGetStr(pomv3));
            printf("%c\n",strGetStr(&c));
            printf("%i\n",strCmpString(pomv3,&c));*/



            if (strCmpString(pomv3,&c)==0){
                /*printf("%s\n",strGetStr(pomv3));
                printf("%c\n",strGetStr(&c));*/
                generateVariable(&v3);
                printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(pomv1),strGetStr(pomv2),strGetStr(&v3));
                strCopyString(pomv1,&v3);
                printf("%s\n",strGetStr(pomv1));
                strCopyString(pomv2,&c);
                printf("%s\n",strGetStr(pomv2));
                sp123=0;
                sp1234=0;
                sp12345=0;
            }else{
                generateVariable(&v4);
                printf("op %i, %sv2, %sv3, %sv4\n",op,strGetStr(pomv2),strGetStr(pomv3),strGetStr(&v4));
                strCopyString(pomv2,&v4);
                printf("%s\n",strGetStr(pomv1));
                strCopyString(pomv3,&c);
                printf("%s\n",strGetStr(pomv2));
                sp123=0;
                sp1234=0;
                sp12345=0;
            }


        }

        if (op!=-1 && i123==1 && i1234==1){

            printf("v1 + prom1 = v2 \n");
            generateVariable(&a);
            if (strCmpString(pomv3,&c)==0){
                generateVariable(&v2);
                //printf("%s\n",strGetStr(pomv1));
                if (sp123>sp1234){
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom1->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom5->nazev)),strGetStr(&v2));
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
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(pomv1),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(pomv1),strGetStr(&v2));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(pomv1),strGetStr(&v2));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(pomv1),strGetStr(&v2));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(pomv1),strGetStr(&v2));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(pomv1,&v2);
                //printf("%s\n",strGetStr(pomv1));
            }else{
                generateVariable(&v3);
                //printf("%s\n",strGetStr(pomv1));
                if (sp123>sp1234){
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&(spom1->nazev)),strGetStr(&v3));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&(spom2->nazev)),strGetStr(&v3));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&(spom3->nazev)),strGetStr(&v3));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&(spom4->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&(spom5->nazev)),strGetStr(&v3));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv2),strGetStr(&a),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    if (strCmpString(&(spom2->nazev),&tec)==0){
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(pomv2),strGetStr(&v3));
                        strCopyString(&(spom1->nazev),&tec);
                    }else{
                        if (strCmpString(&(spom3->nazev),&tec)==0){
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(pomv2),strGetStr(&v3));
                            strCopyString(&(spom2->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom4->nazev),&tec)==0){
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(pomv2),strGetStr(&v3));
                                strCopyString(&(spom3->nazev),&tec);
                            }else{
                                if(strCmpString(&(spom5->nazev),&tec)==0){
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(pomv2),strGetStr(&v3));
                                    strCopyString(&(spom4->nazev),&tec);
                                }else{
                                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(pomv2),strGetStr(&v3));
                                    strCopyString(&(spom5->nazev),&tec);
                                }
                            }
                        }
                    }
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(pomv2,&v3);
                //printf("%s\n",strGetStr(pomv1));
            }

        }

        if (op!=-1 && i123==1 && i12345==1){
            printf("v3 + prom1 = v1 \n");
            generateVariable(&a);
            generateVariable(&v2);
            //printf("%s\n",strGetStr(pomv1));
            if (sp123>sp12345){
                if (strCmpString(&(spom2->nazev),&tec)==0){
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom1->nazev)),strGetStr(&v2));
                        strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom2->nazev)),strGetStr(&v2));
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom3->nazev)),strGetStr(&v2));
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec)==0){
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom4->nazev)),strGetStr(&v2));
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                printf("op %i, %sv1, %s, %sv2\n",op,strGetStr(pomv1),strGetStr(&(spom5->nazev)),strGetStr(&v2));
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
                    printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom1->nazev)),strGetStr(pomv1),strGetStr(&v2));
                    strCopyString(&(spom1->nazev),&tec);
                }else{
                    if (strCmpString(&(spom3->nazev),&tec)==0){
                        printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom2->nazev)),strGetStr(pomv1),strGetStr(&v2));
                        strCopyString(&(spom2->nazev),&tec);
                    }else{
                        if(strCmpString(&(spom4->nazev),&tec)==0){
                            printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom3->nazev)),strGetStr(pomv1),strGetStr(&v2));
                            strCopyString(&(spom3->nazev),&tec);
                        }else{
                            if(strCmpString(&(spom5->nazev),&tec)==0){
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom4->nazev)),strGetStr(pomv1),strGetStr(&v2));
                                strCopyString(&(spom4->nazev),&tec);
                            }else{
                                printf("op %i, %s, %sv1, %sv2\n",op,strGetStr(&(spom5->nazev)),strGetStr(pomv1),strGetStr(&v2));
                                strCopyString(&(spom5->nazev),&tec);
                            }
                        }
                    }
                }
                sp123=0;
                sp1234=0;
                sp12345=0;
            }
            strCopyString(pomv1,&v2);
            //printf("%s\n",strGetStr(pomv1));
        }

        if (op!=-1 && i1234==1 && i12345==1){

            printf("v1 + v2 = v3 \n");
            //printf("%s\n",strGetStr(pomv1));
            //printf("%s\n",strGetStr(pomv2));
            if (strCmpString(pomv3,&c)==0)
            {
                generateVariable(&v3);
                if (sp1234>sp12345){
                    printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(pomv1),strGetStr(pomv2),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    printf("op %i, %sv2, %sv1, %sv3\n",op,strGetStr(pomv2),strGetStr(pomv1),strGetStr(&v3));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(pomv1,&v3);
                //printf("%s\n",strGetStr(pomv1));
                strCopyString(pomv2,&c);
                //printf("%s\n",strGetStr(pomv2));
            }else{
                generateVariable(&v4);
                if (sp1234>sp12345){
                    printf("op %i, %sv2, %sv3, %sv4\n",op,strGetStr(pomv2),strGetStr(pomv3),strGetStr(&v4));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }else{
                    printf("op %i, %sv3, %sv2, %sv4\n",op,strGetStr(pomv3),strGetStr(pomv2),strGetStr(&v4));
                    sp123=0;
                    sp1234=0;
                    sp12345=0;
                }
                strCopyString(pomv2,&v4);
                //printf("%s\n",strGetStr(pomv1));
                strCopyString(pomv3,&c);
                //printf("%s\n",strGetStr(pomv2));
            }
        }

        if (op!=-1 && i12345==2){

            printf("v1 + v2 = v3 \n");
            //printf("%s\n",strGetStr(pomv1));
            //printf("%s\n",strGetStr(pomv2));
            if (strCmpString(pomv3,&c)==0)
            {
                generateVariable(&v3);
                printf("op %i, %sv1, %sv2, %sv3\n",op,strGetStr(pomv1),strGetStr(pomv2),strGetStr(&v3));
                sp123=0;
                sp1234=0;
                sp12345=0;
                strCopyString(pomv1,&v3);
                //printf("%s\n",strGetStr(pomv1));
                strCopyString(pomv2,&c);
                //printf("%s\n",strGetStr(pomv2));
            }
        }



        if (ptstack[redukpom]==12){
            redukid=1;
        }
        if (ptstack[redukpom]==11){
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
        if (redukzavor==1 && (t==TP_SEM || t==KEY_END || t==KEY_DO || t==KEY_THEN)){

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
        if (t!=11){
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
    /*printf("active %i \n",ptstack[aktiv]);
    printf("token %i \n",t);
    printf("id  %i zavor %i\n",redukid,redukzavor);*/
    return;
}

void shifting(tGlobSymbolTable *ST,Tridic *ridic){

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




