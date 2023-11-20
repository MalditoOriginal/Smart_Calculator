CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV = -fprofile-arcs -ftest-coverage
CC = gcc
LIBS = -lcheck
RM = rm -rf
SRCS = s21_smartcalc.c
TARGET = Smart_Calculator
OBJS = $(SRCS:.c=.o)
OS := $(shell uname -s)

ifeq ($(OS), Linux)
CFLAGS += -D OS_LINUX
ADD_LIB = -lcheck -lm -lrt -lpthread
TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm
endif
ifeq ($(OS), Darwin)
CFLAGS += -D OS_MAC
ADD_LIB =
TEST_FLAGS =-lcheck
endif

all: s21_smartcalc

s21_smartcalc: s21_smartcalc.a
	$(CC) unit_test.c -lcheck -L. s21_smartcalc.a -o s21_smartcalc

s21_smartcalc.a:
	$(CC) -c $(CFLAGS) $(SRCS)
	ar rcs s21_smartcalc.a $(OBJS)
	ranlib s21_smartcalc.a

install:
	qmake -o Executables/Makefile $(TARGET)/$(TARGET).pro
	cd Executables && make

start: install
	cd Executables/$(TARGET).app/Contents/MacOS && ./$(TARGET)

uninstall: clean
	rm -rf Executables

package: install 
	cd .. && tar -czf $(TARGET).tgz src

test: s21_smartcalc.a
	$(CC) unit_test.c -lcheck -L. s21_smartcalc.a -o smartcalc_test
	./smartcalc_test

gcov_report:
	$(CC) $(GCOV) unit_test.c $(SRCS) -o smartcalc_test -lcheck
	./smartcalc_test
	lcov -t "test" -o test.info -c -d ./
	genhtml test.info -o report
	open report/index.html

clean:
	$(RM) *.a *.o *.info *.gcno *.gcda *.gcov smartcalc_test report a.out s21_smartcalc smartcalc_test.c .clang-format

valgrind_check: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./s21_matrix

leak: test
	CK_FORK=no leaks -atExit -- ./s21_smartcalc

style_test:
	clang-format -style=Google -n *.c *.h

style_change:
	clang-format -style=Google -i *.c *.h

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all install clean test s21_smartcalc.a gcov_report