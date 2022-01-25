%{
#include "Nodes.h"

#include <string>
#include <utility>
#include <memory>
#include <vector>

extern FILE* yyin;
Node* root;
extern int yylineno;
int yylex();
void yyerror(const char*);
%}

%union {
int ival;
std::string* s_name;
Logic bval;
Datatypes types_;
Node* Node_;
std::vector<Node*>* lst;
std::vector<std::pair<Datatypes, std::string>>* params;
std::pair<Datatypes, std::vector<VarDeclaration>>* vd_list;
}

%token <ival> INTVAL
%token <bval> TRUE_ <bval> FALSE_ <bval> UNDEFINED_
%token <types_> INT_ <types_> SHORT_ <types_> BOOL_ <types_> VECTOR_
%token <s_name> NAME
%token DO WHILE IF
%token BEGIN_ END
%token MOVE LEFT RIGHT PRINT
%token SET
%token LMS OF
%token FUNC RETURN
%token SIZEOF
%token THEN
//%token FIRST SECOND
%nonassoc IFX
%nonassoc ELSE
%left S_LARGER S_SMALLER F_LARGER F_SMALLER
%left LARGER SMALLER
%left ADD SUB
%left NAND NOR
%left OR
%left AND
//%nonassoc '['

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
   	stmt_list                                             	{$$=$1; root=$$;
//															delete $1;
															}
	;

stmt_list:
	stmt												    {$$=new StatementList($1);
//															delete $1;
															}
	| stmt_list stmt									    {dynamic_cast<StatementList*>($1)->add($2); $$=$1;
//															delete $1; delete $2;
															}
	;

stmt:
	BEGIN_ END											    {$$=new Node();}
	| BEGIN_ stmt_list END								    {$$=$2;
//															delete $2;
															}
	| ';'												    {$$=nullptr;}
	| expr ';'											    {$$=$1;
//															delete $1;
															}
	| decl ';'											    {$$=$1;
//															delete $1;
															}
    | directions ';'									    {$$=$1;
//															delete $1;
															}
	| expr SET expr ';'									    {$$=new SetNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| DO stmt WHILE expr ';'							    {$$=new LoopNode(yylineno, $4, $2);
//															delete $2; delete $4;
															}
	| IF expr THEN stmt %prec IFX						    {$$=new IfNode(yylineno, $2, $4);
//															delete $2; delete $4;
															}
	| IF expr THEN stmt ELSE stmt						    {$$=new IfNode(yylineno, $2, $4, $6);
//															delete $2; delete $4; delete $6;
															}
	| FUNC NAME argslist BEGIN_ stmt_list END RETURN expr ';' 	{$$=new FDeclNode(yylineno, *$2, $5, *$3, $8);
//																delete $2; delete $3; delete $5; delete $8;
																}
	| PRINT expr ';'                                        {$$=new PrintNode(yylineno, $2);
//															delete $2;
															}
	;

argslist:
	'(' ')'												    {$$=new std::vector<std::pair<Datatypes, std::string>>();}
	| '(' fargs ')'										    {$$=$2;
//															delete $2;
															}
	;

fargs:
	type NAME											    {$$=new std::vector<std::pair<Datatypes, std::string>>();
	                                                         std::pair<Datatypes, std::string> p; p.first=$1; p.second=*$2;
	                                                         $$->push_back(p);
//															delete $2;
															}
	| fargs ',' type NAME								    {std::pair<Datatypes, std::string> p; p.first=$3; p.second=*$4;
                                                             $1->push_back(p); $$=$1;
//															delete $1; delete $4;
															}
	;
decl:
	varlist												    {$$=new VarListNode(yylineno, *$1);
//															delete $1;
															}
	| vecof type NAME SET vecdecl       				    {std::vector<Node*> v;
	                                                         $$= new VecDeclNode(yylineno, $1, *$3, *$5, v);
//															delete $3; delete $5;
															}
	| vecof type NAME indexes							    {std::vector<Node*> v;
	                                                         $$= new VecDeclNode(yylineno, $1, *$3, v, *$4);
//															delete $3; delete $4;
															}
	| vecof type NAME indexes SET vecdecl          		    {$$=new VecDeclNode(yylineno, $1, *$3, *$6, *$4);
//															delete $3; delete $4; delete $6;
															}
	;

varlist:
	type NAME											    {$$=new std::pair<Datatypes, std::vector<VarDeclaration>>();
	                                                         (*$$).first = $1; VarDeclaration p; p.name = *$2; p.init = nullptr; (*$$).second.push_back(p);
//															delete $2;
															}
    | type NAME SET expr									{$$=new std::pair<Datatypes, std::vector<VarDeclaration>>();
                                                             (*$$).first = $1; VarDeclaration p; p.name = *$2; p.init = $4; (*$$).second.push_back(p);
//															delete $2; delete $4;
															}
    | varlist ',' NAME										{VarDeclaration p; p.name = *$3; p.init = nullptr; (*$1).second.push_back(p); $$=$1;
//															delete $1; delete $3;
															}
	| varlist ',' NAME SET expr						        {VarDeclaration p; p.name = *$3; p.init = $5; (*$1).second.push_back(p); $$=$1;
//															delete $1; delete $3; delete $5;
															}
    ;

vecof:
	VECTOR_ OF												{$$=1;}
	| vecof VECTOR_ OF										{$$=$1+1;}
	;

vecdecl:
	'{' expr_list '}'									    {$$=$2;
//															delete $2;
															}
	| '{' vecdecl_list '}'						            {$$=$2;
//															delete $2;
															}
	;

vecdecl_list:
	vecdecl 											    {$$=new std::vector<Node*>(); $$->push_back(new VecDeclNode(yylineno, *$1));
//															delete $1;
															}
	| vecdecl_list ',' vecdecl							    {$1->push_back(new VecDeclNode(yylineno, *$3)); $$=$1;
//															delete $1; delete $3;
															}
	;

expr_list:
     expr                                                   {$$=new std::vector<Node*>(); $$->push_back($1);
//															delete $1;
															}
    | expr_list ',' expr                                    {$1->push_back($3); $$=$1;
///															delete $1; delete $3;
															}
    ;

expr:
	INTVAL													{$$=new IntLeaf(yylineno, $1);}
	| NAME												    {$$=new VarLeaf(yylineno, *$1);
//															delete $1;
															}
	| TRUE_												    {$$=new BoolLeaf(yylineno, $1);}
	| FALSE_											    {$$=new BoolLeaf(yylineno, $1);}
	| UNDEFINED_										    {$$=new BoolLeaf(yylineno, $1);}
	| expr ADD expr										    {$$=new AddNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| expr SUB expr										    {$$=new SubNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| expr OR expr										    {$$=new OrNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| expr NOR expr									        {$$=new NorNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| expr AND expr									    	{$$=new AndNode(yylineno, $1, $3);
//															delete $1; delete $3;
															}
	| expr NAND expr								    	{$$=new NandNode(yylineno, $1, $3);
//															delete $1; delete $3;
                                                            }
    | expr F_SMALLER expr                                   {$$ = new SmallerNode(yylineno, $1, $3, true);}
    | expr S_SMALLER expr                                   {$$ = new SmallerNode(yylineno, $1, $3, false);}
    | expr F_LARGER expr                                    {$$ = new LargerNode(yylineno, $1, $3, true);}
    | expr S_LARGER expr                                    {$$ = new LargerNode(yylineno, $1, $3, false);}
//	| expr '|' expr SMALLER							    	{$$=new SmallerNode(yylineno, $1, $3);
//															delete $1; delete $3;
//															}
//    | expr '|' expr LARGER   							    {$$=new LargerNode(yylineno, $1, $3);
//															delete $1; delete $3;
//															}
	| '(' expr ')'									    	{$$=$2;}
	| SIZEOF '(' type ')'   						    	{$$=new SizeofNode(yylineno, $3);}
	| SIZEOF '(' NAME ')'                                   {$$=new SizeofNode(yylineno, *$3);
//															delete $3;
															}
	| expr indexes									    	{$$=new IndexNode(yylineno, $1, *$2);
//															delete $1; delete $2;
															}
	| NAME '(' callargs ')'							    	{$$=new FcallNode(yylineno, *$1, *$3);
//															delete $1; delete $3;
															}
	| LMS                                                   {$$=new LmsNode();}
	;

callargs:
	expr											    	{$$=new std::vector<Node*>(); $$->push_back($1);
//															delete $1;
															}
	| callargs expr									    	{$1->push_back($2); $$=$1;
//															delete $1; delete $2;
															}
	;

indexes:
	'[' expr ']'										    {$$=new std::vector<Node*>(); $$->push_back($2);
//															delete $1;
															}
	| indexes '[' expr ']'								    {$1->push_back($3); $$=$1;
															//delete $1; delete $3;
															}
	;

type:
	INT_												    {$$=$1;}
	| SHORT_											    {$$=$1;}
	| BOOL_												    {$$=$1;}
	| VECTOR_											    {$$=$1;}
	;

directions:
	MOVE RIGHT											    {$$=new RightNode();}
	| MOVE LEFT											    {$$=new LeftNode();}
	| MOVE												    {$$=new MoveNode();}
	| LEFT												    {$$=new LeftNode();}
	| RIGHT												    {$$=new RightNode();}
	;
%%



void yyerror(char const *s) {
  fprintf(stderr, "%s\n", s);
}



int main() {
	yydebug = 1;
    yyin = fopen("code.txt", "r");
    yyparse();
    fclose(yyin);
//    std::cout << "parse complete" << std::endl;
//    if (!root)
//        std::cout << "error" << std::endl;
//    std::cout << dynamic_cast<StatementList*>(root)->vec.size() << std::endl;
	init(new Memory(), root);
    return 0;
}

