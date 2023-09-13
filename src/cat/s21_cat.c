#include "s21_cat.h"

int main(int argc, char *argv[]) {
  options_t options = {0};  // Инициализация структуры options
  // Обработка аргументов командной строки
  while ((options.opt_result = getopt_long(argc, argv, short_options,
                                           long_options, NULL)) != -1) {
    flags(
        &options);  // Устанавливаем флаги на основе аргументов командной строки
  }
  // Обработка файлов
  while (argv[optind] != NULL) {
    reading_file(argv[optind], &options);  // Читаем файл и обрабатываем опции
    optind++;  // Переходим к следующему файлу
  }
  return 0;
}

// Реализация обработки опций для файла
void options_implementation(FILE *file, options_t *options) {
  // Инициализация переменных
  options->nonblank_count = 0;
  options->all_count = 0;
  options->curr_position = 0;
  options->curr_line = 0;
  options->next_line = 0;
  options->line_flag = 1;

  // Если не было ошибок при обработке опций, читаем файл и обрабатываем опции
  if (!options->opt_error) {
    while ((options->character = fgetc(file)) != EOF) {
      int s = s_options(options);  // Обработка опции -s (squeeze-blank)
      if (s) continue;  // Если выполняется опция -s, пропускаем текущий символ
      b_options(options);  // Обработка опции -b (number-nonblank)
      n_options(options);  // Обработка опции -n (number)
      t_options(options);  // Обработка опции -T (show-tabs)
      e_options(options);  // Обработка опции -E (show-ends)
      v_options(options);  // Обработка опции -v (show-nonprinting)
      options->line_flag =
          (options->character == '\n')
              ? 1
              : 0;  // Устанавливаем флаг line_flag в зависимости от того,
                    // является ли символ концом строки
      printf("%c", options->character);  // Выводим символ
    }
  }
}

// Функция для чтения файла и обработки опций
void reading_file(char argv[optind], options_t *options) {
  FILE *file = fopen(argv, "r");  // Открываем файл для чтения
  if (file != NULL) {
    options_implementation(file, options);  // Обрабатываем опции для файла
    fclose(file);                           // Закрываем файл
  } else {
    fprintf(stderr, "s21_cat: %s: No such file or directory",
            argv);  // Если файл не найден, выводим сообщение об ошибке
  }
}

// Функция для установки флагов на основе опций командной строки
void flags(options_t *options) {
  switch (options->opt_result) {
    case 'b':
      options->num_nonblank_flag = 1;
      break;
    case 'E':
      options->show_ends_flag = 1;
      break;
    case 'e':
      options->show_ends_flag = 1;
      options->show_nonprinting_flag = 1;
      break;
    case 'n':
      options->num_all_flag = 1;
      break;
    case 's':
      options->squeeze_blank_flag = 1;
      break;
    case 'T':
      options->show_tabs_flag = 1;
      break;
    case 't':
      options->show_tabs_flag = 1;
      options->show_nonprinting_flag = 1;
      break;
    case 'v':
      options->show_nonprinting_flag = 1;
      break;
    case '?':
    default:
      fprintf(stderr,
              "usage: s21_cat [-benstv] [file ...]\n");  // Выводим сообщение об
                                                         // ошибке при неверном
                                                         // использовании опций
      options->opt_error = 1;
      break;
  }
}

// Функция для обработки опции -s (squeeze-blank)
int s_options(options_t *options) {
  int skip = 0;
  if (options->squeeze_blank_flag) {
    options->curr_line = 0;
    if (!options->curr_position && options->character == '\n')
      options->curr_line = 1;
    if (options->character == '\n' && options->curr_position)
      options->curr_position = 0;
    if (options->character != '\n' && !options->curr_position)
      options->curr_position = 1;
    if (options->curr_line && options->next_line) skip = 1;
    options->next_line = options->curr_line;
  }
  return skip;
}

// Функция для обработки опции -b (number-nonblank)
void b_options(options_t *options) {
  if (options->num_nonblank_flag) {
    if (options->line_flag && options->character != '\n')
      printf("%6d\t", ++options->nonblank_count);
  }
}

// Функция для обработки опции -n (number)
void n_options(options_t *options) {
  if (options->num_all_flag) {
    if (options->line_flag && !options->num_nonblank_flag)
      printf("%6d\t", ++options->all_count);
  }
}

// Функция для обработки опции -T (show-tabs)
void t_options(options_t *options) {
  if (options->show_tabs_flag) {
    if (options->character == '\t') {
      printf("^");
      options->character = 'I';
    }
  }
}

// Функция для обработки опции -E (show-ends)
void e_options(options_t *options) {
  if (options->show_ends_flag) {
    if (options->character == '\n') printf("$");
  }
}

void v_options(options_t *options) {
  if (options->show_nonprinting_flag) {
    if (options->character < 32 && options->character != 9 &&
        options->character != 10) {
      printf("^");
      options->character = options->character + 64;
    } else if (options->character == 127) {
      printf("^");
      options->character = options->character - 64;
    }
  }
}
