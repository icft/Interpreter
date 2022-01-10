%{
#include "Nodes.h"

#include <string>
#include <utility>
#include <memory>
#include <vector>

extern FILE* yyin;
std::shared_ptr<Node>* root;
extern int yylineno;
int yylex();
void yyerror(const char*);
%}

%union {
int ival;
std::string* s_name;
Logic bval;
Datatypes types_;
std::shared_ptr<Node>* Node_;
std::vector<std::shared_ptr<Node>>* lst;
std::vector<std::pair<Datatypes, std::string>>* params;
std::pair<Datatypes, std::vector<VarDeclaration>>* vd_list;
}

%token WORK
%token <ival> INTVAL
%token <bval> TRUE_ <bval> FALSE_ <bval> UNDEFINED_
%token <types_> INT_ <types_> SHORT_ <types_> BOOL_ <types_> VECTOR_
%token <s_name> NAME
%token DO WHILE IF
%nonassoc THEN
%nonassoc IFX
%nonassoc ELSE
%token BEGIN_ END
%left AND
%left OR
%left NAND
%left NOR
%token MOVE LEFT RIGHT PRINT
%token SET
%token LMS OF
%token FUNC RETURN
%token SIZEOF
%token LARGER SMALLER
%left ADD SUB
%nonassoc '{' '}' '[' ']' '(' ')'

%type <Node_> program
//%type <Node_> maindecl
%type <Node_> stmt_list
%type <Node_> stmt
//%type <Node_> fcall
%type <params> argslist
%type <params> fargs
%type <Node_> decl
%type <vd_list> varlist
%type <ival> vecof
%type <lst> vecdecl
%type <lst> vecdecl_list
%type <lst> expr_list
%type <Node_> expr
%type <lst> callargs
%type <lst> indexes
%type <types_> type
%type <Node_> directions

%%
program:
                                                            {}
    | FUNC WORK '(' ')' stmt                                  {}
    | error                                                 {printf("some error at line %d\n", @1.first_line); yyerror;}
	;

stmt_list:
	stmt												    {}
	| error                                                 {printf("some error at line %d\n", @1.first_line); yyerror;} 
	| stmt_list stmt									    {}
	| stmt_list error                                       {printf("some error at line %d\n", @2.first_line); yyerror;}
	;

stmt:
	BEGIN_ END											    {}
	| BEGIN_ stmt_list END								    {}
	| ';'												    {}
	| expr ';'											    {}
	| decl ';'											    {}
    | directions ';'									    {}
	| expr SET expr ';'									    {}
	| DO stmt WHILE expr ';'							    {}
	| IF expr THEN stmt %prec IFX						    {}
	| IF expr THEN stmt ELSE stmt						    {}
	| FUNC NAME argslist BEGIN_ stmt_list END RETURN expr ';' 	{}
	| PRINT expr ';'                                        {}
	;

argslist:
	'(' ')'												    {}
	| '(' fargs ')'										    {}
	;

fargs:
	type NAME											    {}
	| fargs ',' type NAME								    {}
	;

decl:
	varlist												    {}
	| vecof type NAME SET vecdecl       				    {}
	| vecof type NAME indexes							    {}
	| vecof type NAME indexes SET vecdecl          		    {}
	;

varlist:
	type NAME											    {}
    | type NAME SET expr									{}
    | varlist ',' NAME										{}
	| varlist ',' NAME SET expr						        {}
    ;

vecof:
	VECTOR_ OF												{}
	| vecof VECTOR_ OF										{}
	;

vecdecl:
	'{' expr_list '}'									    {}
	| '{' vecdecl_list '}'						            {}
	;

vecdecl_list:
	vecdecl 											    {}
	| vecdecl_list ',' vecdecl							    {}
	;

expr_list:
    expr                                                    {}
    | expr_list ',' expr                                    {}
    ;

expr:
	INTVAL													{}
	| NAME												    {}
	| TRUE_												    {}
	| FALSE_											    {}
	| UNDEFINED_										    {}
	| expr ADD expr										    {}
	| expr SUB expr										    {}
	| expr OR expr										    {}
	| expr NOR expr									        {}
	| expr AND expr									    	{}
	| expr NAND expr								    	{}
	| expr '|' expr SMALLER							    	{}
	| expr '|' expr LARGER							    	{}
	| '(' expr ')'									    	{}
	| SIZEOF '(' type ')'   						    	{}
	| SIZEOF '(' NAME ')'                                   {}
	| expr indexes									    	{}
	| NAME '(' callargs ')'							    	{}
	| LMS                                                   {}
	;

callargs:
	expr											    	{}
	| callargs expr									    	{}
	;

indexes:
	'[' expr ']'										    {;}
	| indexes '[' expr ']'								    {}
	;

type:
	INT_												    {}
	| SHORT_											    {}
	| BOOL_												    {}
	| VECTOR_											    {}
	;

directions:
	MOVE RIGHT											    {}
	| MOVE LEFT											    {}
	| MOVE												    {}
	| LEFT												    {}
	| RIGHT												    {}
	;
%%



void yyerror (char const *s) {
  fprintf(stderr, "%s\n", s);
}



int main() {
    yyin = fopen("code.txt", "r");
    yydebug = 1;
    yyparse();
    fclose(yyin);
    return 0;
}
