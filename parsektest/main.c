/*!!prosim komenty bez diakritiky, blbne kodovani*/
/*!!neprelozitelne, pracuje se natom*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
string attr;
FILE *soubor;
  int token;
  double hodnota;
  int error;
void gtoken(){
    if ((strInit(&attr))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }
      token=get_token(soubor,&hodnota,&attr,&error);
        printf("\nJe to typ: %i\n",token);
     printf("String je: %s\n",strGetStr(&attr));
      strFree(&attr);
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
    gtoken();
    if ((token == KEY_BEGIN) || (token ==KEY_VAR ) || (token == KEY_FUNCTION)) {
      if ((GLOBDEK()) && (FUNC()) && (SLOZ())) {
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
int FUNC (){

   if ((token == KEY_BEGIN)){
        return 1;

   }else {
   if ((token==KEY_FUNCTION)){
       gtoken();
       if (token==TP_IDENT){
            gtoken();
            if (token==TP_LBRA){
                gtoken();
                if (ARG()) {
                    if (token==TP_RBRA){
                        gtoken();
                        if (token==TP_COL){
                            gtoken();

                                    return TYPE() && FORWAR();
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
int FORWAR (){
    printf("forward\n");
    if (token==TP_SEM){
        printf("forward\n");
        gtoken();
        if ((DEK())&& (SLOZ())) {
            if (token==TP_SEM){
                gtoken();
                return FUNC();
            }
        }
    }else{
        if (token==KEY_FORWARD){
            gtoken();
            if (token==TP_SEM){
                gtoken();
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
            gtoken();
            if (token==TP_COL){
                gtoken();
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
            gtoken();
            if (token==TP_IDENT){
                gtoken();
                if (token==TP_COL){
                    gtoken();
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
        gtoken();
        if(VYRAZ()){
            if (token==KEY_DO)
                gtoken();
                return SLOZ();
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){
    printf("if\n");
    if (token==52/*KEY_IF*/){
        printf("if\n");
        gtoken();
        if(VYRAZ()){
            if (token==KEY_THEN){
                gtoken();
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
            gtoken();
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
printf("\nkeif\n");
  switch (token ){
    case TP_IDENT:
        gtoken();
        return PRIKAZ();
    break;
    case KEY_WHILE:
        gtoken();
        return CYKLUS();
    break;
    case KEY_IF:
        printf("\nkeif\n");
        return KDYZ();
    break;
    case KEY_READLN:
        gtoken();
        if (token==TP_LBRA){
          gtoken();
          if (token==TP_IDENT){
            gtoken();
            if (token==TP_RBRA){
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        gtoken();
        if (token==TP_LBRA){
            gtoken();
            if (VYPIS()){
                if (token==TP_RBRA){
                    gtoken();
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        gtoken();
        return SLOZ();
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){
     if (token == KEY_BEGIN){
       gtoken();;
       if (PRVNI()){
            printf("SLOZ2\n");
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
int PRVNI (){
    printf("PRVNI0\n");
   // printf("\nJe to typ: %i\n",token);
    if (token==KEY_END){
        printf("PRVNI\n");
        return 1;

    }else {
        if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)
        ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)){
            gtoken();
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
			gtoken();
			return POKYN() && PRVNI();
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
	if (token==TP_IDENT) {
		gtoken();
		if (token==TP_SGNMNT){
			gtoken();
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
			gtoken();
			if ((token==TP_IDENT)){
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE()){
						if (token==TP_SEM){
							gtoken();
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
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE()){
					if (token==TP_SEM){
						gtoken();
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
			gtoken();
			return 1;
		break;
		case KEY_STRING:
			gtoken();
			return 1;
		break;
		case KEY_INTEGER:
			gtoken();
			return 1;
		break;
		case KEY_BOOLEAN:
			gtoken();
			return 1;
		break;
	}
return 0;
}
/*prusvih c.2 co  s termama? bud cast v závorce resit jako vyraz nebo docasne promenne, konzultace Hublik*/
/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
	if (token==TP_IDENT){
			gtoken();
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
			gtoken();
			if ((token==TP_IDENT)){
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE()){
						if (token==TP_SEM){
							gtoken();
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
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE()){
					if (token==TP_SEM){
						gtoken();
						return DEKDAL();
					}
				}

			}
		}
	}
return 0;
}

int VYRAZ(){
 if (token==TP_IDENT){
    gtoken();
    return 1;

 }
 return 0;
}








