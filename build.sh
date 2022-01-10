bison -d --report=all --report-file=report grammar.y 
flex lexer.l
g++ -g -O -c grammar.tab.c
g++ -g -O -c lex.yy.c
g++ -g -O -c Memory.cpp
g++ -g -O -c Nodes.cpp
g++ -o interpreter lex.yy.o Memory.o Nodes.o grammar.tab.o
