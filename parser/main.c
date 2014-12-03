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
    ridic=malloc(sizeof (Tridic));
    tGlobSymbolTable ST;
    sGlobTableItem *koren;
    strInit(&(ridic->attr_token));
    strInit(&(ridic->nazev_ident));
    strInit(&(ridic->nazev_func));
    GlobTableInit(&ST,ridic);
    printf("sdsd\n");


    koren=ST.first;
    soubor = fopen("text.txt", "r");



    if (START(&ST,ridic)) {
        printf("i tyhle hovadiny jsou spravne");

    }
    else{
        printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line());
    }
    koren=ST.first;

  //  RamecCopy(koren->link, RamecInit());
    GlobVypis(&ST,ridic, koren);
    //PopTopR(&poma);


    koren=ST.first;
    printf("****************************************************************");



    error(&ST,0,ridic);
    return 0;
}
int START (tGlobSymbolTable *ST,Tridic *ridic){
    gtoken(ridic);
    if ((ridic->token == KEY_BEGIN) || (ridic->token ==KEY_VAR ) || (ridic->token == KEY_FUNCTION)) {
      if ((GLOBDEK(ST,ridic)) && (FUNC(ST,ridic)) && (SLOZ(ST,ridic))) {
            if (ridic->token==TP_DOT){
                 gtoken(ridic);
                return 1;
            }
        }
    }
error(ST,SYN_ERR,ridic);
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
            pom=strCopyString(&(ridic->nazev_func),&(ridic->attr_token));

        if (GlobTableInsert(ST,&(ridic->nazev_func),FUNCTION_HEADER,ridic)){
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
                                if (LokTableInsert(ST,NULL,typide,ridic)){
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
             printf("generate(FUNCTION_BEGIN,%s,NULL);\n",strGetStr(&(ridic->nazev_func)));
            if  (SLOZ(ST,ridic)){
                if (ridic->token==TP_SEM){
                    if (GlobTableInsert(ST,NULL,FUNCTION_END,ridic));
                    printf("generate(FUNCTION_END,%s,NULL);\n",strGetStr(&(ridic->nazev_func)));
                    gtoken(ridic);
                    return FUNC(ST,ridic);
                }
            }

        }
    }else{
        if (ridic->token==KEY_FORWARD){
            if (GlobTableInsert(ST,NULL,FUNCTION_FORWARD,ridic)){
            //  printf("FUNCTION_FORWARD\n"); // generate(KEY_FORWARD,ridic->nazev_func,NULL,NULL);
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
                   if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
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
                         if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
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
           printf("generate(WHILE_BEGIN,NULL,NULL);\n");
        if(1/*VYRAZ(ST,ridic)*/){
             printf("generate(WHILE_COND,Hubli,NULL);\n");
            if (ridic->token==KEY_DO)
                gtoken(ridic);
                if ( SLOZ(ST,ridic)){
                  printf("generate(WHILE_END,NULL,NULL);\n"); // generate(WHILE_END,ridic->nazev_func,NULL,NULL);
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
            printf("generate(KEY_COND,HUBLI,NULL);\n");
            if (ridic->token==KEY_THEN){

                gtoken(ridic);
                if (SLOZ(ST,ridic)){

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

        if (ridic->token==KEY_ELSE){
           printf("generate(ELSE_BEGIN,NULL,NULL);\n"); // generate(ELSE_BEGIN,ridic->nazev_func,NULL,NULL);
            gtoken(ridic);
            if( SLOZ(ST,ridic)){
                printf("generate(ELSE_END,NULL,NULL);\n");// generate(ELSE_END,ridic->nazev_func,NULL,NULL);
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
            gtoken(ridic);
            if (ridic->token==TP_RBRA){
                gtoken(ridic);
                return 1;
            }
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
            printf("generate(TP_SGNMNT,HUBLI, KAM)\n");
            gtoken(ridic);
            if (ridic->token==TP_SGNMNT){
                gtoken(ridic);
                return VYRAZ(ST,ridic);
            }

        }

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
                        //printf("asasasasasa");
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
      printf("zac**\n");
    if (ST!=NULL){
        printf("yavolano mazani\n");
        sGlobTableItem *koren;
        koren=ST->first;
        TableFree(ST, ridic, koren);
    }
    printf("sdsd**\n");
    strFree(&(ridic->attr_token));
    strFree(&(ridic->nazev_func));
    strFree(&(ridic->nazev_ident));
     strFree(&(ridic->typarg));
     printf("provadim free nad ridic\n");
     free(ridic);
fclose(soubor);
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

    }
    exit(0);
}
