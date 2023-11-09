NAME=timedrel
VERSION=0.3

BASEDIR?=$(shell pwd)
PREFIX?=/usr/local

all: install

install:
	cp -R ./include/timedrel/ $(PREFIX)/include/

uninstall:
	rm -rf $(PREFIX)/include/timedrel

develop:
	mkdir $(PREFIX)/include/timedrel
	ln -s $(BASEDIR)/include/timedrel/* $(PREFIX)/include/timedrel

test: test-main test-bound test-zone test-zone-set  test-temporal

clean: test-clean

test-main:
	g++ test/tests-main.cpp -c -o test/main.o -std=c++14 -fPIC -I include

test-bound:
	g++ test/main.o test/tests-bound.cpp -o test/test-bound -std=c++14 -fPIC -I include
	./test/test-bound -r compact

test-zone:
	g++ test/main.o test/tests-zone.cpp -o test/test-zone -std=c++14 -fPIC -I include
	./test/test-zone -r compact

test-zone-set:
	g++ test/main.o test/tests-zone-set.cpp -o test/test-zone-set -std=c++14 -fPIC -I include
	./test/test-zone-set -r compact

test-temporal:
	g++ test/main.o test/tests-temporal.cpp -o test/test-temporal -std=c++14 -fPIC -I include
	./test/test-temporal -r compact

test-clean:
	rm -rf test/main.o test/test-bound test/test-zone test/test-zone-set test/test-temporal


.PHONY: test develop install uninstall all