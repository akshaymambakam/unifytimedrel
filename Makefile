all: eitre mptre

eitre.tab.c eitre.tab.h: eitre.y
	bison -t -v -d eitre.y

lex.yy.c: eitre.l eitre.tab.h
	flex eitre.l

eitre: lex.yy.c eitre.tab.c eitre.tab.h ./paramtimedrel/*
	g++ -o eitre eitre.tab.c lex.yy.c -lppl -lgmp -lgmpxx

mptre.tab.c mptre.tab.h: mptre.y
	bison -t -v -d mptre.y

mptre.lex.c: mptre.l mptre.tab.h
	flex -o mptre.lex.c  mptre.l

mptre: mptre.lex.c mptre.tab.c mptre.tab.h ./paramtimedrel/*
	g++ -o mptre mptre.tab.c mptre.lex.c -lppl -lgmp -lgmpxx

clean:
	rm eitre eitre.tab.c lex.yy.c eitre.tab.h eitre.output mptre mptre.tab.c mptre.lex.c mptre.tab.h mptre.output
