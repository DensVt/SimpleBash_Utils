all: s21_cat

s21_cat:
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c -o s21_cat

clean:
	rm -rf s21_cat

rebuild: 
	make clean 
	make all

tests:
	sh test_func_cat.sh