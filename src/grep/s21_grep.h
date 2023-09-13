#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>  // для обработки аргументов командной строки
#include <regex.h>  // для работы с регулярными выражениями
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAM 1000  // максимальная длина строки

// структура для хранения опций grep
struct grep_opt {
  int eflag;  // флаг -e, позволяющий указать регулярное выражение
  int iflag;  // флаг -i, игнорировать регистр при поиске
  int vflag;  // флаг -v, инвертировать поиск (найти строки, которые НЕ
              // совпадают с шаблоном)
  int cflag;  // флаг -c, подсчитать количество строк с совпадениями
  int lflag;  // флаг -l, выводить только имена файлов с совпадениями
  int nflag;  // флаг -n, выводить номера строк с совпадениями
  int hflag;  // флаг -h, не выводить имя файла с совпадениями
  int sflag;  // флаг -s, подавить вывод ошибок
  int fflag;  // флаг -f, читать шаблоны из файла
  char **sample;     // массив шаблонов для поиска
  int sample_count;  // количество шаблонов
  char **files;      // массив имен файлов
  int files_count;   // количество файлов
};
// структура для хранения данных, связанных с флагами
struct flag_grep {
  int flag_reg;   // флаг совпадения шаблона
  int flag_l;     // флаг для обработки -l
  int count_cl;   // счетчик совпадений
  int count_cv;   // счетчик строк без совпадений
  int count_str;  // счетчик строк
  int count_c;    // счетчик для обработки -c
  int count_n;    // счетчик для обработки -n
  char *clicker;  // буфер для хранения строки
};

// прототипы функций
int exam_options(int argc, char *argv[],
                 struct grep_opt *msd);  // разбор опций командной строки
void searht_samples(int argc, char *argv[],
                    struct grep_opt *msd);  // поиск шаблонов
void sample_flagf(struct grep_opt *msd, int *flag);  // чтение шаблонов из файла
void cartyceps(struct grep_opt *msd);  // выполнение grep
void process_option(struct flag_grep *stalk, struct grep_opt *msd,
                    int i);  // обработка опций
void process_l(struct flag_grep *stalk, struct grep_opt *msd,
               int i);  // обработка флага -l
void process_lc(struct flag_grep *stalk, struct grep_opt *msd,
                int i);  // обработка флагов -l и -c
void process_c(struct flag_grep *stalk, struct grep_opt *msd,
               int i);  // обработка флага -c
void process_n(struct flag_grep *stalk, struct grep_opt *msd,
               int i);  // обработка флага -n
void process(struct flag_grep *stalk, struct grep_opt *msd,
             int i);  // обработка остальных флагов
void template_validation(struct flag_grep *stalk,
                         struct grep_opt *msd);  // проверка совпадения шаблонов
void restart_flags(
    struct flag_grep *stalk);  // сброс флагов для следующей строки
char **memory_on();  // выделение памяти для массива указателей
void memory_off(char **wer);  // освобождение памяти

#endif
