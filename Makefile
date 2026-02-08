CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TESTFLAGS = -fprofile-arcs -ftest-coverage
OS:=$(shell uname)

SRC = $(wildcard library/*.c)
TEST_SRC = $(wildcard tests/*.c)

ifeq ($(OS), Darwin)
	LDFLAGS = -lcheck
else ifeq ($(OS), Linux)
	LDFLAGS = -lcheck -lsubunit -lm
endif

all : clean s21_decimal.a

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(SRC)
	ar rcs s21_decimal.a *.o
	rm -f *.o

test:
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TEST_SRC) $(SRC) -o test $(LDFLAGS)
	./test

gcov_report:
	lcov --capture --directory . --output-file coverage.info --rc geninfo_unexecuted_blocks=1
	genhtml -o report/ coverage.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a tests/*.o
	open ./report/index.html || xdg-open ./report/index.html

clean:
	rm -rf *.o s21_decimal.a *.gc* report test