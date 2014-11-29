/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
int pom;


int typide;
FILE *soubor;
int counterVar = 1;

void gtoken(Tridic *ridic){
     strFree(&(ridic->attr_token));
    if ((strInit(&(ridic->attr_token)))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }
      token=get_token(soubor,&hodnota,&(ridic->attr_token),&error);

}
void pomoc(Tridic *ridic){

    pom=strCopyString(&(ridic->nazev_ident),&(ridic->attr_token));
}
int main()
{
    Tridic *ridic;
    ridic=malloc(sizeof (Tridic));
    tGlobSymbolTable ST;
    sGlobTableItem *koren;
    strInit(&(ridic->attr_token));
    strInit(&(ridic->nazev_ident));
    strInit(&(ridic->nazev_func));
    GlobTableInit(&ST,ridic);

    soubor = fopen("text.txt", "r");



    if (START(&ST,ridic)) {
        printf("i tyhle hovadiny jsou spravne");

    }
    else{
        printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line() );
    }
    koren=ST.first;
    GlobVypis(&ST,ridic, koren);
  //  TableFree(&ST, ridic);

   fclose(soubor);

    return 4;
}
int START (tGlobSymbolTable *ST,Tridic *ridic){
    gtoken(ridic);
    if (ST->first==NULL){
                            //printf("nulleee\n");
                        }


    if ((token == KEY_BEGIN) || (token ==KEY_VAR ) || (token == KEY_FUNCTION)) {
      if ((GLOBDEK(ST,ridic)) && (FUNC(ST,ridic)) && (SLOZ(ST,ridic))) {
            if (token==TP_DOT){
                 gtoken(ridic);
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (tGlobSymbolTable *ST,Tridic *ridic){

   if ((token == KEY_BEGIN)){
        return 1;
   }else {
   if ((token==KEY_FUNCTION)){
       gtoken(ridic);
       if (token==TP_IDENT){
            pom=strCopyString(&(ridic->nazev_func),&(ridic->attr_token));

        if (GlobTableInsert(ST,&(ridic->nazev_func),FUNCTION_HEADER,ridic)){
            gtoken(ridic);
            if (token==TP_LBRA){
                gtoken(ridic);
                if (ARG(ST,ridic)) {
                    if (token==TP_RBRA){
                        gtoken(ridic);
                        if (token==TP_COL){
                            gtoken(ridic);
                           if (TYPE(ST,ridic)) {
                            if (token==TP_SEM){
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

    if (token==KEY_VAR|| token==KEY_BEGIN){
        //gtoken();
        printf("sem");
        if ((DEK(ST,ridic))&& (SLOZ(ST,ridic))) {
            if (token==TP_SEM){
                if (GlobTableInsert(ST,NULL,FUNCTION_END,ridic));
                gtoken(ridic);
                return FUNC(ST,ridic);
            }

        }
    }else{
        if (token==KEY_FORWARD){

            gtoken(ridic);
            if (token==TP_SEM){
                gtoken(ridic);

                return FUNC(ST,ridic);
            }

        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (tGlobSymbolTable *ST,Tridic *ridic){
    if (token==TP_RBRA){
        return 1;
    }else{
        if (token==TP_IDENT){
            pomoc(ridic);
            gtoken(ridic);
            if (token==TP_COL){
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
     if (token==TP_RBRA){
        return 1;
    }else{
        if (token==TP_SEM){
            gtoken(ridic);
            if (token==TP_IDENT){
                pomoc(ridic);
                gtoken(ridic);
                if (token==TP_COL){
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
    if (token==KEY_WHILE){
        gtoken(ridic);
        if(VYRAZ(ST,ridic)){
            if (token==KEY_DO)
                gtoken(ridic);
                return SLOZ(ST,ridic);
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (tGlobSymbolTable *ST,Tridic *ridic){

    if (token==KEY_IF){
        gtoken(ridic);
        if(VYRAZ(ST,ridic)){
            if (token==KEY_THEN){
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
    if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)||(token==ST_SEM)
    ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)||(token==KEY_END)){
       return 1;
    }else {

        if (token==KEY_ELSE){
            gtoken(ridic);
            return SLOZ(ST,ridic);
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
  switch (token ){
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
        if (token==TP_LBRA){
          gtoken(ridic);
          if (token==TP_IDENT){
            gtoken(ridic);
            if (token==TP_RBRA){
                gtoken(ridic);
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        gtoken(ridic);
        if (token==TP_LBRA){
            gtoken(ridic);
            if (VYPIS(ST,ridic)){
                if (token==TP_RBRA){
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
     if (token == KEY_BEGIN){
       gtoken(ridic);
       if (PRVNI(ST,ridic)){
            if (token== KEY_END){
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

    if (token==KEY_END){
        return 1;

    }else {
        if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)
        ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)){
            return POKYN(ST,ridic) && DALSI(ST,ridic);

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (tGlobSymbolTable *ST,Tridic *ridic){
	if (token==KEY_END){
		return 1;
	}else {
		if (token==TP_SEM){
			gtoken(ridic);
			return POKYN(ST,ridic) && DALSI(ST,ridic);
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (tGlobSymbolTable *ST,Tridic *ridic){
	if (token==TP_IDENT) {
       if (tableSearch(ST,&(ridic->attr_token),1,ridic)){

            gtoken(ridic);
            if (token==TP_SGNMNT){
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

	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==KEY_VAR)){
			gtoken(ridic);
			if ((token==TP_IDENT)){
				pomoc(ridic);
				gtoken(ridic);
				if (token==TP_COL){
					gtoken(ridic);
					if (TYPE(ST,ridic)){
                        //printf("asasasasasa");
                        if (ST->first==NULL){
                            //printf("nulleee\n");
                        }
                        if   (GlobTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                            if (token==TP_SEM){
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
	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		return 1;

	}else {
		if ((token==TP_IDENT)){
             pomoc(ridic);
			gtoken(ridic);
			if (token==TP_COL){
				gtoken(ridic);
				if (TYPE(ST,ridic)){
				     if (GlobTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                        if (token==TP_SEM){
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

	switch(token){
		case KEY_REAL:
            typide=REAL;
			gtoken(ridic);
			return 1;
		break;
		case KEY_STRING:
		    typide=STRING;
			gtoken(ridic);
			return 1;
		break;
		case KEY_INTEGER:
		    typide=INTEGER;
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
	if ((token==TP_IDENT)||(token==TP_STRING)||(token==TP_CHAR)||(token==TP_REAL)||(token==TP_REAL_EXP)||(token==TP_INT)){
			gtoken(ridic);
			return DVYPIS(ST,ridic);
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/

int DVYPIS (tGlobSymbolTable *ST,Tridic *ridic){
	if (token==TP_RBRA){
		return 1;
	}else {
		if (token==TP_COMMA){
            gtoken(ridic);
			return VYPIS(ST,ridic);
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (tGlobSymbolTable *ST,Tridic *ridic){
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==KEY_VAR)){
			gtoken(ridic);
			if ((token==TP_IDENT)){
                pomoc(ridic);
				gtoken(ridic);
				if (token==TP_COL){
					gtoken(ridic);
					if (TYPE(ST,ridic)){
                         if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                            if (token==TP_SEM){
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
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==TP_IDENT)){
		    pomoc(ridic);
			gtoken(ridic);
			if (token==TP_COL){
				gtoken(ridic);
				if (TYPE(ST,ridic)){
                     if (LokTableInsert(ST,&(ridic->nazev_ident),typide,ridic)){
                        if (token==TP_SEM){
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
    char k,m;

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
