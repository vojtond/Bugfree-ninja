/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
int pom;
int errora;

int typide;
FILE *soubor;
int counterVar = 1;

void gtoken(Tridic *ridic){
     strFree(&(ridic->attr_token));
    if ((strInit(&(ridic->attr_token)))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }
      ridic->token=get_token(soubor,&(ridic->hodnota),&(ridic->attr_token),&errora);

}
void pomoc(Tridic *ridic){

    pom=strCopyString(&(ridic->nazev_ident),&(ridic->attr_token));
}
int main()
{
    int pomt;
    int i=0;
    Tridic *ridic;
    sRamec *poma ;
    sRamec *pome ;
    /*hubli string a;*/
    ridic=malloc(sizeof (Tridic));
    tGlobSymbolTable ST;
    sGlobTableItem *koren;
    strInit(&(ridic->attr_token));
    strInit(&(ridic->nazev_ident));
    strInit(&(ridic->nazev_func));
    GlobTableInit(&ST,ridic);

    /*hubli generateVariable(&a);*/


    koren=ST.first;
    soubor = fopen("text.txt", "r");

    /* hubli printf("%s******\n",strGetStr(&a));*/

    if (START(&ST,ridic)) {
        printf("i tyhle hovadiny jsou spravne");

    }
    else{
        printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line());
    }
    koren=ST.first;
Rfirst=NULL;
  //  RamecCopy(koren->link, RamecInit());
  //  PopTopR(&poma);
    printf("v ramci je po ulozeni na zasobnik****\n");
   // LokVypis(&ST, ridic,poma);
    GlobVypis(&ST,ridic, koren);
    //PopTopR(&poma);


    koren=ST.first;
    printf("****************************************************************");



    error(&ST,0,ridic);
    return 0;
}
/*<START>   ->  <GLOBDEK>   <FUNC>  <SLOZ>*/
int START (tGlobSymbolTable *ST,Tridic *ridic){
    gtoken(ridic);
    if ((ridic->token == KEY_BEGIN) || (ridic->token ==KEY_VAR ) || (ridic->token == KEY_FUNCTION)) {   /*pokud je prvni token begin, var nebo function */
      if ((GLOBDEK(ST,ridic)) && (FUNC(ST,ridic)) && (SLOZ(ST,ridic))) {    /*rekuryivni sestup*/
            if (ridic->token==TP_DOT){/*pokud je posledni token tecka*/
                 gtoken(ridic);
                return 1;
            }
        }
    }
    error(ST,SYN_ERR,ridic);/*byl naleyen error v syn analyze*/
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (tGlobSymbolTable *ST,Tridic *ridic){

   if ((ridic->token == KEY_BEGIN)){
        return 1;
   }else {
   if ((ridic->token==KEY_FUNCTION)){
       gtoken(ridic);
       if (ridic->token==TP_IDENT){
            pom=strCopyString(&(ridic->nazev_func),&(ridic->attr_token));/*uchovani nazvu fce pro pozdejsi vyuziti*/

        if (GlobTableInsert(ST,&(ridic->nazev_func),FUNCTION_HEADER,ridic)){/*vlozeni funkce do glob tabulky*/
           //generate(FUNCTION_HEADER,ridic->nazev_func,NULL,NULL);
            gtoken(ridic);
            if (ridic->token==TP_LBRA){
                gtoken(ridic);
                if (ARG(ST,ridic)) {
                    if (ridic->token==TP_RBRA){
                        gtoken(ridic);
                        if (ridic->token==TP_COL){
                            gtoken(ridic);
                           if (TYPE(ST,ridic)) {
                            if (ridic->token==TP_SEM){
                                 gtoken(ridic);
                                if (LokTableInsert(ST,NULL,typide,ridic)){/*vlozeni navratoveho typu do lokalni tabulky*/
                                    return FORWAR(ST,ridic);
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
   }

    return 0;
}


/*<FORWARD> 	->	; <DEK> <SLOZ> ; <FUNC>*/
/*<FORWARD>	->	forward ; <FUNC>*/
int FORWAR (tGlobSymbolTable *ST,Tridic *ridic){

    if (ridic->token==KEY_VAR|| ridic->token==KEY_BEGIN){
        if ((DEK(ST,ridic))) {
             printf("generate(FUNCTION_BEGIN,%s,NULL,NULL);\n",strGetStr(&(ridic->nazev_func)));/*generovani navesti pro zacatek funkce*/
            if  (SLOZ(ST,ridic)){
                if (ridic->token==TP_SEM){
                    if (GlobTableInsert(ST,NULL,FUNCTION_END,ridic));/*oznaceni konce funkce pro glob tabulku*/
                    printf("generate(FUNCTION_END,%s,NULL,NULL);\n",strGetStr(&(ridic->nazev_func)));/*generovani konce tela funkce*/
                    gtoken(ridic);
                    return FUNC(ST,ridic);
                }
            }

        }
    }else{
        if (ridic->token==KEY_FORWARD){
            if (GlobTableInsert(ST,NULL,FUNCTION_FORWARD,ridic)){
                gtoken(ridic);
                if (ridic->token==TP_SEM){
                    gtoken(ridic);

                    return FUNC(ST,ridic);
                }
            }

        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (tGlobSymbolTable *ST,Tridic *ridic){
    if (ridic->token==TP_RBRA){
        return 1;
    }else{
        if (ridic->token==TP_IDENT){
            pomoc(ridic);
            gtoken(ridic);
            if (ridic->token==TP_COL){
                gtoken(ridic);

                if  (TYPE (ST,ridic)) {
                   if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){/*vlozeni argumentu do lok. tabulky symbolu*/
                            return ARGDAL(ST,ridic);
                        }


                }
            }
        }
    }

    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (tGlobSymbolTable *ST,Tridic *ridic){
     if (ridic->token==TP_RBRA){
        return 1;
    }else{
        if (ridic->token==TP_SEM){
            gtoken(ridic);
            if (ridic->token==TP_IDENT){
                pomoc(ridic);
                gtoken(ridic);
                if (ridic->token==TP_COL){
                    gtoken(ridic);
                    if ( TYPE(ST,ridic)) {
                         if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){/*vlozeni argumentu do lok. tabulky symbolu*/
                            return ARGDAL(ST,ridic);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (tGlobSymbolTable *ST,Tridic *ridic){
    if (ridic->token==KEY_WHILE){
        gtoken(ridic);
           printf("generate(WHILE_BEGIN,NULL,NULL,NULL);\n");/*zacatek vzhodnocovani podminky cyklu*/
        if(1/*VYRAZ(ST,ridic)*/){
             printf("generate(WHILE_COND,BOOL_Hubli,NULL,NULL);\n");/*konec vyhodnocovani podminky cyklu*/
            if (ridic->token==KEY_DO)
                gtoken(ridic);
                if ( SLOZ(ST,ridic)){
                  printf("generate(WHILE_END,NULL,NULL,NULL);\n"); /*konec tela cyklu*/
                  return 1;
                }
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (tGlobSymbolTable *ST,Tridic *ridic){

    if (ridic->token==KEY_IF){
        gtoken(ridic);

        if(1/*VYRAZ(ST,ridic)*/){
            printf("generate(IF_COND,BOOL_HUBLI,NULL,NULL);\n");/*konec podminky if*/
            if (ridic->token==KEY_THEN){
                printf("generate(IF_BEGIN,HUBLI,NULL,NULL);\n");/*zacatek tela if*/
                gtoken(ridic);
                if (SLOZ(ST,ridic)){
                    printf("generate(IF_END,HUBLI,NULL,NULL);\n");/*konec kladne vetve if*/
                    return ELSEP(ST,ridic);
                }
            }
        }
    }
return 0;
}

/*<ELSE>		->  	else  <SLOZ>*/
/*<ELSE>		-> 	eps*/
int ELSEP (tGlobSymbolTable *ST,Tridic *ridic){
   /* if ((ridic->token==TP_IDENT)||(ridic->token==KEY_WHILE)|| (ridic->token==KEY_IF)||(ridic->token==ST_SEM)
    ||(ridic->token==KEY_READLN)||(ridic->token==KEY_WRITE)||(ridic->token==KEY_BEGIN)||(ridic->token==KEY_END)){
       return 1;
    }else {*/
/*vlozeni argumentu do lok. tabulky symbolu*/
        if (ridic->token==KEY_ELSE){
           printf("generate(ELSE_BEGIN,NULL,NULL,NULL);\n"); /*zacatek zaporne vetve*/
            gtoken(ridic);
            if( SLOZ(ST,ridic)){
                printf("generate(ELSE_END,NULL,NULL,NULL);\n");/*konec zaporne vetve if */
                return 1;
            }
        }

return 0;
}


/*<POKYN>		->	<CYKLUS>*/
/*<POKYN>		->	<KDYZ>*/
/*<POKYN>		->	<PRIKAZ>*/
/*<POKYN>		->	READLN(id) */
/*<POKYN>		->	WRITE( <VYPIS>)	*/
/*<POKYN>		->	<SLOZ> */
int POKYN (tGlobSymbolTable *ST,Tridic *ridic){
  switch (ridic->token ){
    case TP_IDENT:
        return PRIKAZ(ST,ridic);
    break;
    case KEY_WHILE:
        return CYKLUS(ST,ridic);
    break;
    case KEY_IF:
        return KDYZ(ST,ridic);
    break;
    case KEY_READLN:
        gtoken(ridic);
        if (ridic->token==TP_LBRA){
          gtoken(ridic);
          if (ridic->token==TP_IDENT){
            if (tableSearch(ST,&(ridic->attr_token),0,ridic)){/*zda promena byla inicializovana*/
                printf("generate(KEY_READLN,NULL, NULL,%s)\n",strGetStr(&ridic->attr_token));
                gtoken(ridic);
                if (ridic->token==TP_RBRA){
                    gtoken(ridic);
                    return 1;
                }
            }error(ST,TAB_ERR,ridic);
          }
        }
    break;
    case KEY_WRITE:
        gtoken(ridic);
        if (ridic->token==TP_LBRA){
            gtoken(ridic);
            if (VYPIS(ST,ridic)){
                if (ridic->token==TP_RBRA){
                    gtoken(ridic);
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        return SLOZ(ST,ridic);
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (tGlobSymbolTable *ST,Tridic *ridic){
     if (ridic->token == KEY_BEGIN){
       gtoken(ridic);

       if (PRVNI(ST,ridic)){
            if (ridic->token== KEY_END){
                gtoken(ridic);
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (tGlobSymbolTable *ST,Tridic *ridic){

    if (ridic->token==KEY_END){
        return 1;

    }else {
        if ((ridic->token==TP_IDENT)||(ridic->token==KEY_WHILE)|| (ridic->token==KEY_IF)
        ||(ridic->token==KEY_READLN)||(ridic->token==KEY_WRITE)||(ridic->token==KEY_BEGIN)){
            return POKYN(ST,ridic) && DALSI(ST,ridic);

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (tGlobSymbolTable *ST,Tridic *ridic){
	if (ridic->token==KEY_END){
		return 1;
	}else {
		if (ridic->token==TP_SEM){
			gtoken(ridic);
			return POKYN(ST,ridic) && DALSI(ST,ridic);
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (tGlobSymbolTable *ST,Tridic *ridic){
	if (ridic->token==TP_IDENT) {
       if (tableSearch(ST,&(ridic->attr_token),1,ridic)){

            gtoken(ridic);
            if (ridic->token==TP_SGNMNT){
                gtoken(ridic);
                if( 1/*VYRAZ(ST,ridic)*/){
                    printf("generate(TP_PRIRAZENI,co,NULL, KAM)\n");
                    return 1;
                }
            }

        }else {error(ST,TAB_ERR,ridic);}

	}

   return 0;
}

/*<GLOBDEK>		->	var id : <TYPE> ; <GLOBDEKDAL>*/
/*<GLOBDEK>		->	eps*/
int GLOBDEK (tGlobSymbolTable *ST,Tridic *ridic){

	if ((ridic->token==KEY_FUNCTION)|| (ridic->token==KEY_BEGIN)){
		return 1;
	}else {
		if ((ridic->token==KEY_VAR)){
			gtoken(ridic);
			if ((ridic->token==TP_IDENT)){
				pomoc(ridic);
				gtoken(ridic);
				if (ridic->token==TP_COL){
					gtoken(ridic);
					if (TYPE(ST,ridic)){
                        if   (GlobTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                            if (ridic->token==TP_SEM){
                                gtoken(ridic);
                                return GLOBDEKDAL(ST,ridic);
                            }
                        }
					}
				}
			}
		}
	}


return 0;
}

/*<GLOBDEKDAL>	->	id : <TYPE> ;  <GLOBDEKDAL>*/
/*<GLOBDEKDAL>	->	eps*/
int GLOBDEKDAL (tGlobSymbolTable *ST,Tridic *ridic){
	if ((ridic->token==KEY_FUNCTION)|| (ridic->token==KEY_BEGIN)){
		return 1;

	}else {
		if ((ridic->token==TP_IDENT)){
             pomoc(ridic);
			gtoken(ridic);
			if (ridic->token==TP_COL){
				gtoken(ridic);
				if (TYPE(ST,ridic)){
				     if (GlobTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                        if (ridic->token==TP_SEM){
                            gtoken(ridic);
                            return GLOBDEKDAL(ST,ridic);
                        }
				}
				}

			}
		}
	}
return 0;
}

/*<TYPE>		->	real*/
/*<TYPE>		->	string*/
/*<TYPE>		->	integer*/
/*<TYPE>		->	boolean*/
int TYPE (tGlobSymbolTable *ST,Tridic *ridic){

	switch(ridic->token){
		case KEY_REAL:
            typide=TP_REAL;
			gtoken(ridic);
			return 1;
		break;
		case KEY_STRING:
		    typide=TP_STRING;
			gtoken(ridic);
			return 1;
		break;
		case KEY_INTEGER:
		    typide=TP_INT;
			gtoken(ridic);
			return 1;
		break;
		case KEY_BOOLEAN:
		    typide=BOOLEAN;
			gtoken(ridic);
			return 1;
		break;
	}
return 0;
}

/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (tGlobSymbolTable *ST,Tridic *ridic){
	if ((ridic->token==TP_IDENT)||(ridic->token==TP_STRING)||(ridic->token==TP_CHAR)||(ridic->token==TP_REAL)||(ridic->token==TP_REAL_EXP)||(ridic->token==TP_INT)){
            if (ridic->token==TP_IDENT) {
                    if (tableSearch(ST,&(ridic->attr_token),0,ridic));else error(ST,TAB_ERR,ridic);


            }
            printf("generate(KEY_WRITE,%s,NULL, KAM)\n",strGetStr(&ridic->attr_token));
			gtoken(ridic);
			return DVYPIS(ST,ridic);
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/

int DVYPIS (tGlobSymbolTable *ST,Tridic *ridic){
	if (ridic->token==TP_RBRA){
		return 1;
	}else {
		if (ridic->token==TP_COMMA){
            gtoken(ridic);
			return VYPIS(ST,ridic);
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (tGlobSymbolTable *ST,Tridic *ridic){
	if ( (ridic->token==KEY_BEGIN)){
		return 1;
	}else {
		if ((ridic->token==KEY_VAR)){
			gtoken(ridic);
			if ((ridic->token==TP_IDENT)){
                pomoc(ridic);
				gtoken(ridic);
				if (ridic->token==TP_COL){
					gtoken(ridic);
					if (TYPE(ST,ridic)){
                         if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                            if (ridic->token==TP_SEM){
                                gtoken(ridic);
                                return DEKDAL(ST,ridic);
                            }
                        }
					}
				}
			}
		}
	}


return 0;
}
/*<DEKDAL>	->	id : <TYPE> ;  <DEKDAL>*/
/*<DEKDAL>	->	eps*/
int DEKDAL (tGlobSymbolTable *ST,Tridic *ridic){
	if ( (ridic->token==KEY_BEGIN)){
		return 1;
	}else {
		if ((ridic->token==TP_IDENT)){
		    pomoc(ridic);
			gtoken(ridic);
			if (ridic->token==TP_COL){
				gtoken(ridic);
				if (TYPE(ST,ridic)){
                     if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                        if (ridic->token==TP_SEM){
                            gtoken(ridic);
                            return DEKDAL(ST,ridic);
                        }
                    }
				}
			}
		}
	}
return 0;
}




void generateVariable(string *var)
{
  strClear(var);
  strAddChar(var, '$');
  int i;
  i = counterVar;
  while (i != 0)
  {
    strAddChar(var, (char)(i % 10 + '0'));
    i = i / 10;
  }
  counterVar ++;
}

int key(string *klic,string *master){
    int delka;
    int i=0;


    if (!(strCmpString(klic,master))){
        //printf("asasas\n");
        return 0;

    }else {;
        if (strGetLength(klic)>strGetLength(master)){
            delka=strGetLength(master);
        }else delka=strGetLength(klic);

        while ((i<delka)) {
            if (klic->str[i]==master->str[i]) {

                i++;
            }else {
                if (klic->str[i]>master->str[i]){
                    return 2;
                }else return 1;
            }
        }
        if (strGetLength(master)<strGetLength(klic)) {
            return 2;
        }else return 1;

    }

}
/* 																marek*/
void error(tGlobSymbolTable *ST,int error_num,Tridic *ridic){
    int in=1;

    if (ST!=NULL){/*pokud neni globalni tabulka szmbolu prazdna*/
        printf("zavolano mazani\n");
        sGlobTableItem *koren;
        koren=ST->first;/*nastavim prvni prvek*/
        TableFree(ST, ridic, koren,&in);/*yavolam volani tabulek*/
        if (!in && error_num==0) {/*pokud je nedefinovaná funkce a zaroveò pokud je program validní*/
                error_num=TAB_ERR;/*generuj chybu v tabulce*/
        }
    }
     if (error_num!=0)printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line());
    strFree(&(ridic->attr_token));/*mazani ridicich promenich*/
    strFree(&(ridic->nazev_func));
    strFree(&(ridic->nazev_ident));
     strFree(&(ridic->typarg));
     printf("provadim free nad ridic\n");
     free(ridic);/*mazani ridici struktury*/
    fclose(soubor);/*zavirani souboru*/
    switch (error_num){
        case LEX_ERR:
            exit(1);
        break;
        case SYN_ERR:
            exit(2);
        break;
        case TAB_ERR:
            exit(3);
        break;
        case SEM_ERR:
            exit(4);
        break;
        case OSEM_ERR:
            exit(5);
        break;

        case RUNN_IN_ERR:
            exit(6);
        break;
        case RUNN_NOIN_ERR:
            exit(7);
        break;
         case RUNN_ZERODI_ERR:
            exit(8);
        break;
        case OTHER_ERR:
            exit(9);
        break;
        case OTHER_RUNN_ERR:
            exit(99);
        break;
        case 0:
            exit (0);
        break;

    }

}
