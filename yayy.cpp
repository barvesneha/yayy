ASSIGNMENT 1
file.l
  
%{
%}
letter [A-Za-z]
digit [0-9]
identifier {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?
punctuation [;,."#(){}]
operators [+-=*<>]
keywords if|else|for|int|while|do|void
literal ["].*["]
comment "//".*
headerfile "#".*
multicomment "/*"(.|\n)*"*/"

%%

{headerfile} {printf("\n Headerfile %s is found ",yytext);}
{keywords} {printf("\n Keyword %s is found",yytext);}
{identifier} {printf("\n Identifier %s is found ",yytext);}
{number} {printf("\n  Number %s is found ",yytext);}
{punctuation} {printf("\n Punctuation  %s is found ",yytext);}
{literal} {printf("\n Literal %s is found ",yytext);}
{operators} {printf("\n Operators  %s is found ",yytext);}
{comment} {printf("\n  Single-line Comment %s is found ",yytext);}
{multicomment} {printf("\n Multi-line comment %s is found",yytext);}

%%

int main(void)
{
 yylex();
 return 0;
}

int yywrap()
{
  return 1;
}


input.c
#include<stdio.h>

void main()
{
  int a,b,c;
   a=4;
   b=5;

  c=a+b;  // addition 
  printf("Accept number a");
 /* number is 
accepted */

  getch();
 }


ASSIGNMENT 2
file.l

%{ 
  
    int ccount=0,capcount=0,smalcount=0,lcount=0;
%}

cword [A-Z]+
sword [a-z]+
eol \n
%%

{cword} {capcount++;ccount+=yyleng;}
{sword} {smalcount++;ccount+=yyleng;}
{eol}  {ccount++;lcount++;}
 .  {ccount++;}
%%

int main(void)
{
  yylex();
  printf("\nNumber of characters : %d",ccount);
  printf("\nNumber of Capital Case Words : %d",capcount);
  printf("\nNumber of small Case Words : %d",smalcount);
  printf("\nNumber of Lines : %d",lcount);
  return 0;
}

int yywrap()
{
  return 1;
}

file.txt

sys PROG
op sys
cl TE
br COMP
div B
ES iot
wt

ASSIGNMENT 3
file.l
%{
#include<stdio.h>
#include "y.tab.h"
%}
letter 		[A-Za-z]
digit  		[0-9]
keyword 	int|float|char
identifier 	{letter}({letter}|{digit})*
%%
{keyword} 	return TYPE;
"," 		return COMMA;
";" 		return SC;
{identifier} 	return ID;
"\n" 		return NL;
%%

file.y

%{
#include<stdio.h>
int yylex();
int yyerror();

%}
%token ID TYPE SC NL COMMA
%%
start:TYPE varlist SC NL 	{printf("valid declarative statement");}
;

varlist:varlist COMMA ID
	|ID
;

%%
int yyerror()
{
printf("Invalid declarative statement");
}

int yywrap()
{
return 1;
}

int main()
{
yyparse();
}


ASSIGNMENT 4
file.l

%{
/*
 * We now build a lexical analyzer to be used by a higher-level parser.
 */
#include "y.tab.h"    /* token codes from the parser */
%}
verb 		is|am|are|was|were|be|being|been|do|does|did|will|would|should|can|could|have|has|had|go|play
adverb 		very|simply|gently|calmly|quietly
preposition 	to|from|above|behind|below|between
conjunction 	if|then|and|but|or
adjective 	their|my|your|his|her|its
pronoun 	I|you|he|she|they
noun 		[a-zA-Z]+
%%
[\t ]+  ;
{verb}    	 return VERB;  
{adverb}         return ADVERB;   
{preposition}    return PREPOSITION; 
{conjunction}    return CONJUNCTION;   
{adjective}      return ADJECTIVE;          
{pronoun}        return PRONOUN;
{noun}           return NOUN;  
"\n"		 return NL;  
%%

file.y
  
%{
#include<stdlib.h>
#include<stdio.h>
int yylex();
int yyerror();

%}

%token NOUN PRONOUN VERB ADVERB ADJECTIVE PREPOSITION CONJUNCTION NL

%%

sentence: simple_sentence NL  {printf("Parsed a simple sentence.\n"); exit(0);}
      | compound_sentence NL  {printf("Parsed a compound sentence.\n"); exit(0);}
      ;

simple_sentence: subject verb object
      |     subject verb object prep_phrase
      ;

compound_sentence: simple_sentence CONJUNCTION simple_sentence
      |     compound_sentence CONJUNCTION simple_sentence
      ;

subject:    NOUN
      |     PRONOUN
      |     ADJECTIVE subject
      ;

verb:       VERB
      |     ADVERB VERB
      |     verb VERB
      ;

object:           NOUN
      |     ADJECTIVE object
      ;

prep_phrase:     PREPOSITION NOUN
      ;

%%

int main()
{
yyparse();
}
       
int yyerror()
{
printf("invalid");
}

int yywrap()
{
return 1;
}


ASSIGNMENT 5
rdp.c

    #include <stdio.h>  
    #include <string.h>  
      
    #define SUCCESS 1  
    #define FAILED 0  
      
    int E(), Edash(), T(), Tdash(), F();  
      
    const char *cursor;  
    char string[64];  
      
    int main()  
    {  
        puts("Enter the string");  
        // scanf("%s", string);  
        sscanf("i+(i+i)*i", "%s", string);  
        cursor = string;  
        puts("");  
        puts("Input      Action");  
        puts("--------------------------------");  
      
        if (E() && *cursor == '\0') {  
            puts("--------------------------------");  
            puts("String is successfully parsed");  
            return 0;  
        } else {  
            puts("--------------------------------");  
            puts("Error in parsing String");  
            return 1;  
        }  
    }  
      
    int E()  
    {  
        printf("%-16s E -> T E'\n", cursor);  
        if (T()) {  
            if (Edash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    }  
      
    int Edash()  
    {  
        if (*cursor == '+') {  
            printf("%-16s E' -> + T E'\n", cursor);  
            cursor++;  
            if (T()) {  
                if (Edash())  
                    return SUCCESS;  
                else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else {  
            printf("%-16s E' -> $\n", cursor);  
            return SUCCESS;  
        }  
    }  
      
    int T()  
    {  
        printf("%-16s T -> F T'\n", cursor);  
        if (F()) {  
            if (Tdash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    }  
      
    int Tdash()  
    {  
        if (*cursor == '*') {  
            printf("%-16s T' -> * F T'\n", cursor);  
            cursor++;  
            if (F()) {  
                if (Tdash())  
                    return SUCCESS;  
                else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else {  
            printf("%-16s T' -> $\n", cursor);  
            return SUCCESS;  
        }  
    }  
      
    int F()  
    {  
        if (*cursor == '(') {  
            printf("%-16s F -> ( E )\n", cursor);  
            cursor++;  
            if (E()) {  
                if (*cursor == ')') {  
                    cursor++;  
                    return SUCCESS;  
                } else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else if (*cursor == 'i') {  
            cursor++;  
            printf("%-16s F ->i\n", cursor);  
            return SUCCESS;  
        } else  
            return FAILED;  
    }  


ASSIGNMENT 6
file.y

%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int yylex();
int yyerror();
%}

%union
{
double dval;
}
%token <dval> NUMBER
%token NAME SINE nLOG SQRT
%left '+''-'
%left '*''/'
%left SINE nLOG SQRT
%right '^'
%type <dval> E
%%
S : NAME '=' E
  | E		        {printf("=%g\n",$1);}
  ;

E : E '+' E	{$$=$1+$3;}
  | E '-' E	{$$=$1-$3;}
  | E '*' E	{$$=$1*$3;}
  | E '/' E	{$$=$1/$3;}
  | NUMBER	{$$=$1;}
  ;

E : SINE E  	{$$=sin($2 * 3.14/180);}
  | nLOG E  	{$$=log($2);}
  | E '^' E	{$$=pow($1,$3);}
  | SQRT E      {$$=sqrt($2);}
  ; 
%%
int main()
{
yyparse();
return 0;
}
int yyerror()
{
printf("syntax error");
}

file.l

%{
#include "y.tab.h"
#include<stdio.h>
#include<math.h>
//extern int yylval;
%}
%%
[0-9]+(\.[0-9]*)? 	{yylval.dval=atof(yytext); return NUMBER;}
[ \t]	;
\n	return 0;
.	return yytext[0];
sin	return SINE;
log     return nLOG;
sqrt    return SQRT;
%%
int yywrap()
{
return 1;
}

ASSIGNMENT 7
file.l

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[20];
struct Symbol {
    char name[50];
    int value;
};

struct Symbol symbolTable[100];
int symbolCount = 0;

void addSymbol(char* name, int value) {
    strcpy(symbolTable[symbolCount].name, name);
    symbolTable[symbolCount].value = value;
    symbolCount++;
}

#define ID 1
#define NUM 2
%}

%option noyywrap

%%
[a-zA-Z][a-zA-Z0-9]*    {
                            strcpy(str, yytext);
                            printf("Identifier: %s\n", yytext);
                            return ID;
                        }
[0-9]+                  {
			    addSymbol(str, atoi(yytext));
                            printf("Number: %s\n", yytext);
                            return NUM;
                        }
"="                    {return *yytext;}
[ \t\n]                 ; // Ignore whitespace and newlines
.                       printf("Invalid character: %c\n", *yytext);

%%

int main() {
    int token;
    while ((token = yylex()) != 0) {
        if (token == '=') {
            printf("Assignment operator: %c\n", token);
        }
    }
    
    printf("\nSymbol Table:\n");
    printf("Name\tValue\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%s\t%d\n", symbolTable[i].name, symbolTable[i].value);
    }
    
    return 0;
}


ASSIGNMENT 8
file.l

%{			
#include"y.tab.h"
#include"stdio.h"
#include"string.h"
int lineno=1;
%}

number [0-9]+|([0-9]*\.[0-9]+)	    
identifier [a-zA-Z][a-zA-Z0-9]*
%%

{identifier} {strcpy(yylval.var,yytext);
                return VAR;}

{number} {strcpy(yylval.var,yytext);
          return NUM;}

\n lineno++;

[\t ] ;

. {return yytext[0];}		
%%


file.y

%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int i=0,index1=0,tindex=0;
void addqruple(char op[5],char arg1[10],char arg2[10],char result[10]);
int yylex();
int yyerror();
struct q
{
      char op[5];
      char arg1[10];
      char arg2[10];
      char result[10];
}q[30];

%}

%union
{
  char var[10];
}

%token <var>NUM VAR 
%type <var>EXPR ASSIGNMENT 
%left'-''+'
%left'*''/'
%nonassoc UMINUS
%left '('')'

%%

ASSIGNMENT:VAR'='EXPR {
           	strcpy(q[index1].op,"=");
           	strcpy(q[index1].arg1,$3);
           	strcpy(q[index1].arg2,"");
           	strcpy(q[index1].result,$1);
           	strcpy($$,q[index1++].result);
            	}
            ;
EXPR:EXPR'+'EXPR {addqruple("+",$1,$3,$$);}
    |EXPR'-'EXPR {addqruple("-",$1,$3,$$);}
    |EXPR'*'EXPR {addqruple("*",$1,$3,$$);}
    |EXPR'/'EXPR {addqruple("/",$1,$3,$$);}
    |'('EXPR')'EXPR {strcpy($$,$2);}
    |'-'EXPR {addqruple("uminus",$2,"",$$);}
    |VAR
    |NUM
    ;

%%

int main()
{

yyparse();
printf("\n\nthree address code");
for(i=0;i<index1;i++)
{
 printf("\n %s\t %c\t %s\t %s\t %s\n",q[i].result, '=', q[i].arg1,q[i].op,q[i].arg2);
}
printf("\n\nINDEX\t OP\t ARG1\t ARG2\t RESULT");
for(i=0;i<index1;i++)
{
 printf("\n%d\t %s\t %s\t %s\t %s\n",i,q[i].op,q[i].arg1,q[i].arg2,q[i].result);
}
return 0;
}
void addqruple(char op[5],char arg1[10],char arg2[10],char result[10])
 {
 strcpy(q[index1].op,op);
 strcpy(q[index1].arg1,arg1);
 strcpy(q[index1].arg2,arg2);
 sprintf(q[index1].result,"t%d",tindex++);
 strcpy(result,q[index1++].result);  
 }

int yyerror()
{ 
printf("syntax error");
}
int yywrap()
{
return 1;
}








