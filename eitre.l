%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "eitre.tab.h"

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
"<="    {yylval.ival=1; return LEQ;}
"&"    {return T_AND;}
"|"    {return T_OR;}
"%"    {return T_SEQCOMP;}
"["    {return T_SLEFT;}
"]"    {return T_SRIGHT;}
"("		{return T_LEFT;}
")"		{return T_RIGHT;}
"EPS"   {return T_EPS;}

%%