#include "s21_grep.h"

// Главная функция программы
int main(int argc, char *argv[]) {
  int firv = 0;
  // Инициализация структуры для хранения опций
  struct grep_opt mushroom = {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, 0, NULL, 0};
  mushroom.sample = memory_on();  // Выделение памяти для хранения паттернов
  mushroom.files = memory_on();  // Выделение памяти для хранения файлов
  // Если память выделена успешно
  if (mushroom.sample != NULL && mushroom.files != NULL) {
    // Разбор опций командной строки
    firv = exam_options(argc, argv, &mushroom);
    // Если разбор опций успешен и результат не равен 2
    if (firv != 0 && firv != 2) {
      searht_samples(argc, argv, &mushroom);  // Поиск паттернов
      cartyceps(&mushroom);  // Выполнение поиска с учетом опций
    } else if (firv == 0) {
      fprintf(stderr, "Error!\n");
    }
    // Освобождение памяти
    memory_off(mushroom.sample);
    memory_off(mushroom.files);
  }

  return 0;
}

// Функция для разбора опций командной строки
int exam_options(int argc, char *argv[], struct grep_opt *msd) {
  int flag = 1, flag_opt;
  // Определение возможных опций
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  // Цикл разбора опций
  while ((flag_opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                                 NULL)) != -1) {
    // Обработка опций
    switch (flag_opt) {
      case 'e':
        msd->eflag = 1;
        snprintf(msd->sample[msd->sample_count], PAM, "%s", optarg);
        (msd->sample_count)++;
        break;
      case 'i':
        msd->iflag = 1;
        break;
      case 'v':
        msd->vflag = 1;
        break;
      case 'c':
        msd->cflag = 1;
        break;
      case 'l':
        msd->lflag = 1;
        break;
      case 'n':
        msd->nflag = 1;
        break;
      case 'h':
        msd->hflag = 1;
        break;
      case 's':
        msd->sflag = 1;
        break;
      case 'f':
        msd->fflag = 1;
        sample_flagf(msd, &flag);
        break;
      case '?':
        flag = 2;
        fprintf(stderr,
                "usage:s21_grep[-abcDEFGHhIiJLlmnOoqRSsUVvwxZ][-Anum][-Bnum] "
                "[-C[num]]\n");
        break;
    }
  }
  return flag;
}

// Функция поиска паттернов и файлов среди аргументов
void searht_samples(int argc, char *argv[], struct grep_opt *msd) {
  int flag = 0;
  // Если флаги e и f не установлены
  if (msd->eflag != 1 && msd->fflag != 1) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        if (flag != 1) {
          // Запись паттерна
          snprintf(msd->sample[msd->sample_count], PAM, "%s", argv[i]);
          (msd->sample_count)++;
          flag = 1;
        } else {
          // Запись файла
          snprintf(msd->files[msd->files_count], PAM, "%s", argv[i]);
          (msd->files_count)++;
        }
      }
    }
  }
  // Если установлены флаги e или f
  if (msd->eflag == 1 || msd->fflag == 1) {
    for (int i = optind; i < argc; i++) {
      // Запись файла
      snprintf(msd->files[msd->files_count], PAM, "%s", argv[i]);
      (msd->files_count)++;
    }
  }
}

// Функция обработки флага f
void sample_flagf(struct grep_opt *msd, int *flag) {
  char *str_f = NULL, current_symbol;
  int i = 0;
  // Открытие файла с паттернами
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    str_f = (char *)malloc(PAM * sizeof(char));
    if (str_f != NULL) {
      // Чтение паттернов из файла
      while ((current_symbol = fgetc(file)) != EOF) {
        if (current_symbol != '\n') {
          str_f[i] = current_symbol;
          i++;
        }
        if (current_symbol == '\n') {
          current_symbol = '\0';
          str_f[i] = current_symbol;
          // Запись паттерна
          snprintf(msd->sample[msd->sample_count], PAM, "%s", str_f);
          i = 0;
          (msd->sample_count)++;
        }
      }
      current_symbol = '\0';
      str_f[i] = current_symbol;
      // Запись последнего паттерна
      snprintf(msd->sample[msd->sample_count], PAM, "%s", str_f);
      (msd->sample_count)++;
      free(str_f);
    }
    fclose(file);
  } else {
    (*flag) = 0;
  }
}

// Функция выделения памяти
char **memory_on() {
  char **wsx = NULL;
  wsx = (char **)malloc(PAM * sizeof(char *));
  for (int i = 0; i < PAM; i++) {
    wsx[i] = (char *)malloc(PAM * sizeof(char));
  }
  return wsx;
}

// Функция освобождения памяти
void memory_off(char **wer) {
  for (int i = 0; i < PAM; i++) {
    free(wer[i]);
  }
  free(wer);
}

// Функция обработки файлов и паттернов с учетом установленных флагов
void cartyceps(struct grep_opt *msd) {
  char str_symbol, last_symbol = '\n';
  struct flag_grep stalk = {0, 0, 0, 0, 0, 0, 0, NULL};
  stalk.clicker = (char *)malloc(PAM * sizeof(char));
  if (stalk.clicker != NULL) {
    for (int i = 0; i < msd->files_count; i++) {
      FILE *file = fopen(msd->files[i], "r");
      if (file == NULL) {
        if (msd->sflag != 1) fprintf(stderr, "Error!\n");
      } else {
        while ((str_symbol = fgetc(file)) != EOF) {
          if (last_symbol == '\n' && str_symbol != '\n') ++stalk.count_str;
          last_symbol = str_symbol;
        }
        fseek(file, 0, SEEK_SET);
        while (!feof(file)) {
          if (fgets(stalk.clicker, PAM, file) != NULL) {
            stalk.count_n++;
            template_validation(&stalk, msd);
            process_option(&stalk, msd, i);
            stalk.flag_reg = 0;
          }
        }
        restart_flags(&stalk);
        fclose(file);
      }
    }
    free(stalk.clicker);
  }
}

// Функция проверки совпадений паттернов с текущей строкой файла
void template_validation(struct flag_grep *stalk, struct grep_opt *msd) {
  regex_t regex;
  for (int j = 0; j < msd->sample_count; j++) {
    if (msd->iflag == 1) {
      regcomp(&regex, msd->sample[j], REG_ICASE | REG_NEWLINE);
    } else {
      regcomp(&regex, msd->sample[j], REG_NEWLINE);
    }
    if (!regexec(&regex, stalk->clicker, 0, NULL, 0)) {
      (stalk->flag_reg)++;
      (stalk->count_cl)++;
    }
    regfree(&regex);
  }
  if (stalk->flag_reg > 0)
    (stalk->count_c)++;
  else
    (stalk->count_cv)++;
}

// Функция сброса флагов и счетчиков
void restart_flags(struct flag_grep *stalk) {
  stalk->flag_l = 0;
  stalk->count_str = 0;
  stalk->count_n = 0;
  stalk->count_c = 0;
  stalk->count_cv = 0;
  stalk->count_cl = 0;
}

// Функция выбора обработки в зависимости от установленных флагов
void process_option(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  if (msd->lflag == 1 && msd->cflag != 1) {
    process_l(stalk, msd, i);
  } else if (msd->lflag == 1 && msd->cflag == 1) {
    process_lc(stalk, msd, i);
  } else if (msd->cflag == 1 && msd->lflag != 1) {
    process_c(stalk, msd, i);
  } else {
    if (msd->nflag == 1)
      process_n(stalk, msd, i);
    else
      process(stalk, msd, i);
  }
}

// Функция обработки флага l (вывод имен файлов с совпадениями)
void process_l(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  if (msd->vflag == 1 && stalk->flag_l != 1) {
    if (stalk->flag_reg == 0) {
      printf("%s\n", msd->files[i]);
      stalk->flag_l = 1;
    }
  } else if (msd->vflag != 1 && stalk->flag_l != 1) {
    if (stalk->flag_reg > 0) {
      printf("%s\n", msd->files[i]);
      stalk->flag_l = 1;
    }
  }
}

void process_lc(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  // Если установлен флаг v (вывод строк, НЕ содержащих совпадений)
  if (msd->vflag == 1) {
    // Если обрабатывается один файл или установлен флаг h (не выводить имена
    // файлов)
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      if (stalk->count_n == stalk->count_str && stalk->count_cl == 0)
        printf("1\n%s\n", msd->files[i]);
      else if (stalk->count_n == stalk->count_str && stalk->count_cl > 0)
        printf("0\n");
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      if (stalk->count_n == stalk->count_str && stalk->count_cl == 0)
        printf("%s:1\n%s\n", msd->files[i], msd->files[i]);
      else if (stalk->count_n == stalk->count_str && stalk->count_cl > 0)
        printf("%s:0\n", msd->files[i]);
    }
  } else {  // Если флаг v не установлен
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      if (stalk->count_n == stalk->count_str && stalk->count_cl > 0)
        printf("1\n%s\n", msd->files[i]);
      else if (stalk->count_n == stalk->count_str && stalk->count_cl == 0)
        printf("0\n");
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      if (stalk->count_n == stalk->count_str && stalk->count_cl > 0)
        printf("%s:1\n%s\n", msd->files[i], msd->files[i]);
      else if (stalk->count_n == stalk->count_str && stalk->count_cl == 0)
        printf("%s:0\n", msd->files[i]);
    }
  }
}

// Функция обработки флага c (вывод количества совпадений)
void process_c(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  if (msd->vflag ==
      1) {  // Если установлен флаг v (вывод строк, НЕ содержащих совпадений)
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      if (stalk->count_n == stalk->count_str) printf("%d\n", stalk->count_cv);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      if (stalk->count_n == stalk->count_str)
        printf("%s:%d\n", msd->files[i], stalk->count_cv);
    }
  } else {  // Если флаг v не установлен
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      if (stalk->count_n == stalk->count_str) printf("%d\n", stalk->count_c);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      if (stalk->count_n == stalk->count_str)
        printf("%s:%d\n", msd->files[i], stalk->count_c);
    }
  }
}

// Функция обработки флага n (вывод номера строки перед строкой)
void process_n(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  if (msd->vflag == 1 &&
      stalk->flag_reg == 0) {  // Если установлены флаги v и n, и совпадений нет
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      printf("%d:%s", stalk->count_n, stalk->clicker);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      printf("%s:%d:%s", msd->files[i], stalk->count_n, stalk->clicker);
    }
  } else if (msd->vflag != 1 &&
             stalk->flag_reg > 0) {  // Если установлен флаг n и есть совпадения
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      printf("%d:%s", stalk->count_n, stalk->clicker);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      printf("%s:%d:%s", msd->files[i], stalk->count_n, stalk->clicker);
    }
  }
}

// Функция обработки случая без флагов n и v
void process(struct flag_grep *stalk, struct grep_opt *msd, int i) {
  if (msd->vflag == 1 &&
      stalk->flag_reg == 0) {  // Если установлен флаг v и нет совпадений
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      printf("%s", stalk->clicker);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      printf("%s:%s", msd->files[i], stalk->clicker);
    }
  } else if (msd->vflag != 1 &&
             stalk->flag_reg >
                 0) {  // Если совпадения есть и флаг v не установлен
    if (msd->files_count == 1 || (msd->files_count > 1 && msd->hflag == 1)) {
      printf("%s", stalk->clicker);
    } else if (msd->files_count > 1 && msd->hflag != 1) {
      printf("%s:%s", msd->files[i], stalk->clicker);
    }
  }
}
