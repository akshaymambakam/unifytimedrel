all: eitre mptre pebtre

eitre.tab.c eitre.tab.h: eitre.y
	bison -t -v -d eitre.y

eitre.lex.c: eitre.l eitre.tab.h
	flex -o eitre.lex.c eitre.l

eitre: eitre.lex.c eitre.tab.c eitre.tab.h ./paramtimedrel/*
	g++ -o eitre eitre.tab.c eitre.lex.c -lppl -lgmp -lgmpxx

mptre.tab.c mptre.tab.h: mptre.y
	bison -t -v -d mptre.y

mptre.lex.c: mptre.l mptre.tab.h
	flex -o mptre.lex.c mptre.l

mptre: mptre.lex.c mptre.tab.c mptre.tab.h ./paramtimedrel/*
	g++ -o mptre mptre.tab.c mptre.lex.c -lppl -lgmp -lgmpxx

pebtre.tab.c pebtre.tab.h: pebtre.y
	bison -t -v -d pebtre.y

pebtre.lex.c: pebtre.l pebtre.tab.h
	flex -o pebtre.lex.c pebtre.l

pebtre: pebtre.lex.c pebtre.tab.c pebtre.tab.h ./paramtimedrel/*
	g++ -o pebtre pebtre.tab.c pebtre.lex.c -lppl -lgmp -lgmpxx

clean:
	rm eitre eitre.tab.c eitre.lex.c eitre.tab.h eitre.output mptre mptre.tab.c mptre.lex.c mptre.tab.h mptre.output pebtre pebtre.tab.c pebtre.lex.c pebtre.tab.h pebtre.output
