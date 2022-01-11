%option noyywrap
%option yylineno

%{
#include "Nodes.h"
//#include "Datatypes.h"
#include "grammar.tab.h"
#include <stdlib.h>
void yyerror(const char *);
%}

%%
[1-9][0-9]*			          {yylval.ival=atoi(yytext); return INTVAL;}
(true)		                  {yylval.bval=TRUE; return TRUE_;}
(false)		                  {yylval.bval=FALSE; return FALSE_;}
(undefined)                   {yylval.bval=UNDEFINED; return UNDEFINED_;}
(int)		                  {yylval.types_=INT; return INT_;}
(Sint)	                      {yylval.types_=SHORT; return SHORT_;}
(bool)	                      {yylval.types_=BOOL; return BOOL_;}
(vector)	                  {yylval.types_=VECTOR; return VECTOR_;}
(of)	                      {return OF;}
(sizeof)	                  {return SIZEOF;}
(set)                         {return SET;}
(add)		                  {return ADD;}
(sub)		                  {return SUB;}
(smaller)                     {return SMALLER;}
(larger)		              {return LARGER;}
(not[ \t]*or)                 {return NOR;}
(or)	                      {return OR;}
(not[ \t]*and)                {return NAND;}
(and)		                  {return AND;}
(begin)		                  {return BEGIN_;}
(end)		                  {return END;}
(do)		                  {return DO;}
(while)		                  {return WHILE;}
(if)		                  {return IF;}
(then)		                  {return THEN;}
(else)		                  {return ELSE;}
(move)		                  {return MOVE;}
(left)		                  {return LEFT;}
(right)		                  {return RIGHT;}
(lms)	                      {return LMS;}
(function)	                  {return FUNC;}
(print)                       {return PRINT;}
(return)		              {return RETURN;}
[a-zA-Z_][a-zA-Z_0-9]*        {yylval.s_name=new std::string(yytext); return NAME;}

[\[\]\|\{\},\(\);]            {return *yytext;}
[ \t\r\n]+				      ;
.				              {yyerror(yytext);}

%%
