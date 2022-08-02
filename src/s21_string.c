#include "s21_string.h"

/**
 * Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
 * байтах строки, на которую указывает аргумент str.
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ret = S21_NULL;

  short repeat = TRUE;
  for (size_t i = 0; i < n && repeat; i++) {
    if ((char)c == *((char *)str + i)) {
      ret = (char *)((char *)str + i);
      repeat = FALSE;
    }
  }

  return ret;
}

/**
 * Сравнивает первые n байтов str1 и str2
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *string1, *string2;
  string1 = str1;
  string2 = str2;
  int ret = 0;
  while (n > 0 && ret == 0) {
    ret = *string1 - *string2;
    string1++;
    string2++;
    n--;
  }
  return ret;
}

/**
 * Копирует n символов из src в dest
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;
  while (n--) {
    *d = *s;
    d++;
    s++;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  if (dest <= src) {
    for (s21_size_t i = 0; i < n; i++) {
      *((char *)dest + i) = *((char *)src + i);
    }
  } else {
    for (s21_size_t i = n; i > 0; i--) {
      *((char *)dest + i - 1) = *((char *)src + i - 1);
    }
  }
  return dest;
}

/**
 * Копирует символ c (беззнаковый тип) в первые n символов строки,
 * на которую указывает аргумент str
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  if (NULL != str) {
    char *str_with_c = str;
    while (n--) {
      *str_with_c = c;
      str_with_c++;
    }
  }
  return str;
}

/**
 * Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest
 */
char *s21_strcat(char *dest, const char *src) {
  char *d = dest;
  while (*d) d++;
  while (*src) {
    *d = *src;
    d++;
    src++;
  }
  *d = 0;
  return dest;
}

/**
 * Добавляет строку, на которую указывает src, в конец строки,
 * на которую указывает dest, длиной до n символов
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ret = dest;
  while (*ret) ret++;
  while (*src && (n > 0)) {
    *ret = *src;
    ret++;
    src++;
    n--;
  }
  *ret = 0;
  return dest;
}

/**
 * Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке,
 * на которую указывает аргумент str
 */
char *s21_strchr(const char *str, int c) {
  char *ret = S21_NULL;

  short repeat = 1;
  for (size_t i = 0; repeat; i++) {
    if ((char)c == *(str + i)) {
      ret = (char *)(str + i);
      repeat = 0;
    }
    if (0 == *(str + i)) repeat = 0;
  }
  return ret;
}

/**
 * Сравнивает строку, на которую указывает str1,
 * со строкой, на которую указывает str2
 */
int s21_strcmp(const char *str1, const char *str2) {
  while ((*str1 || *str2) && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

/**
 * Сравнивает не более первых n байтов str1 и str2
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t flag = 1;
  int ret = 0;
  while (n && flag) {
    char c1, c2;
    c1 = *str1++;
    c2 = *str2++;
    if (c1 != c2) {
      ret = c1 - c2;
      flag = 0;
    }
    if (!c1) flag = 0;
    n--;
  }
  return ret;
}

/**
 * Копирует строку, на которую указывает src, в dest
 */
char *s21_strcpy(char *dest, const char *src) {
  char *d = dest;
  while ((*dest = *src) != '\0') {
    dest++;
    src++;
  }
  return d;
}

/**
 * Копирует до n символов из строки,
 * на которую указывает src, в dest
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *d = dest;
  while (n) {
    if ((*d = *src) != 0) src++;
    d++;
    n--;
  }
  return dest;
}

/**
 * Вычисляет длину начального сегмента str1,
 * который полностью состоит из символов, не входящих в str2
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s1;
  const char *s2;
  s21_size_t ret = 0;
  s21_size_t flag = 1;
  for (s1 = str1; *s1 != '\0' && flag; s1++) {
    for (s2 = str2; *s2 != '\0' && flag; s2++) {
      if (*s1 == *s2) flag = 0;
    }
    if (flag) ret++;
  }
  return ret;
}

/**
 * Выполняет поиск во внутреннем массиве номера ошибки errnum
 * и возвращает указатель на строку с сообщением об ошибке.
 */
char *s21_strerror(int errnum) {
  static char s21_buffer[MANY] = {'\0'};
  char *ret = s21_buffer;
  if (errnum >= S21_ERROR_COUNT || errnum < 0) {
    if (IS_APPLE)
      s21_sprintf((char *)ret, "Unknown error: %i", errnum);
    else
      s21_sprintf((char *)ret, "No error information");
  } else {
    s21_sprintf((char *)ret, "%s", s21_error_array[errnum]);
  }
  return (char *)ret;
}

/**
 * Вычисляет длину строки str,
 * не включая завершающий нулевой символ
 */
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}

/**
 * Находит первый символ в строке str1,
 * который соответствует любому символу, указанному в str2
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *s1, *s2;
  char *ret = S21_NULL;
  s21_size_t flag = 1;
  for (s1 = str1; *s1 != '\0' && flag; ++s1) {
    for (s2 = str2; *s2 != '\0' && flag; ++s2) {
      if (*s1 == *s2) {
        ret = (char *)s1;
        flag = 0;
      }
    }
  }
  return ret;
}

/**
 * Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке,
 * на которую указывает аргумент str
 */
char *s21_strrchr(const char *str, int c) {
  const char *last = S21_NULL;
  do {
    if (*str == (char)c) last = str;
  } while (*str++);
  return (char *)last;
}

/**
 * Вычисляет длину начального сегмента str1,
 * который полностью состоит из символов str2
 */
s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *s1;
  const char *s2;
  s21_size_t ret = 0;
  for (s1 = str1; *s1 != '\0'; s1++) {
    for (s2 = str2; *s2 != '\0'; s2++) {
      if (*s1 == *s2) break;
    }
    if (*s2 == '\0') return ret;
    ret++;
  }
  return ret;
}

/**
 * Находит первое вхождение всей строки needle (не включая завершающий нулевой
 * символ), которая появляется в строке haystack
 */
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len1 = s21_strlen(haystack);
  s21_size_t len2 = s21_strlen(needle);
  s21_size_t flag = 1;
  char *ret = S21_NULL;
  if (!len2) {
    ret = (char *)haystack;
    flag = 0;
  }
  while (len1 >= len2 && flag) {
    len1--;
    if (!s21_memcmp(haystack, needle, len2)) {
      ret = (char *)haystack;
      flag = 0;
    }
    if (flag) haystack++;
  }
  return ret;
}

/**
 * Разбивает строку str на ряд токенов, разделенных delim
 */
char *s21_strtok(char *str, const char *delim) {
  static char *olds;
  char *token;

  if (str == NULL) str = olds;
  str += s21_strspn(str, delim);

  if (*str == '\0') {
    olds = str;
    token = NULL;
  } else {
    token = str;
    str = s21_strpbrk(token, delim);
    if (str == NULL) {
      olds = s21_memchr(token, '\0', 3000);
    } else {
      *str = '\0';
      olds = str + 1;
    }
  }

  return token;
}

/**
 * Возвращает копию строки(str), преобразованной в верхний регистр.
 * В случае какой-либо ошибки следует вернуть значение NULL
 */
void *s21_to_upper(const char *str) {
  char *res = NULL;
  if (str != NULL) {
    s21_size_t length = s21_strlen(str) + 1;
    res = (char *)calloc(length, sizeof(char));
    if (res != NULL) {
      int i = 0;
      while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
          res[i] = str[i] - ('a' - 'A');
        } else {
          res[i] = str[i];
        }
        i++;
      }
      res[i] = '\0';
    }
  }
  return res;
}

/**
 * Возвращает копию строки (str), преобразованной в нижний регистр.
 * В случае какой-либо ошибки следует вернуть значение NULL
 */
void *s21_to_lower(const char *str) {
  char *res = NULL;
  if (str != NULL) {
    s21_size_t length = s21_strlen(str) + 1;
    res = (char *)calloc(length, sizeof(char));
    if (res != NULL) {
      int i = 0;
      while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          res[i] = str[i] + ('a' - 'A');
        } else {
          res[i] = str[i];
        }
        i++;
      }
      res[i] = '\0';
    }
  }
  return res;
}

/**
 * Возвращает новую строку, в которой указанная строка (str) вставлена
 * в указанную позицию (start_index) в данной строке (src).
 * В случае какой-либо ошибки следует вернуть значение NULL
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = NULL;
  if (src != NULL && str != NULL && start_index <= s21_strlen(src)) {
    s21_size_t length = s21_strlen(str) + s21_strlen(src) + 1;
    res = calloc(length, sizeof(char));
    if (res != NULL) {
      s21_size_t i = 0;
      s21_size_t j = 0;
      for (i = 0; i < start_index; i++) {
        res[i] = src[i];
      }
      for (i = start_index, j = 0; i < (start_index + s21_strlen(str));
           i++, j++) {
        res[i] = str[j];
      }
      for (i = (start_index + s21_strlen(str)), j = start_index; i < length;
           i++, j++) {
        res[i] = src[j];
      }
    }
  }
  return res;
}

/**
 * Возвращает новую строку, в которой удаляются все начальные и конечные
 * вхождения набора заданных символов (trim_chars) из данной строки (src).
 * В случае какой-либо ошибки следует вернуть значение NULL
 */
void *s21_trim(const char *src, const char *trim_chars) {
  char *res = NULL;

  if (src != NULL) {
    s21_size_t length = s21_strlen(src);

    res = calloc((length + 1), sizeof(char));
    if (res != NULL) {
      char *trim_chars_temp;
      if (!trim_chars || !trim_chars[0]) {
        trim_chars_temp = calloc(8, sizeof(char));
        s21_strcpy(trim_chars_temp, WHITE_SPACES);
        trim_chars_temp[6] = '\0';
      } else {
        trim_chars_temp = calloc(s21_strlen(trim_chars) + 1, sizeof(char));
        s21_strcpy(trim_chars_temp, trim_chars);
        trim_chars_temp[s21_strlen(trim_chars)] = '\0';
      }
      s21_size_t l_trim_position = 0;
      s21_size_t r_trim_position = 0;

      char *reversed_src = calloc((length + 1), sizeof(char));
      for (s21_size_t i = 0; i < length; i++) {
        reversed_src[i] = src[length - 1 - i];
      }
      reversed_src[length] = '\0';
      l_trim_position = s21_strspn(src, trim_chars_temp);
      r_trim_position = length - s21_strspn(reversed_src, trim_chars_temp);
      free(reversed_src);
      free(trim_chars_temp);

      s21_size_t i = 0;
      s21_size_t j = 0;

      for (i = l_trim_position, j = 0; i < r_trim_position; i++, j++) {
        res[j] = src[i];
      }
      res[j] = '\0';
    }
  }
  return res;
}
