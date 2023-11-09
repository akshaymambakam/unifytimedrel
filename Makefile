all: eitre

eitre.tab.c eitre.tab.h: eitre.y
	bison -t -v -d eitre.y

lex.yy.c: eitre.l eitre.tab.h
	flex eitre.l

eitre: lex.yy.c eitre.tab.c eitre.tab.h ./paramtimedrel/*
	g++ -o eitre eitre.tab.c lex.yy.c -lppl -lgmp -lgmpxx

clean:
	rm eitre eitre.tab.c lex.yy.c eitre.tab.h eitre.output
