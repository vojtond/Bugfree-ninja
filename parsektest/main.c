/*!!prosim komenty bez diakritiky, blbne kodovani*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"
FILE *soubor;
  SToken *token;

int main()
{

    token=malloc(sizeof(SToken));
    token->stri=malloc(sizeof(string));
    token->type=-1;


  /*  while (token->type != 3)
    {
        if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }

        get_token(soubor,token);
        printf("\nJe to typ: %i\n",token->type);
        printf("Charnum je: %f\n",token->charnum);
        printf("String je: %s\n",strGetStr(token->stri));
        printf("**************************************\n");
        strFree(token->stri);
        //printf("String je: %s\n",token->stri);
    }

    fclose(soubor);*/
    soubor = fopen("text.txt", "r");
    if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvoøit øetìzec\n");
        }
          if (TYPE())
    printf ("%i",START());
    free(token);
    fclose(soubor);

    return 4;
}
int START (){
    get_token(soubor,token);
    if (1/*(token->type == KEY_BEGIN) || (token->type ==KEY_VAR ) || (token->type == KEY_FUNCTION)*/) {
      if ((GLOBDEK()) && (FUNC()) && (SLOZ())) {
            get_token(soubor,token);
            if (token->type==TP_DOT){
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (){

   if ((1/*token->type == KEY_BEGIN*/)){

        return 1;

   }else {
   if (1/*(token->type==KEY_FUNCTION)*/){
       get_token(soubor,token);
       if (token->type==TP_IDENT){
            get_token(soubor,token);
            if (token->type==TP_LBRA){
                get_token(soubor,token);
                if (ARG()) {
                    if (token->type==TP_RBRA){
                        get_token(soubor,token);
                        if (token->type==TP_COL){
                            get_token(soubor,token);

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
    if (token->type==ST_SEM){
        get_token(soubor,token);
        if ((DEK())&& (SLOZ())) {
            if (token->type==ST_SEM){
                get_token(soubor,token);
                return FUNC();
            }
        }
    }else{
        if (1/*token->type==KEY_FORWARD*/){
            get_token(soubor,token);
            if (token->type==ST_SEM){
                get_token(soubor,token);
                return FUNC();
            }
        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (){
    if (token->type==TP_RBRA){
        return 1;
    }else{
        if (token->type==TP_IDENT){
            get_token(soubor,token);
            if (token->type==TP_COL){
                get_token(soubor,token);
                return TYPE () && ARGDAL();
            }
        }
    }
    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (){
     if (token->type==TP_RBRA){
        return 1;
    }else{
        if (token->type==ST_SEM){
            get_token(soubor,token);
            if (token-> type==TP_IDENT){
                get_token(soubor,token);
                if (token->type==TP_COL){
                    get_token(soubor,token);
                    return TYPE() && ARGDAL();
                }
            }
        }
    }
    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (){
    if (1/*token->type==KEY_WHILE*/){
        get_token(soubor,token);
        if(VYRAZ()){
            if (1/*token->type==KEY_DO*/)
                get_token(soubor,token);
                return SLOZ();
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){
    if (1/*token->type==KEY_IF*/){
        get_token(soubor,token);
        if(VYRAZ()){
            if (1/*token->type==KEY_THEN*/){
                get_token(soubor,token);
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
    if (1/*(token->type==TP_IDENT)||(token->type==KEY_WHILE)|| (token->type==KEY_IF)||(token->type==ST_SEM)
    ||(token->type==KEY_READLN)||(token->type==KEY_WRITE)||(token->type==KEY_BEGIN)||(token->type==KEY_END)*/){

       return 1;
    }else {
        if (1/*token->type==KEY_ELSE*/){
            get_token(soubor,token);
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
  switch (token->type ){
    case TP_IDENT:
        get_token(soubor,token);
        return PRIKAZ();
    break;
    case 1/*KEY_WHILE*/:
        get_token(soubor,token);
        return CYKLUS();
    break;
    case 2/*KEY_IF*/:
        get_token(soubor,token);
        return KDYZ();
    break;
    case 3/*KEY_READLN*/:
        get_token(soubor,token);
        if (token->type==TP_LBRA){
          get_token(soubor,token);
          if (token->type==TP_IDENT){
            get_token(soubor,token);
            if (token->type==TP_RBRA){
                return 1;
            }
          }
        }
    break;
    case 4/*KEY_WRITE*/:
        get_token(soubor,token);
        if (token->type==TP_LBRA){
            get_token(soubor,token);
            if (VYPIS()){
                if (token->type==TP_RBRA){
                    get_token(soubor,token);
                    return 1;
                }
            }
        }
    break;
    case 5/*KEY_BEGIN*/:
        get_token(soubor,token);
        return SLOZ();
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){
     if (1/*token->type == KEY_BEGIN*/){
       get_token(soubor,token);
       if (PRVNI()){
            if (1/*token->type== KEY_END*/){
                get_token(soubor,token);
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (){
    if (1/*token-> type==KEY_END*/){

        return 1;

    }else {
        if (1/*(token->type==TP_IDENT)||(token->type==KEY_WHILE)|| (token->type==KEY_IF)
        ||(token->type==KEY_READLN)||(token->type==KEY_WRITE)||token->type==KEY_BEGIN)*/){
            get_token(soubor,token);
            return POKYN() && DALSI();

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (){
	if (1/*token->type==KEY_END*/){

		return 1;
	}else {
		if (token->type==TP_SEM){
			get_token(soubor,token);
			return POKYN() && PRVNI();
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
	if (token->type==TP_IDENT) {
		get_token(soubor,token);
		if (token->type==TP_SGNMNT){
			get_token(soubor,token);
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
	if (1/*(token->type==KEY_FUNCTION)|| (token->type==KEY_BEGIN)*/){
		return 1;
	}else {
		if (1/*(token->type==KEY_VAR)*/){
			get_token(soubor,token);
			if ((token->type==TP_IDENT)){
				get_token(soubor,token);
				if (token->type==TP_COL){
					get_token(soubor,token);
					if (TYPE()){
						if (token->type==TP_SEM){
							get_token(soubor,token);
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
	if (1/*(token->type==KEY_FUNCTION)|| (token->type==KEY_BEGIN)*/){
		return 1;
	}else {
		if ((token->type==TP_IDENT)){
			get_token(soubor,token);
			if (token->type==TP_COL){
				get_token(soubor,token);
				if (TYPE()){
					if (token->type==TP_SEM){
						get_token(soubor,token);
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
	switch(token->type){
		case 1/*KEY_REAL*/:
			get_token(soubor,token);
			return 1;
		break;
		case 2 /*KEY_STRING*/:
			get_token(soubor,token);
			return 1;
		break;
		case 3/*KEY_INTEGER*/:
			get_token(soubor,token);
			return 1;
		break;
		case 4/*KEY_BOOLEAN*/:
			get_token(soubor,token);
			return 1;
		break;
	}
return 0;
}
/*prusvih c.2 co  s termama? bud cast v závorce resit jako vyraz nebo docasne promenne, konzultace Hublik*/
/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
	if (token->type==TP_IDENT){
			get_token(soubor,token);
			return DVYPIS();
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/
/*mara asi nema nadefinovanou carku, zeptat se*/
int DVYPIS (){
	if (token->type==TP_RBRA){
		return 1;
	}else {
		if (1/*token->type==TP_*/){
			return VYPIS();
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (){
	if (1/* (token->type==KEY_BEGIN)*/){
		return 1;
	}else {
		if (1/*(token->type==KEY_VAR)*/){
			get_token(soubor,token);
			if ((token->type==TP_IDENT)){
				get_token(soubor,token);
				if (token->type==TP_COL){
					get_token(soubor,token);
					if (TYPE()){
						if (token->type==TP_SEM){
							get_token(soubor,token);
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
	if (1/* (token->type==KEY_BEGIN)*/){
		return 1;
	}else {
		if ((token->type==TP_IDENT)){
			get_token(soubor,token);
			if (token->type==TP_COL){
				get_token(soubor,token);
				if (TYPE()){
					if (token->type==TP_SEM){
						get_token(soubor,token);
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









