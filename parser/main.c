/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
int pom;
string iden;
string funciden;
int typide;
FILE *soubor;
int counterVar = 1;

void gtoken(){
     strFree(&attr);
    if ((strInit(&attr))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }
      token=get_token(soubor,&hodnota,&attr,&error);

}
void pomoc(){

    pom=strCopyString(&iden,&attr);
}
int main()
{
    strInit(&attr);
    strInit(&iden);
    strInit(&funciden);
    generateVariable(&iden);
    tGlobSymbolTable ST;
    TableInit(&ST);
    soubor = fopen("text.txt", "r");

    if (START(&ST)) {
        printf("i tyhle hovadiny jsou spravne");

    }
    else{
        printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line() );
    }

    fclose(soubor);
    strFree(&attr);
    return 4;
}
int START (tGlobSymbolTable *ST){
    gtoken();



    if ((token == KEY_BEGIN) || (token ==KEY_VAR ) || (token == KEY_FUNCTION)) {
      if ((GLOBDEK(&ST)) && (FUNC(&ST)) && (SLOZ(&ST))) {
            if (token==TP_DOT){
                 gtoken();
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (tGlobSymbolTable *ST){

   if ((token == KEY_BEGIN)){
        return 1;
   }else {
   if ((token==KEY_FUNCTION)){
       gtoken();
       if (token==TP_IDENT){
            pom=strCopyString(&funciden,&attr);
            gtoken();
            if (token==TP_LBRA){
                gtoken();
                if (ARG(&ST)) {
                    if (token==TP_RBRA){
                        gtoken();
                        if (token==TP_COL){
                            gtoken();
                            return TYPE(&ST) && FORWAR(&ST);
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
int FORWAR (tGlobSymbolTable *ST){

    if (token==TP_SEM){
        gtoken();
        if ((DEK(&ST))&& (SLOZ(&ST))) {
            if (token==TP_SEM){
                gtoken();
                return FUNC(&ST);
            }
        }
    }else{
        if (token==KEY_FORWARD){
            gtoken();
            if (token==TP_SEM){
                gtoken();
                return FUNC(&ST);
            }
        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (tGlobSymbolTable *ST){
    if (token==TP_RBRA){
        return 1;
    }else{
        if (token==TP_IDENT){
            pomoc();
            printf("1");
            gtoken();
            if (token==TP_COL){
                gtoken();

                if  (TYPE (&ST)) {

                   if (GlobTableInsert(ST,&iden,typide)){
                            return ARGDAL(&ST);
                        }


                }
            }
        }
    }
    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (tGlobSymbolTable *ST){
     if (token==TP_RBRA){
        return 1;
    }else{
        if (token==TP_SEM){
            gtoken();
            if (token==TP_IDENT){
                pomoc();
                gtoken();
                if (token==TP_COL){
                    gtoken();
                    if ( TYPE(&ST)) {
                          if (GlobTableInsert(ST,&iden,typide)){
                            return ARGDAL(&ST);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (tGlobSymbolTable *ST){
    if (token==KEY_WHILE){
        gtoken();
        if(VYRAZ(&ST)){
            if (token==KEY_DO)
                gtoken();
                return SLOZ(&ST);
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (tGlobSymbolTable *ST){

    if (token==KEY_IF){
        gtoken();
        if(VYRAZ(&ST)){
            if (token==KEY_THEN){
                gtoken();
                if (SLOZ(&ST)){
                    return ELSEP(&ST);
                }
            }
        }
    }
return 0;
}

/*<ELSE>		->  	else  <SLOZ>*/
/*<ELSE>		-> 	eps*/
int ELSEP (tGlobSymbolTable *ST){
    if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)||(token==ST_SEM)
    ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)||(token==KEY_END)){
       return 1;
    }else {

        if (token==KEY_ELSE){
            gtoken();
            return SLOZ(&ST);
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
int POKYN (tGlobSymbolTable *ST){
  switch (token ){
    case TP_IDENT:
        return PRIKAZ(&ST);
    break;
    case KEY_WHILE:
        return CYKLUS(&ST);
    break;
    case KEY_IF:
        return KDYZ(&ST);
    break;
    case KEY_READLN:
        gtoken();
        if (token==TP_LBRA){
          gtoken();
          if (token==TP_IDENT){
            gtoken();
            if (token==TP_RBRA){
                gtoken();
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        gtoken();
        if (token==TP_LBRA){
            gtoken();
            if (VYPIS(&ST)){
                if (token==TP_RBRA){
                    gtoken();
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        return SLOZ(&ST);
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (tGlobSymbolTable *ST){
     if (token == KEY_BEGIN){
       gtoken();;
       if (PRVNI(&ST)){
            if (token== KEY_END){
                gtoken();
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (tGlobSymbolTable *ST){

    if (token==KEY_END){
        return 1;

    }else {
        if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)
        ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)){
            return POKYN(&ST) && DALSI(&ST);

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (tGlobSymbolTable *ST){
	if (token==KEY_END){
		return 1;
	}else {
		if (token==TP_SEM){
			gtoken();
			return POKYN(&ST) && DALSI(&ST);
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (tGlobSymbolTable *ST){
	if (token==TP_IDENT) {
       // if (searchvar(&attr, 0)){
            gtoken();
            if (token==TP_SGNMNT){
                gtoken();
                return VYRAZ(&ST);
         //   }
        }
	}
return 0;
}

/*<GLOBDEK>		->	var id : <TYPE> ; <GLOBDEKDAL>*/
/*<GLOBDEK>		->	eps*/
int GLOBDEK (tGlobSymbolTable *ST){

	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==KEY_VAR)){
			gtoken();
			if ((token==TP_IDENT)){
				pomoc();
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE(&ST)){
                        if   (GlobTableInsert(ST,&iden,typide)){
                            if (token==TP_SEM){
                                gtoken();
                                return GLOBDEKDAL(&ST);
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
int GLOBDEKDAL (tGlobSymbolTable *ST){
	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		return 1;

	}else {
		if ((token==TP_IDENT)){
             pomoc();
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE(&ST)){
				     if (GlobTableInsert(ST,&iden,typide)){
                        if (token==TP_SEM){
                            gtoken();
                            return GLOBDEKDAL(&ST);
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
int TYPE (tGlobSymbolTable *ST){

	switch(token){
		case KEY_REAL:
            typide=REAL;
			gtoken();
			return 1;
		break;
		case KEY_STRING:
		    typide=STRING;
			gtoken();
			return 1;
		break;
		case KEY_INTEGER:
		    typide=INTEGER;
			gtoken();
			return 1;
		break;
		case KEY_BOOLEAN:
		    typide=BOOLEAN;
			gtoken();
			return 1;
		break;
	}
return 0;
}

/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (tGlobSymbolTable *ST){
	if ((token==TP_IDENT)||(token==TP_STRING)||(token==TP_CHAR)||(token==TP_REAL)||(token==TP_REAL_EXP)||(token==TP_INT)){
			gtoken();
			return DVYPIS(&ST);
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/

int DVYPIS (tGlobSymbolTable *ST){
	if (token==TP_RBRA){
		return 1;
	}else {
		if (token==TP_COMMA){
            gtoken();
			return VYPIS(&ST);
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (tGlobSymbolTable *ST){
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==KEY_VAR)){
			gtoken();
			if ((token==TP_IDENT)){
                pomoc();
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE(&ST)){
                         if (GlobTableInsert(ST,&iden,typide)){
                            if (token==TP_SEM){
                                gtoken();
                                return DEKDAL(&ST);
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
int DEKDAL (tGlobSymbolTable *ST){
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==TP_IDENT)){
		    pomoc();
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE(&ST)){
                     if (GlobTableInsert(ST,&iden,typide)){
                        if (token==TP_SEM){
                            gtoken();
                            return DEKDAL(&ST);
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


