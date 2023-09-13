all: s21_grep

s21_grep:
	gcc -Wall -Werror -Wextra -std=c11 s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep

rebuild: 
	make clean 
	make all

tests:
	sh test_func_grep.sh
