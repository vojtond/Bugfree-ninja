#include <stdio.h>
#include <stdlib.h>


#include "scanner.h"



#define TEXT "text.txt"
int line=1;

char *KeyWord[20]={"do","if","end","var","else","find","real","sort","then","true","begin","false","while","write","readln","string","boolean","forward","integer","function"};

int get_token(FILE *F, double *num, string *stri)       //F je ukazatel na soubor. num je ukazatel na hodnotu real a int. stri je ukazatel na řetězec
{
    int pom;                                            //Pomocná proměnná pro průchod polem KeyWord.
    int konec = 0;                                      //Řídící proměnná while cyklu.
    int realac = 0;                                     //Proměnná, která nám u reálného čísla hlídá neprázdnost části za desetinou tečkou
    int cha=0;                                          //Je proměnná, do které načítáme hodnotu za znakem #.
    int err_char=0;                                     //Proměnná, pomocí které kontrolujeme, jestli jsme dodrželi interval <0;255>
    int next_state=ST_START;                            //Následující stav automatu.
    char c;                                             //Pomocí této proměnné, načítáme znak ze souboru.
    char *chyba;                                        //Indikuje chybu v převodu z řetězce na číslo.
    char min;                                           //U reálného čísla si do něj ukládáme znak -, podle toho jestli jsme ho načetli nebo ne.

    *num=0;                                             //Nulování hodnoty
    c=fgetc(F);                                         //Načtení znaku ze souboru.

    while (konec == 0)                                  //Opakujeme, dokud je konec == 0.
    {

        switch(next_state)                              //Swichem modelujeme automat.
        {
            case ST_START:                                              //Pokud jsme v prvním stavu automatu...
                            if (c == '\n')                              //Když načteme znak odřádkování..
                            {
                                line++;                                 //Inkrementujeme počítadlo řádku.
                                next_state=ST_START;                    //Jako další stav je start.
                            }
                            else if (c == EOF)                          //Pokud načteme eof...
                            {
                                konec = 1;                              //ukončíme cyklus.
                                break;                                  //Ukončíme case a zrychlíme další průběh.
                            }
                            else if (isspace(c))
                            {
                                break;                                  //Při mezeře ukončíme case a jdeme na začátek.
                            }
                            else if (c == ';')                          //Při jedtotlivých znacich vracíme typ tokenu.
                            {
                                return TP_SEM;
                            }
                            else if (c == '/')
                            {
                                return TP_MOD;
                            }
                            else if (c == '.')
                            {
                                return TP_DOT;
                            }
                            else if (c == '(')
                            {
                                return TP_LBRA;
                            }
                            else if (c == '+')
                            {
                                return TP_PLUS;
                            }
                            else if (c == '-')
                            {
                                return TP_MINUS;
                            }
                            else if (c == ')')
                            {
                                return TP_RBRA;
                            }
                            else if (c == '*')
                            {
                                return TP_MUL;
                            }
                            else if (c == ',')
                            {
                                return TP_COMMA;
                            }
                            else if (c == '=')
                            {
                                return TP_EQU;
                            }
                            else if (c == '<')
                            {
                                next_state=ST_LESS;                 //Zde jdeme do následujícího stavu, kde vyhodnocujeme, jestli jsme dostali < nebo <=.
                            }
                            else if (c == '>')
                            {
                                next_state=ST_MORE;                 //Zde jdeme do následujícího stavu, kde vyhodnocujeme, jestli jsme dostali > nebo >=.
                            }
                            else if (c == '{')
                            {
                                next_state=ST_KOMENT;               //Zde jdeme do stavu, kdy vyhodnocujeme komentář.
                            }
                            else if (c == 39)
                            {
                                next_state=ST_STRING;               //Zde jdeme do stavu, kdy vyhodnocujeme string.
                            }
                            else if (isdigit(c))                    //Pokud načteme číslo, musíme vyhodnotit, jestli je real nebo int a jestli je validní.
                            {
                                next_state=ST_NUMBER;
                                strAddChar(stri,c);                 //Přidáme znak do stringu.
                            }
                            else if (isalpha(c) || (c == '_'))                    //Pokud je znak písmeno, musíme vyhodnotit, jestli se jedná o identifikátor nebo klíčové slovo.
                            {
                                pom=0;                              //Pomocnou pro průchod polem nastavíme do 0;
                                next_state=ST_IDENT_KEY;
                                strAddChar(stri,c);                 //Přidáme znak do stringu.
                            }
                            else if (c == ':')
                            {
                                next_state=ST_COLONS;               //Pokud je znak :, musíme rozlišit, jestli bude token : nebo :=.
                                strAddChar(stri,c);
                            }

                            else
                            {
                                error(NULL,LEX_ERR,NULL);                          //Který koliv jiný znak je lexikální chyba.
                            }
            break;

            case ST_KOMENT:                                         //Stav kde kontrolujeme komentář.
                            if (c == '}')                           //Čekáme na ukončení komentáře.
                            {
                                next_state=ST_START;                //Pokud je ukončen, jdeme na začátek.
                            }
                            else if (c == EOF)                      //Pokud je komentář neukončen, jedná se o lexikální chybu.
                            {
                                error(NULL,LEX_ERR,NULL);
                            }
            break;

            case ST_IDENT_KEY:                                                              //Stav, kde rozlišujeme, zda se jedná o identifikátor nebo klíčové slovo.

                            if  ((!(isdigit(c))) && (!(isalpha(c)) && (c != '_')))          //Pokud načteme něco jiného než číslo písmeno nebo _, je identifikátor ukončen a vracíme typ tokenu a identifikátor je zapsán ve stringu stri.
                            {
                                ungetc(c,F);                                                //Vracíme znak do souboru, aby jsme mohli rozlišit token.
                                return TP_IDENT;                                            //Vracíme typ tokenu.
                            }
                            else
                            {
                                strAddChar(stri,c);                                         //Pokud načteme číslo písmeno nebo _, uložíme ho do stringu.
                            }


                            for (pom=0;pom<20;pom++)                                        //Projíždíme pole klíčových slov.
                            {
                                if ((strCmpConstStr(stri,KeyWord[pom]))==0)                 //Porovnáváme jednotlivý prvky
                                {

                                    c=fgetc(F);                                             //Načteme další znak.
                                    if ((!(isdigit(c))) && (!(isalpha(c)) && (c != '_')))   //Pokud neni další znak číslo písmeno nebo podtržítko, máme klíčové slovo.
                                    {
                                        ungetc(c,F);                                        //Vracíme znak do souboru, pro další vyhodnocení tokenu.
                                        return pom+51;                                      //Vracíme definovanou hodnotu klíčového slova.
                                    }
                                    else
                                    {
                                        ungetc(c,F);                                        //Pokud následuje nějaký znak, vrátíme ho do souboru a načteme ho v dalším opakování stavu automatu.
                                    }

                                }

                            }



            break;

            case ST_NUMBER:                                                             //Stav pro vyhodnocování čísla.

                            if(!(isdigit(c)))                                           //Pokud načtený znak neni číslo...
                            {
                                if(c == '.')                                            //ale je desetinná tečka.
                                {
                                    next_state=ST_REAL;                                 //Jako další stav nastavíme REAL.
                                    strAddChar(stri,c);                                 //Uložíme ji do stringu.
                                }
                                else if ((c == 'E') || (c == 'e'))                      //Pokud je znak E nebo e...
                                {
                                    next_state=ST_REAL_EXP;                             //Jako další stav nastavíme REAL_EXP
                                    strAddChar(stri,c);                                 //Uložíme znak do stringu.
                                }
                                else if ((c == '+') || (c == '-'))                      //Pokud je znak + nebo -.
                                {
                                    if (c == '-')                                       //Pokud je -..
                                    {
                                        min='-';                                        //uložíme si jej.
                                    }
                                    else
                                    {
                                        min='+';                                        //uložíme si jej.
                                    }
                                    c=fgetc(F);                                         //Načteme další znak.
                                    if ((c == 'E') || (c == 'e'))                       //Pokud je znak E nebo e, jedná se zatím o validní číslo.
                                    {
                                        next_state=ST_REAL_EXP;                         //Jako další stav nastavíme REAL_EXP.
                                        strAddChar(stri,c);                             //Přidáme znak do stringu.
                                        if (min == '-')                                 //Pokud jsme načetli mínus, uložíme jej do stringu. Tímhle převedeme pascalovské číslo s exponentem na céčkovské, pro další práci,
                                        {
                                            strAddChar(stri,'-');
                                        }
                                    }
                                    else
                                    {
                                        ungetc(c,F);                                    //Vracíme znak do souboru.
                                        ungetc(min,F);                                  //Vracíme znak + nebo - do souboru.
                                        *num = strtod(strGetStr(stri),&chyba);          //Převedeme řetězec na číslo
                                        if ((strGetStr(stri) == chyba) || ((int)*num > INT_MAX))   //Pokud se převod nepovede nebo jsme překročili rozsah, končíme program s chybou.
                                        {
                                            error(NULL,LEX_ERR,NULL);
                                        }
                                        return TP_INT;                                  //Pokud se převod povedl, vrátíme typ tokenu pro číslo.
                                    }
                                }
                                else if (!(isdigit(c)))                                 //Pokud znak neni číslo..
                                {
                                    ungetc(c,F);                                        //Vrátíme znak do souboru,
                                    *num = strtod(strGetStr(stri),&chyba);              //Převedeme řetězec na číslo.
                                    if ((strGetStr(stri) == chyba) || (*num > INT_MAX)) //Pokud se převod nepovede nebo jsme překročili rozsah, končíme program s chybou.
                                        {
                                            error(NULL,LEX_ERR,NULL);
                                        }
                                    return TP_INT;                                      //Pokud se převod povedl, vrátíme typ tokenu pro číslo.
                                }
                            }
                            else
                            {
                                strAddChar(stri,c);                                     //Pokud mám ečíslo, zapíšeme ho do stringu.
                            }
            break;

            case ST_LESS:                                                               //Stav který rozlišuje < nebo <= <>.
                            if (c == '>')                                               //Pokud načteme >, znamená že máme token <> a vracíme jeho definovanou hodnotu
                            {
                                return TP_NEQU;
                            }
                            else if (c == '=')                                          //Pokud načteme =, znamená že máme token <= a vracíme jeho definovanou hodnotu
                            {
                                return TP_LESSQ;
                            }
                            else                                                        //Pokud znak neni ani > ani =, vracíme znak do souboru a vracíme definovanou hodnotu tokenu <
                            {
                                ungetc(c,F);
                                return TP_LESS;
                            }
            break;

            case ST_MORE:                                                               //Stav který rozlišuje > nebo >=.
                            if (c == '=')                                               //Pokud načteme =, znamená že máme token >= a vracíme jeho definovanou hodnotu
                            {
                                return TP_MOREQ;
                            }
                            else                                                         //Pokud znak neni =, vracíme znak do souboru a vracíme definovanou hodnotu tokenu >
                            {
                                ungetc(c,F);
                                return TP_MORE;
                            }
            break;

            case ST_COLONS:                                                             //Stav který rozlišuje : nebo :=.
                            if (c == '=')                                               //Pokud je daný znak =, načetli jsme token := a vracíme jeho definovanou hodnotu.
                            {
                                return TP_SGNMNT;
                            }
                            else
                            {
                                ungetc(c,F);                                            //Pokud znak neni =, máme token :, vracíme znak do souboru a vracíme definovanou hodnotu tokenu :.
                                return TP_COL;
                            }
            break;

            case ST_CHAR:                                                               //Stav, kterým řešíme znak #0..255.
                            if (c == 39)                                                //Pokud dostaneme ' je to náš ukončující znak
                            {
                                if (err_char == 0)                                      //Pokud nedošlo k chybě..
                                {
                                    strAddChar(stri,cha);                               //Uložíme znak do stringu.
                                }
                                err_char=0;                                             //Nastavujeme příznak do původní hodnoty pro další vyhodnocování.
                                next_state=ST_STRING;                                   //Vracíme se do stringu.
                                break;
                            }
                            if ((!(isdigit(c)) && (c != 39)) || (err_char==1))          //Pokud načteme něco jiného než číslo a ' a nebo nastala chyba, končíme program s chybou.
                            {
                                error(NULL,LEX_ERR,NULL);                              //Končíme program s chybou.
                            }
                            else                                                        //Pokud načteme číslo.
                            {
                                cha=cha*10+(c-48);                                      //Převádíme postupně řetězec na číslo.
                                if ((cha <1) || (cha > 255))                            //Pokud jsme mimo rozsah, označíme chybu.
                                {
                                    error(NULL,LEX_ERR,NULL);                          //A ukončíme program s chybou.
                                }
                            }

            break;

            case ST_STRING:                                                             //Stav pro vyhodnoceni řetězce.
                            if (c == 39)                                                //Pokud načteme ' načteme další znak pro vyhodnocení situace.
                            {
                                c=fgetc(F);
                                if (c == '#')                                           //Pokud je znak # přejdeme do stavu pro vyhodnocení znaku.
                                {
                                    next_state=ST_CHAR;
                                    break;
                                }
                                else if (c == 39)                                       //Pokud jsme načetli další '..
                                {
                                    strAddChar(stri,39);                                //Znamená to že v řetězci je ' a uložíme si ho do řetězce.
                                }
                                else
                                {
                                    ungetc(c,F);                                        //Pokud něco jiného, tzn., že jsme načetli jen ', takže ukončíme string a vrátíme znak do souboru.
                                    return TP_STRING;                                   //Vracíme definovanou hodnotu pro string.
                                }

                            }
                            else if (c == EOF)                                          //Pokud načteme eof, jedná se o neukončený řetězec.
                            {
                                error(NULL,LEX_ERR,NULL);                              //Končíme program s chybou.
                            }
                            else
                            {
                                strAddChar(stri,c);                                     //Cokoliv jiného než ', tak zapisujeme do stringu.
                            }

            break;

            case ST_REAL:                                                               //Stav pro vyhodnocení reálného čísla.
                            if(!(isdigit(c)))                                           //Pokud načtený znak neni číslo...
                            {

                                if ((c == 'E') || (c == 'e'))                           //Kontrolujeme, jestli není E nebo e.
                                {
                                    if (!realac)                                        //Pokud je E nebo e a desetinná část je prázdná..
                                    {
                                        error(NULL,LEX_ERR,NULL);                      //Potom ukončíme program s chybou.
                                    }
                                    realac = 0;                                         //realac nastavíme do výchozí hodnoty pro další vyhodnocení čísla.
                                    next_state=ST_REAL_EXP;                             //Další stav je reálné číslo s exponentem.
                                    strAddChar(stri,c);                                 //Přidáme znak do řetězce.
                                    break;
                                }
                                else if ((c == '+') || (c == '-'))                      //Pokud načteme + nebo -, vyhodnocujeme to stejně jako ve stavu NUMBER, s tím že navíc hlídáme neprázdnost desetinné části
                                {
                                    if (!realac)
                                    {
                                        error(NULL,LEX_ERR,NULL);                      //Končíme s chybou.
                                    }
                                    if (c == '-')
                                    {
                                        min='-';
                                    }
                                    c=fgetc(F);
                                    if ((c == 'E') || (c == 'e'))
                                    {
                                        realac=0;
                                        next_state=ST_REAL_EXP;
                                        strAddChar(stri,c);
                                        if (min == '-')
                                        {
                                            strAddChar(stri,'-');
                                        }
                                        break;
                                    }
                                    else                                            //Cokoliv jiného než +-/Ee je chyba.
                                    {
                                        error(NULL,LEX_ERR,NULL);
                                    }
                                }
                                else if(!(isdigit(c)))
                                {
                                    ungetc(c,F);
                                    *num = strtod(strGetStr(stri),&chyba);          //Převedeme řetězec na číslo
                                    if ((strGetStr(stri) == chyba) || (*num > DBL_MAX))   //Pokud se převod nepovede nebo jsme překročili rozsah, končíme program s chybou.
                                    {
                                        error(NULL,LEX_ERR,NULL);
                                    }
                                    return TP_REAL;
                                }
                            }
                            else
                            {
                                    strAddChar(stri,c);                             //Načteme číslo do řetězce.
                            }
                            if (!realac) realac=1;                                  //Uložíme si příznak neprázdné desetinné části.
            break;

            case ST_REAL_EXP:                                                       //Stav který vyhodnocuje čísla s exponentem

                            if(!(isdigit(c)))                                       //Pokud načtený znak neni číslo..
                            {
                                ungetc(c,F);                                        //Vrátíme ho do souboru.
                                if (!realac)                                        //Zjistíme, jestli exponenciální část neni prázdná.
                                {
                                        error(NULL,LEX_ERR,NULL);                //Pokud ano, je to chyba a končíme program s chybou.
                                }
                                *num = strtod(strGetStr(stri),&chyba);          //Převedeme řetězec na číslo
                                if ((strGetStr(stri) == chyba) || (*num > DBL_MAX))          //Pokud se převod nepovede nebo jsme překročili rozsah, končíme program s chybou.
                                {
                                    error(NULL,LEX_ERR,NULL);
                                }
                                return TP_REAL;                                 //Vracíme definovanou hodnotu pro REAL
                            }
                            else                                                //Když načteme číslo, uložíme ho do řetězce.
                            {
                                    strAddChar(stri,c);
                            }
                            if (!realac) realac=1;                              //Ukládáme si příznak neprázdnosti exponenciální části.
            break;
        }


    c=fgetc(F);                                                                 //Na konci cyklu načítáme další znak.
    }

    return TP_EOF;                                                              //Pokud se dostaneme ven z cyklu, museli jsme načíst EOF, vracíme jeho definovanou hodnotu.



}












int mara()

{
    string stri;
    int type;
    double num;
    int error;


    type=-1;
    //*num=0;
    //*line=1;

    FILE *soubor;


    //stri=malloc(sizeof(string));

    printf("*******************\n");




    soubor = fopen(TEXT, "r");

    while (type != 3)
    {
        if ((strInit(&stri))==1)
        {
            printf("nepovedlo se vytvořit řetězec\n");
        }
//int get_token(FILE *F, double *num, int *line, string *stri, int *error )
        type=get_token(soubor,&num,&stri);
        printf("\nJe to typ: %i\n",type);
        printf("Charnum je: %f a radek je:%i\n",num,line);
        printf("String je: %s\n",strGetStr(&stri));
        printf("**************************************\n");
        strFree(&stri);

    }
    fclose(soubor);
    return 0;
}
int get_line(){

return line;
}
