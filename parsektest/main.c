/*!!prosim komenty bez diakritiky, blbne kodovani*/
/*!!neprelozitelne, pracuje se natom*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
string attr;
FILE *soubor;
  int token;
int gtoken(FILE *F, SToken *token ){







     printf("\nJe to typ: %i\n",token);
     printf("String je: %s\n",strGetStr(token->stri));
}
int main()
{
    strInit(&attr);
    soubor = fopen("text.txt", "r");
    printf ("%i",START());

    fclose(soubor);
    strFree(&attr);
    return 4;
}
int START (){




    token=get_token(&attr);
    if ((token == KEY_BEGIN) || (token ==KEY_VAR ) || (token == KEY_FUNCTION)) {
      printf("start2\n");

      if ((GLOBDEK()) && (FUNC()) && (SLOZ())) {
            printf("start3\n");

            if (token==TP_DOT){
                 token=get_token(&attr);
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (){

   if ((token == KEY_BEGIN)){
        printf("FUNC2\n");
        return 1;

   }else {
   if ((token==KEY_FUNCTION)){
        printf("FUNC3\n");
       token=get_token(&attr);
       if (token==TP_IDENT){
            token=get_token(&attr);
            if (token==TP_LBRA){
                token=get_token(&attr);
                if (ARG()) {
                    if (token==TP_RBRA){
                        token=get_token(&attr);
                        if (token==TP_COL){
                            token=get_token(&attr);

                                    return TYPE() && FORWAR();
                        }
                    }

                }
            }
        }
    }
   }
           printf("FUNC3\n");

    return 0;
}


/*<FORWARD> 	->	; <DEK> <SLOZ> ; <FUNC>*/
/*<FORWARD>	->	forward ; <FUNC>*/
int FORWAR (){
    if (token==ST_SEM){
        token=get_token(&attr);
        if ((DEK())&& (SLOZ())) {
            if (token==ST_SEM){
                token=get_token(&attr);
                return FUNC();
            }
        }
    }else{
        if (token==KEY_FORWARD){
            token=get_token(&attr);
            if (token==ST_SEM){
                token=get_token(&attr);
                return FUNC();
            }
        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (){
    if (token==TP_RBRA){
        return 1;
    }else{
        if (token==TP_IDENT){
            token=get_token(&attr);
            if (token==TP_COL){
                token=get_token(&attr);
                return TYPE () && ARGDAL();
            }
        }
    }
    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (){
     if (token==TP_RBRA){
        return 1;
    }else{
        if (token==ST_SEM){
            token=get_token(&attr);
            if (token-> type==TP_IDENT){
                token=get_token(&attr);
                if (token==TP_COL){
                    token=get_token(&attr);
                    return TYPE() && ARGDAL();
                }
            }
        }
    }
    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (){
    if (token==KEY_WHILE){
        token=get_token(&attr);
        if(VYRAZ()){
            if (token==KEY_DO)
                token=get_token(&attr);
                return SLOZ();
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){
    if (token==KEY_IF){
        token=get_token(&attr);
        if(VYRAZ()){
            if (token==KEY_THEN){
                token=get_token(&attr);
                if (SLOZ()){
                    return ELSEP();
                }
            }
        }
    }
return 0;
}

/*<ELSE>		->  	else  <SLOZ>*/
/*<ELSE>		-> 	eps*/
int ELSEP (){
    if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)||(token==ST_SEM)
    ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)||(token==KEY_END)){

       return 1;
    }else {
        if (token==KEY_ELSE){
            token=get_token(&attr);
            return SLOZ();
        }
    }
return 0;
}

//<SEKVENCE>	-> 	<POKYN> <SEKVENCE>
//sEKVENCE>	->	eps
//int SEKVENCE (){
//return 0;
//}

/*<POKYN>		->	<CYKLUS>*/
/*<POKYN>		->	<KDYZ>*/
/*<POKYN>		->	<PRIKAZ>*/
/*<POKYN>		->	READLN(id) */
/*<POKYN>		->	WRITE( <VYPIS>)	*/
/*<POKYN>		->	<SLOZ> */
int POKYN (){
  switch (token ){
    case TP_IDENT:
        token=get_token(&attr);
        return PRIKAZ();
    break;
    case KEY_WHILE:
        token=get_token(&attr);
        return CYKLUS();
    break;
    case KEY_IF:
        token=get_token(&attr);
        return KDYZ();
    break;
    case KEY_READLN:
        token=get_token(&attr);
        if (token==TP_LBRA){
          token=get_token(&attr);
          if (token==TP_IDENT){
            token=get_token(&attr);
            if (token==TP_RBRA){
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        token=get_token(&attr);
        if (token==TP_LBRA){
            token=get_token(&attr);
            if (VYPIS()){
                if (token==TP_RBRA){
                    token=get_token(&attr);
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        token=get_token(&attr);
        return SLOZ();
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){
     if (token == KEY_BEGIN){
        printf("SLOZ\n");
                printf("String je: %s\n",strGetStr(token->stri));

                       printf("\nJe to typ: %i\n",token);

       token=get_token(&attr);;
               printf("String je: %s\n",strGetStr(token->stri));

               printf("\nJe to typ: %i\n",token);

       if (PRVNI()){
            printf("SLOZ2\n");
            if (token== KEY_END){
                token=get_token(&attr);
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (){
    printf("PRVNI0\n");
   // printf("\nJe to typ: %i\n",token);
    if (token==KEY_END){
        printf("PRVNI\n");
        return 1;

    }else {
        if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)
        ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)){
            token=get_token(&attr);
            return POKYN() && DALSI();

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (){
	if (token==KEY_END){

		return 1;
	}else {
		if (token==TP_SEM){
			token=get_token(&attr);
			return POKYN() && PRVNI();
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
	if (token==TP_IDENT) {
		token=get_token(&attr);
		if (token==TP_SGNMNT){
			token=get_token(&attr);
			return VYRAZ();
		}
	}
return 0;
}

/*<GLOBDEK>		->	var id : <TYPE> ; <GLOBDEKDAL>*/
/*<GLOBDEK>		->	eps*/
/*----asi vyreseno---asi pouze na deklaraci globalnich prom.*/
/*----asi vyreseno---prusvih c. 1 pokud bude deklarace lokalnich promennych, pak eps nemuze zacinat na function, ale pouze na begin, vypada to na dalsi 4 pravidla*/
int GLOBDEK (){
	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
        printf("GLOBDEK\n\n");
		return 1;
	}else {
		if ((token==KEY_VAR)){
			token=get_token(&attr);
			if ((token==TP_IDENT)){
				token=get_token(&attr);
				if (token==TP_COL){
					token=get_token(&attr);
					if (TYPE()){
						if (token==TP_SEM){
							token=get_token(&attr);
							return DEKDAL();
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
int GLOBDEKDAL (){
	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==TP_IDENT)){
			token=get_token(&attr);
			if (token==TP_COL){
				token=get_token(&attr);
				if (TYPE()){
					if (token==TP_SEM){
						token=get_token(&attr);
						return DEKDAL();
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
int TYPE (){
	switch(token){
		case KEY_REAL:
			token=get_token(&attr);
			return 1;
		break;
		case KEY_STRING:
			token=get_token(&attr);
			return 1;
		break;
		case KEY_INTEGER:
			token=get_token(&attr);
			return 1;
		break;
		case KEY_BOOLEAN:
			token=get_token(&attr);
			return 1;
		break;
	}
return 0;
}
/*prusvih c.2 co  s termama? bud cast v závorce resit jako vyraz nebo docasne promenne, konzultace Hublik*/
/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
	if (token==TP_IDENT){
			token=get_token(&attr);
			return DVYPIS();
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/
/*mara asi nema nadefinovanou carku, zeptat se*/
int DVYPIS (){
	if (token==TP_RBRA){
		return 1;
	}else {
		if (token==TP_COMMA){
			return VYPIS();
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (){
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==KEY_VAR)){
			token=get_token(&attr);
			if ((token==TP_IDENT)){
				token=get_token(&attr);
				if (token==TP_COL){
					token=get_token(&attr);
					if (TYPE()){
						if (token==TP_SEM){
							token=get_token(&attr);
							return DEKDAL();
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
int DEKDAL (){
	if ( (token==KEY_BEGIN)){
		return 1;
	}else {
		if ((token==TP_IDENT)){
			token=get_token(&attr);
			if (token==TP_COL){
				token=get_token(&attr);
				if (TYPE()){
					if (token==TP_SEM){
						token=get_token(&attr);
						return DEKDAL();
					}
				}

			}
		}
	}
return 0;
}

int VYRAZ(){
return 1;/*simulace eps pravidla pro vyraz, jakmile, hubli, zacnes pravidlo rozvijet, zmen na 0*/
}








