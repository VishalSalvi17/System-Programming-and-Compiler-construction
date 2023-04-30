/*
EXPERIMENT 4b

Name: Vishal Salvi
UID: 2019230069
Roll No. 52
Batch: C

*/

#include<stdio.h>
#include<stdlib.h>
# include <string.h>
#include <ctype.h>

int state = 0;
int start = 0;
char c;
FILE *fp;
char lexeme[100];
int count=0;
int lexeme_count = 0;
int table_counter = 0;
int token_count = 0;
int indexT;

struct TOKEN
{
    int id;
    char lexeme[100];
    char tokenName[100];
    struct TOKEN* next;

};

struct TOKEN * table[100];

struct TOKEN* createToken(int ID, char lex[100], char tName[100])
{
    struct TOKEN* newToken = (struct TOKEN*)malloc(sizeof(struct TOKEN));
    newToken->id = ID;
    strcpy(newToken->lexeme,lex);
    strcpy(newToken->tokenName,tName);
    return newToken;
}

int searchToken(char lexeme[100])
{
    for(int i=0; i<table_counter; i++)
    {
        if(strcmp(table[i]->lexeme,lexeme)==0)
        {
            return i;
        }
    }
    return -1;
}

int fail()
{
    switch (start)
    {
        case 0:
            start = 30;
            break;
        case 30:
            start = 12;
            break;
        case 12:
            start = 22;
            break;
        case 22:
            start = 25;
            break;
        case 25:
            start = 28;
            break;
        case 28:
            start = 29;
            break;

        default:
            break;
    }
    return start;
}

void retract()
{
    strcpy(lexeme,"");
    count = 0;
    start = 0;
    state = 0;
}

void getRelop()
{
    while (1)
    {
        switch (state)
        {
            case 0:
                if(c ==  '<')
                {
                    state = 1;
                    lexeme[count++] = c;
                }
                else if(c == '=')
                {
                    state =5;
                    lexeme[count++] = c;
                }
                else if (c == '>')
                {
                    state = 6;
                    lexeme[count++] = c;
                }
                else
                {
                    state = fail();
                    return;
                }
                break;

            case 1:
                c = (char)fgetc(fp);
                if(c == '=')
                {
                    state = 2;
                    lexeme[count++] = c;
                }

                else if(c == '>')
                {
                    state = 3;
                    lexeme[count++] = c;
                }

                else
                {
                    state = 4;
                    lexeme[count++] = c;
                }

                break;

            case 2:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;

            case 3:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;

            case 4:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                }
                retract();
                return;
                break;

            case 5:
                c = (char)fgetc(fp);
                if(c == '=')
                {
                    state = 63;
                    lexeme[count++] = c;
                }
                else
                {
                    lexeme[count++] = '\0';
                    indexT = searchToken(lexeme);
                    if(indexT == -1)
                    {
                        struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                        table[table_counter++] = newToken;
                        printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                    }
                    else
                    {
                        printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                    }
                    c =(char)fgetc(fp);
                    retract();
                    return;
                    break;
                }
            case 63:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "opeartor");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "operator", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;

            case 6:
                c = (char)fgetc(fp);
                if (c == '=')
                {
                    state = 7;
                    lexeme[count++] = c;
                }
                else
                {
                    state = 8;
                    lexeme[count++] = c;
                }
                break;

            case 7:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;

            case 8:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "RELOP");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "RELOP", indexT);
                }
                retract();
                return;
                break;

            default:
                break;
        }
    }

}

void getUnsignedNumber()
{
    while(1)
    {
        switch (state)
        {
            case 12:
                if (isdigit(c))
                {
                    state = 13;
                    lexeme[count++] = c;
                }
                else
                {
                    state = fail();
                    return;
                }
                break;

            case 13:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 13;
                    lexeme[count++] = c;
                }
                else if(c == '.')
                {
                    state = 14;
                    lexeme[count++] = c;
                }
                else if(c == 'E')
                {
                    state =16;
                    lexeme[count++] = c;
                }
                else state = 20;
                break;

            case 14:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 15;
                    lexeme[count++] = c;
                }

                break;

            case 15:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 15;
                    lexeme[count++] = c;
                }
                else if(c == 'E')
                {
                    state = 16;
                    lexeme[count++] = c;
                }
                else state = 21;
                break;

            case 16:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 18;
                    lexeme[count++] = c;
                }
                else if(c == '+' || c =='-')
                {
                    state = 17;
                    lexeme[count++] = c;
                }

                break;

            case 17:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 18;
                    lexeme[count++] = c;
                }
                break;

            case 18:
                c = (char)fgetc(fp);
                if (isdigit(c))
                {
                    state = 18;
                    lexeme[count++] = c;
                }
                else state = 19;
                break;

            case 19:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "number");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "number", indexT);
                }
                retract();
                return;
                break;

            case 20:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "number");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "number", indexT);
                }
                retract();
                return;
                break;

            case 21:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "number");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "number", indexT);
                }
                retract();
                return;
                break;

            default:
                break;
        }
    }
}

int isDelimiter(char a)
{
    if(a == ';'|| a==','|| a=='(' || a==')' || a== '{' || a=='}' || a=='[' || a==']' || a=='.' || a==' ' || a=='\t' || a=='\n')
    {
        return 1;
    }
    else return 0;
}

void getDelimiter()
{
    while(1)
    {
        switch (state)
        {
            case 22:
                if(isDelimiter(c))
                {
                    state = 24;
                    lexeme[count++] = c;
                }
                else
                {
                    state = fail();
                    return;
                }
                break;

            case 24:
                lexeme[count++] = '\0';
                retract();
                c = (char)fgetc(fp);
                return;
                break;

            default:
                break;
        }
    }
}

void getStrings()
{
    while (1)
    {
        switch(state)
        {
            case 25:
                if (c == '\"')
                {
                    state = 26;
                    lexeme[count++] = c;
                }
                else
                {
                    state = fail();
                    return;
                }
                break;
            case 26:
                c = (char)fgetc(fp);
                if(c == '\"')
                {
                    state = 27;
                    lexeme[count++] = c;
                }
                else
                {
                    state = 26;
                    lexeme[count++] = c;
                }
                break;

            case 27:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "string");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "string", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;

            default:
                break;

        }
    }

}

int isOperator(char a)
{
    if(a=='+' || a=='-' || a=='*' || a=='/' || a=='%' || a=='&' || a=='=' || a=='|') return 1;
    else return 0;
}

void getOperator()
{




    while (1)
    {
        switch (state)
        {
            case 28:
                if(isOperator(c))
                {
                    lexeme[count++] = c;
                    state = 29;
                }
                else state = fail();
                break;

            case 29:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "opeartor");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "operator", indexT);
                }
                c =(char)fgetc(fp);
                retract();
                return;
                break;


            default:
                break;
        }
    }




}

void getKeyword()
{
    while (1)
    {
        switch (state)
        {
            case 30:
                if(c == 'i')
                {
                    lexeme[count++] = c;
                    state = 31;
                }
                else if(c == 'w')
                {
                    lexeme[count++] = c;
                    state = 35;
                }
                else if(c == 'f')
                {
                    lexeme[count++] = c;
                    state = 40;
                }
                else if(c == 'c')
                {
                    lexeme[count++] = c;
                    state = 43;
                }
                else if(c == 'b')
                {
                    lexeme[count++] = c;
                    state = 51;
                }
                else if(c == 'r')
                {
                    lexeme[count++] = c;
                    state = 56;
                }
                else state = 9;
                break;




            case 31:
                c = (char)fgetc(fp);
                if(c == 'f')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else if(c == 'n')
                {
                    lexeme[count++] = c;
                    state = 33;
                }
                else state = 9;
                break;

            case 32:
                c = (char)fgetc(fp);
                if(isalpha(c)) state = 9;
                else if(isdigit(c)) state = 62;
                else
                {
                    lexeme[count++] = '\0';
                    indexT = searchToken(lexeme);
                    if(indexT == -1)
                    {
                        struct TOKEN *newToken = createToken(token_count++,lexeme, "keyword");
                        table[table_counter++] = newToken;
                        printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                    }
                    else
                    {
                        printf("\n%d. < %s, %d>\n", lexeme_count++, "keyword", indexT);
                    }
                    retract();
                    return;
                }
                break;

            case 33:
                c = (char)fgetc(fp);
                if(c == 't')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;




            case 35:
                c = (char)fgetc(fp);
                if(c == 'h')
                {
                    lexeme[count++] = c;
                    state = 36;
                }
                else state=9;
                break;

            case 36:
                c = (char)fgetc(fp);
                if(c == 'i')
                {
                    lexeme[count++] = c;
                    state = 37;
                }
                else state=9;
                break;


            case 37:
                c = (char)fgetc(fp);
                if(c == 'l')
                {
                    lexeme[count++] = c;
                    state = 38;
                }
                else state=9;
                break;

            case 38:
                c = (char)fgetc(fp);
                if(c == 'e')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;



            case 40:
                c = (char)fgetc(fp);
                if(c == 'o')
                {
                    lexeme[count++] = c;
                    state = 41;
                }
                else state=9;
                break;

            case 41:
                c = (char)fgetc(fp);
                if(c == 'r')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;

            case 43:


                c = (char)fgetc(fp);
                if(c == 'o')
                {
                    lexeme[count++] = c;
                    state = 44;
                }
                else state=9;
                break;

            case 44:
                c = (char)fgetc(fp);
                if(c == 'n')
                {
                    lexeme[count++] = c;
                    state = 45;
                }
                else state=9;
                break;

            case 45:
                c = (char)fgetc(fp);
                if(c == 't')
                {
                    lexeme[count++] = c;
                    state = 46;
                }
                else state=9;
                break;

            case 46:
                c = (char)fgetc(fp);
                if(c == 'i')
                {
                    lexeme[count++] = c;
                    state = 47;
                }
                else state=9;
                break;

            case 47:
                c = (char)fgetc(fp);
                if(c == 'n')
                {
                    lexeme[count++] = c;
                    state = 48;
                }
                else state=9;
                break;

            case 48:
                c = (char)fgetc(fp);
                if(c == 'u')
                {
                    lexeme[count++] = c;
                    state = 49;
                }
                else state=9;
                break;

            case 49:
                c = (char)fgetc(fp);
                if(c == 'e')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;

            case 51:
                c = (char)fgetc(fp);
                if(c == 'r')
                {
                    lexeme[count++] = c;
                    state = 52;
                }
                else state=9;
                break;

            case 52:
                c = (char)fgetc(fp);
                if(c == 'e')
                {
                    lexeme[count++] = c;
                    state = 53;
                }
                else state=9;
                break;

            case 53:
                c = (char)fgetc(fp);
                if(c == 'a')
                {
                    lexeme[count++] = c;
                    state = 54;
                }
                else state=9;
                break;

            case 54:
                c = (char)fgetc(fp);
                if(c == 'k')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;

            case 56:
                c = (char)fgetc(fp);
                if(c == 'e')
                {
                    lexeme[count++] = c;
                    state = 57;
                }
                else state=9;
                break;

            case 57:
                c = (char)fgetc(fp);
                if(c == 't')
                {
                    lexeme[count++] = c;
                    state = 58;
                }
                else state=9;
                break;

            case 58:
                c = (char)fgetc(fp);
                if(c == 'u')
                {
                    lexeme[count++] = c;
                    state = 59;
                }
                else state=9;
                break;

            case 59:
                c = (char)fgetc(fp);
                if(c == 'r')
                {
                    lexeme[count++] = c;
                    state = 60;
                }
                else state=9;
                break;

            case 60:
                c = (char)fgetc(fp);
                if(c == 'n')
                {
                    lexeme[count++] = c;
                    state = 32;
                }
                else state=9;
                break;

            case 62:
                state=10;
                lexeme[count++] = c;
                break;

            case 9:
                if(isalpha(c))
                {
                    state =10;
                    lexeme[count++] = c;
                }
                else
                {
                    state = fail();
                    return;
                }
                break;

            case 10:
                c = (char)fgetc(fp);
                if(isalpha(c))
                {
                    state=10;
                    lexeme[count++] = c;
                }
                else if(isdigit(c))
                {
                    state = 10;
                    lexeme[count++] = c;
                }



                else state = 11;
                break;

            case 11:
                lexeme[count++] = '\0';
                indexT = searchToken(lexeme);
                if(indexT == -1)
                {
                    struct TOKEN *newToken = createToken(token_count++,lexeme, "identifier");
                    table[table_counter++] = newToken;
                    printf("\n%d. < %s, %d>\n", lexeme_count++, newToken->tokenName, newToken->id);
                }
                else
                {
                    printf("\n%d. < %s, %d>\n", lexeme_count++, "identifier", indexT);
                }
                retract();
                return;
                break;
            default:
                break;
        }
    }
}

int main()
{
    fp = fopen("palind.c", "r");
    c = (char)fgetc(fp);
    while( c != EOF)
    {
        switch (start)
        {
            case 0:
                getRelop();
                break;

            case 30:
                getKeyword();
                break;

            case 12:
                getUnsignedNumber();
                break;

            case 22:
                getDelimiter();
                break;

            case 25:
                getStrings();
                break;

            case 28:
                getOperator();
                break;

            case 29:
                c = (char)fgetc(fp);
                retract();
                break;

            default:
                break;

        }

    }

    printf("\n\nSymbol Table\n");
    printf("\n\nId\t\tToken Type\t\tLexeme\n");
    for(int i=0; i<table_counter; i++)
    {
        printf("\n%d\t\t%s\t\t%s\n", table[i]->id, table[i]->tokenName, table[i]->lexeme);
    }

}
