%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "pebtre.tab.h"

%}

%%

[ \t]	; // ignore all whitespace
[0-9]+		   {yylval.ival = atoi(yytext); return T_INT;}
y[0-9]+   	   {
                 yylval.ival = atoi(yytext+1);
                 return Y_STRING;
               }
p[0-9]+        {
                 yylval.ival = atoi(yytext+1);
                 return P_STRING;
               }

[ \t\r\n]+     { ; }

"^+"    {return K_PLUS;}
"+"     {return T_PLUS;}
"-"     {return T_MINUS;}
"*"     {return T_MULTIPLY;}
"<="    {yylval.ival=1; return LEQ;}
">="    {yylval.ival=3; return GEQ;}
"&"    {return T_AND;}
"|"    {return T_OR;}
"%"    {return T_SEQCOMP;}
"["    {return T_SLEFT;}
"]"    {return T_SRIGHT;}
"("		{return T_LEFT;}
")"		{return T_RIGHT;}
"EPS"   {return T_EPS;}

%%