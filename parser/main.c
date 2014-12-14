/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
int pom;
int errora;

int typide;
FILE *soubor;
int counterVar = 1;

int gtoken(Tridic *ridic){
     strFree(&(ridic->attr_token));

    if ((strInit(&(ridic->attr_token)))==1)
        {
            error(NULL,OTHER_RUNN_ERR,ridic);
        }

      ridic->token=get_token(soubor,&(ridic->hodnota),&(ridic->attr_token));
      return ridic->token;
}
void pomoc(Tridic *ridic){

    pom=strCopyString(&(ridic->nazev_ident),&(ridic->attr_token));
}
int main()
{
    Tridic *ridic;
    //sRamec *zkopirovanyramec;
    /*hubli string a;*/
    trojinit();
    if ((ridic=malloc(sizeof (Tridic)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
    tGlobSymbolTable ST;
    //ST=malloc(sizeof(tGlobSymbolTable));
    ST.first=NULL;
    strInit(&(ridic->attr_token));
    strInit(&(ridic->nazev_ident));
    strInit(&(ridic->nazev_func));
    GlobTableInit(&ST,ridic);

    /*hubli generateVariable(&a);*/



    soubor = fopen("text.txt", "r");

    /* hubli printf("%s******\n",strGetStr(&a));*/

    START(&ST,ridic);





    trojvypis();
    Interpret(&ST);


    error(&ST,0,ridic);

    return 0;
}
/*<START>   ->  <GLOBDEK>   <FUNC>  <SLOZ>*/
int START (tGlobSymbolTable *ST,Tridic *ridic){
    gtoken(ridic);
    Generate(KEY_START,NULL,NULL,NULL);
    if ((ridic->token == KEY_BEGIN) || (ridic->token ==KEY_VAR ) || (ridic->token == KEY_FUNCTION)) {   /*pokud je prvni token begin, var nebo function */
      if ((GLOBDEK(ST,ridic)) && (FUNC(ST,ridic)) ){
          Generate(HLAVNI,NULL,NULL,NULL);
          if (SLOZ(ST,ridic)) {    /*rekuryivni sestup*/
            if (ridic->token==TP_DOT){/*pokud je posledni token tecka*/
                 gtoken(ridic);
                return 1;
            }
          }
      }
    }
    error(ST,SYN_ERR,ridic);/*byl naleyen error v syn analyze*/
    return 0;
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
            //Generate(FUNCTION_HEADER,ridic->nazev_func,NULL,NULL);
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
             Generate(FUNCTION_BEGIN,&(ridic->nazev_func),NULL,NULL);
            if  (SLOZ(ST,ridic)){
                if (ridic->token==TP_SEM){
                    if (GlobTableInsert(ST,NULL,FUNCTION_END,ridic));/*oznaceni konce funkce pro glob tabulku*/
                    Generate(FUNCTION_END,&(ridic->nazev_func),NULL,NULL);
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
     int konst;
    pomv *pom;
     if ((pom = (pomv*) malloc(sizeof(pomv)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
    if (ridic->token==KEY_WHILE){
        gtoken(ridic);
           Generate(WHILE_BEGINLAB,NULL,NULL,NULL);
        pom=VYRAZ(ST,ridic,0,&konst);
         if (pom->type==BOOLEAN){
             Generate(WHILE_BEGIN,NULL,&pom->nazev,NULL);
            if (ridic->token==KEY_DO){
                gtoken(ridic);
                if ( SLOZ(ST,ridic)){
                  Generate(WHILE_END,NULL,NULL,NULL);
                   Generate(WHILE_ENDLAB,NULL,NULL,NULL);
                   strFree(&(pom->nazev));
                   free(pom);
				  return 1;
                }
            }
         }else error(ST,SEM_ERR,ridic);
    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (tGlobSymbolTable *ST,Tridic *ridic){
    int konst=0;
    pomv *pom;


     if ((pom = (pomv*) malloc(sizeof(pomv)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
     strInit(&(pom->nazev));
    if (ridic->token==KEY_IF){
        gtoken(ridic);
        pom=VYRAZ(ST,ridic,0,&konst);
         if (pom->type==BOOLEAN){

            Generate(IF_BEGIN,NULL,&pom->nazev,NULL);
            if (ridic->token==KEY_THEN){

                gtoken(ridic);
                if (SLOZ(ST,ridic)){
                    Generate(IF_END,NULL,NULL,NULL);
                    strFree(&(pom->nazev));
                    free(pom);
                    return ELSEP(ST,ridic);
                }
            }
         }else error(ST,SEM_ERR,ridic);

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
           Generate(ELSE_BEGIN,NULL,NULL,NULL);
            gtoken(ridic);
            if( SLOZ(ST,ridic)){
                Generate(ELSE_END,NULL,NULL,NULL);
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
            if (tableSearch(ST,&(ridic->attr_token),1,ridic)){/*zda promena byla inicializovana*/
                Generate(I_READ,NULL, NULL,&ridic->attr_token);
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
    int konst=0;
    int poc=0;
    int poc2;
    pomv *attrtyp;/*nazev a typ kam se ma priradit*/
    pomv *pom;
   if (( attrtyp = (pomv*) malloc(sizeof(pomv)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*alokovani mista pro prirazeni*/
    if ((pom = (pomv*) malloc(sizeof(pomv)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
    strInit(&(pom->nazev));
    strInit(&(attrtyp->nazev));
    string poms1;
    sGlobTableItem *pomg;
    strInit(&poms1);
    pomg=ST->first;

	if (ridic->token==TP_IDENT) {/*pokud se prirazuje do promenne*/
        strCopyString(&(attrtyp->nazev),&(ridic->attr_token));/*zalohujeme nazev promenne*/
        if ((attrtyp->type=tableSearch(ST,&(ridic->attr_token),3,ridic))){/*zalohujeme typ promenne*/
            gtoken(ridic);
            if (ridic->token==TP_SGNMNT){/*pokud je na vstupu pprirazovaci prikaz*/
                gtoken(ridic);
                if ( !tableSearchGlob(ridic,&pomg,&(ridic->attr_token))&& pomg->data.typ==FUNCTION_HEADER){/*pokud se jedna o volani fce*/
                    strCopyString(&ridic->nazev_ident,&ridic->attr_token);/*zaloha nazvu fce*/
                    Generate(FUNC_VOL,&ridic->nazev_ident,NULL,NULL);/*budou nasledovat argumenty fce*/
                    gtoken(ridic);
                    if (ridic->token==TP_LBRA){/*pokud je token leva zavorka*/
                        gtoken(ridic);
                        if  (ARGVOL(ST,ridic,&pomg->arg,&poc)){/*paramatry fce*/
                            poc2=strGetLength(&pomg->arg);/*ulozime pocet argumentu*/
                            switch ((pomg->arg.str[poc2-1])){/*uloyime navratovy tzp*/
                                case 'i':
                                    pom->type=TP_INT;
                                break;
                                case 'r':
                                    pom->type=TP_REAL;
                                break;
                                case 'b':
                                    pom->type=BOOLEAN;
                                break;
                                case 's':
                                    pom->type=TP_STRING;
                                break;
                            }

                            strCopyString(&(pom->nazev),&(ridic->nazev_ident));
                        }
                    }else return 0;
                    Generate(JMP_FCE,&ridic->nazev_ident,NULL,NULL);/*konec volani fce*/
                }else{
                    pom=VYRAZ(ST,ridic,0,&konst);
                }
                if (attrtyp->type==pom->type){/*porovname navratovy typ*/
                    if (konst==1){/*pokud jde o konstatnu*/
                        switch (pom->type){
                            case TP_REAL:
                                strAddChar(&poms1,'r');
                            break;
                            case BOOLEAN:
                                strAddChar(&poms1,'b');
                            break;
                            case TP_STRING:
                                strAddChar(&poms1,'s');
                            break;
                            case TP_INT:
                                strAddChar(&poms1,'i');
                            break;
                            }
                    }else  strAddChar(&poms1,'p');/*promenna*/


                    if ((attrtyp->type=tableSearch(ST,&(attrtyp->nazev),1,ridic)));
                    Generate(ASSIGN,&(pom->nazev),&poms1,&(attrtyp->nazev) );
                    strFree(&poms1);
                    strFree(&(pom->nazev));
                    strFree(&(attrtyp->nazev));
                    free(pom);
                    free(attrtyp);
                    return 1;
                }error(ST,SEM_ERR,ridic);
            }
        }else {error(ST,TAB_ERR,ridic);}
	}
   return 0;
}
/*54		<ARGVOL>	->	eps
55.		<ARGVOL>	->	<VYRAZ>  <ARGVOLDAL> */

int ARGVOL (tGlobSymbolTable *ST,Tridic *ridic,string *poms,int *poc){
    int konst=0;
    pomv *pom;
    string poms1;
    string poms2;

    *poc=0;
    int druh=0;
    if (ridic->token==TP_SEM || ridic->token==TP_RBRA || ridic->token==KEY_END ){/*pokud je token prava zavorka*/
         if (ridic->token==TP_SEM && *poc==0) error(ST,SYN_ERR,ridic);
         if (ridic->token==KEY_END && *poc==0) error(ST,SYN_ERR,ridic);
        if (ridic->token==TP_RBRA ) {gtoken(ridic);}


        return 1;
    }else{
        (*poc)++;/*zvys pocitadlo argumentu*/
         if (*poc==strGetLength(poms)-1){/*pokud se jedna o posledni token*/
            druh=1;

        }else if (*poc>strGetLength(poms)-1){/*pokud je vice parametru nez ma definice fce*/
            error(ST,SEM_ERR,ridic);
        }
        pom=VYRAZ(ST,ridic,druh,&konst);/*zpracuj argument*/
        TypeKontrol(ST,ridic,poms,*poc,pom);/*proved kontrolu typu*/
        strInit(&poms1);
        strInit(&poms2);
        if (konst==1){/*pokud se jedna o konstantu*/
            switch (pom->type){
                case TP_REAL:
                    strAddChar(&poms1,'r');
                break;
                case BOOLEAN:
                    strAddChar(&poms1,'b');
                break;
                case TP_STRING:
                    strAddChar(&poms1,'s');
                break;

                case TP_INT:
                    strAddChar(&poms1,'i');
                break;

            }
            printf("konst\n");
        }else  strAddChar(&poms1,'p');/*jinak promenna*/
        char str[15];
        sprintf(str, "%d", *poc);
        strAddStr(&poms2,str);
        printf("%s****",strGetStr(&poms1));
        Generate(ARG_VOL,&pom->nazev,&poms1,&poms2 );
        strFree(&poms1);
        strFree(&poms2);
        strFree(&pom->nazev);
        free(pom);
        return ARGVOLDAL(ST,ridic,poms,poc);
    }
    error(ST,SYN_ERR,ridic);
return 0;

}
/*<ARGVOLDAL>	->	eps
	<ARGVOLDAL>	->	, <VYRAZ>  <ARGVOLDAL>*/
int ARGVOLDAL (tGlobSymbolTable *ST,Tridic *ridic,string *poms,int *poc){
    int konst=0;
    pomv *pom;
    string poms1;
    string poms2;
    int druh=0;

    if (ridic->token==TP_SEM|| ridic->token==KEY_END){
        return 1;
    }else{
        if (ridic->token==TP_COMMA){
            (*poc)++;
            if (*poc==strGetLength(poms)-1){
                druh=1;
            }else if (*poc>strGetLength(poms)-1){
                error(ST,SEM_ERR,ridic);
            }
            gtoken(ridic);
            pom=VYRAZ(ST,ridic,druh,&konst);
            TypeKontrol(ST,ridic,poms,*poc,pom);
            strInit(&poms1);
            strInit(&poms2);
            if (konst==1){
                switch (pom->type){
                    case TP_REAL:
                        strAddChar(&poms1,'r');
                    break;
                    case BOOLEAN:
                        strAddChar(&poms1,'b');
                    break;
                    case TP_STRING:
                        strAddChar(&poms1,'s');
                    break;
                    case TP_INT:
                        strAddChar(&poms1,'i');
                    break;
                }
            }else  strAddChar(&poms1,'p');
            char str[15];
            sprintf(str, "%d", *poc);
            strAddStr(&poms2,str);
             printf("%s****",strGetStr(&poms1));
            Generate(ARG_VOL,&pom->nazev,&poms1,&poms2 );
            strFree(&poms1);
            strFree(&poms2);
            strFree(&pom->nazev);
            free(pom);
            return ARGVOLDAL(ST,ridic,poms,poc);
        }
    }

error(ST,SYN_ERR,ridic);
return 0;
}
void TypeKontrol(tGlobSymbolTable *ST,Tridic *ridic,string *poms,int poc, pomv *pom){
    switch (poms->str[poc-1]){
        case 'i':
            if (pom->type!=TP_INT){
                error(ST,SEM_ERR,ridic);
            }
        break;
        case 'r':
              if (pom->type!=TP_REAL){
                error(ST,SEM_ERR,ridic);
            }
        break;
        case 'b':
              if (pom->type!=BOOLEAN){
                error(ST,SEM_ERR,ridic);
            }
        break;
         case 's':
              if (pom->type!=TP_STRING){
                error(ST,SEM_ERR,ridic);
            }
        break;
    }
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
    string pom;
	if ((ridic->token==TP_IDENT)||(ridic->token==TP_STRING)||(ridic->token==TP_CHAR)||(ridic->token==TP_REAL)||(ridic->token==TP_REAL_EXP)||(ridic->token==TP_INT)){
            if (ridic->token==TP_IDENT) {
                    if (!tableSearch(ST,&(ridic->attr_token),0,ridic)) {error(ST,TAB_ERR,ridic);}


            }
            strInit(&pom);
            switch (ridic->token){
                case TP_IDENT:
                    strAddChar(&pom,'p');
                break;
                case TP_REAL:
                    strAddChar(&pom,'r');
                break;
                case BOOLEAN:
                    strAddChar(&pom,'b');
                break;
                case TP_STRING:
                    strAddChar(&pom,'s');
                break;

                case TP_INT:
                    strAddChar(&pom,'i');
                break;

            }
            Generate(I_WRITE,&ridic->attr_token,&pom, NULL);
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
    strInit(var);
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

int key(string *klic,string *master){/*generace jedinečného klíče pro binární strom*/
    int delka;
    int i=0;


    if (!(strCmpString(klic,master))){/*pokud jsou si řetězce rovny*/
        return 0;

    }else {
        if (strGetLength(klic)>strGetLength(master)){/*pokud je délka prvního řetězce delší než druhého*/
            delka=strGetLength(master);/*nastav délku podle kratšího*/
        }else delka=strGetLength(klic);

        while ((i<delka)) {/*dokud nejsme na konci kratšího řetezce*/
            if (klic->str[i]==master->str[i]) {/*porovnej ordinální hodnotu jednoho znaku*/

                i++;/*pokud se rovnají, postup na další znak*/
            }else {
                if (klic->str[i]>master->str[i]){/*pokud je ordinální hodnota znaku prvního řetezce větší než druhého*/
                    return 2;
                }else return 1;
            }
        }
        if (strGetLength(master)<strGetLength(klic)) {/*pokud je druhý retezec kratší než první*/
            return 2;
        }else return 1;

    }

}
/* 																marek*/
void error(tGlobSymbolTable *ST,int error_num,Tridic *ridic){
    int in=1;
if (ST!=NULL){
    if (ST->first!=NULL){/*pokud neni globalni tabulka szmbolu prazdna*/

        sGlobTableItem *koren;
        koren=ST->first;/*nastavim prvni prvek*/
        TableFree(ST, ridic, koren,&in);/*yavolam volani tabulek*/
        if (!in && error_num==0) {/*pokud je nedefinovaná funkce a zaroveò pokud je program validní*/
                error_num=TAB_ERR;/*generuj chybu v tabulce*/
        }
    }
     if (error_num!=0)printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line());
     if (error_num!=LEX_ERR && OTHER_RUNN_ERR){
        strFree(&(ridic->attr_token));/*mazani ridicich promenich*/
        strFree(&(ridic->nazev_func));
        strFree(&(ridic->nazev_ident));

        free(ridic);/*mazani ridici struktury*/

        fclose(soubor);/*zavirani souboru*/

     }

     //free(ST);

}
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
