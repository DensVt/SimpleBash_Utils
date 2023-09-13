#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdio.h>
#include <string.h>

// Структура для хранения всех флагов
typedef struct {
  int num_nonblank_flag;  // нумерация непустых строк
  int show_ends_flag;  // отображения символа $ в конце каждой строки
  int squeeze_blank_flag;  // сжатия последовательности пустых строк до одной
  int show_tabs_flag;  // отображения символов табуляции как ^I
  int show_nonprinting_flag;  // отображения непечатаемых символов в виде
                              // ^-символ или M-символ
  int num_all_flag;  // нумерация всех строк
  int opt_result;  // Переменная для хранения результата обработки опций
  int opt_error;  // для хранения ошибок при обработке опций
  char character;  // для хранения текущего символа при чтении файла
  int nonblank_count;  // Счетчик непустых строк
  int curr_position;   // Текущая позиция в строке
  int all_count;       // Счетчик всех строк
  int curr_line;       // Текущая строка
  int next_line;       // Следующая строка
  int line_flag;  // для определения пустой или непустой строки
} options_t;

const char *short_options = "+bEensTtv";  // Строка с короткими опциями
const struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

void options_implementation(
    FILE *file,
    options_t *options);  // Функции для обработки опций и чтения файлов
void reading_file(char argv[optind],
                  options_t *options);  // Реализация обработки опций
void flags(
    options_t *options);  // Установка флагов в зависимости от командной строки
int s_options(options_t *options);  // Обработка опции -s (squeeze-blank)
void b_options(options_t *options);  // Обработка опции -b (number-nonblank)
void n_options(options_t *options);  // Обработка опции -n (number)
void t_options(options_t *options);  // Обработка опции -T (show-tabs)
void e_options(options_t *options);  // Обработка опции -E (show-ends)
void v_options(options_t *options);  // // Обработка опции -v (show-nonprinting)

#endif
