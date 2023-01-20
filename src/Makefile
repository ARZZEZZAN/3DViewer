CC=gcc
STDFLAGS=-Wall -Werror -Wextra -std=c11 #-fsanitize=address
TST_CFLAGS:= -g $(STDFLAGS)
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose 

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, ${SRC})
# HEADER=$(wildcard s21_*.h)

PREF_TEST_SRC=./our_test/
TEST_SRC=$(wildcard $(PREF_TEST_SRC)/*.c)
# TEST_OBJ = $(patsubst %.c,%.o, ${TEST_SRC})

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install dvi open_exe

install:
	make clean
	mkdir build
	cd ui && qmake && make && make clean && rm Makefile && cd ../ && mv ui/3DViewer.app build

uninstall:
	rm -rf build*
	rm -rf ui/build*
	rm -rf ${HOME}/3DViewer_v1.0

open_exe:
	$(OPEN_CMD) build/3DViewer.app

dvi:
	$(OPEN_CMD) readme.html

dist:
	rm -rf 3DViewer_v1.0/
	mkdir 3DViewer_v1.0/
	mkdir 3DViewer_v1.0/src
	mv ./build/SmartCalc.app 3DViewer_v1.0/src/
	tar cvzf 3DViewer_v1.0.tgz 3DViewer_v1.0/
	rm -rf 3DViewer_v1.0/

tests:
ifeq ($(OS), Darwin)
	${CC} $(STDFLAGS) ${TEST_SRC} ${SRC} -o unit_test $(LIBS) -g
else
	${CC} $(STDFLAGS) ${TEST_SRC} ${SRC} -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
else
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

leaks:
	$(CC) $(TST_CFLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
	leaks -atExit -- ./test

valgrind:
	$(CC) $(TST_CFLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clean_obj:
	rm -rf *.o

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf unit_test
	rm -rf report
	rm -rf unit_test.dSYM

clean: clean_test clean_obj
	rm -rf test
	rm -rf RESULT_VALGRIND.txt
	rm -rf 3DViewer_v1.0
	rm -rf 3DViewer_v1.0.tgz

.PHONY: all clean check lcov
