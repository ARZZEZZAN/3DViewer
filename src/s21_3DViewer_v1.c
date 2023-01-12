#include "s21_3DViewer_v1.h"
#define size 1024
int parsingData(data_t *data, matrix_t *matrix, polygon_t *polygon,
                char *model_file_name);
int parsingDataSize(data_t *data, char *model_file_name);
int parsingСonditions(char c, char *string_file);
int s21_is_space(char c);
int s21_skip_space(char *str, int *step);

int main() {
  /*
  // test1
  data_t data = {0};
  char model_file_name[255] = "./objFiles/cube.obj";

  if (parsingData(&data, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  */

  /*
  // test2
  data_t data = {0};
  char model_file_name[255] = "./objFiles/cube1.obj";

  if (parsingData(&data, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  */

  /*
  // test3
  data_t data = {0};
  char model_file_name[255] = "./objFiles/hz.obj";

  if (parsingData(&data, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  */

  data_t data = {0};
  matrix_t matrix = {0};
  polygon_t polygon = {0};
  char model_file_name[size] = "./objFiles/cube.obj";

  if (parsingData(&data, &matrix, &polygon, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  return 0;
}

int parsingData(data_t *data, matrix_t *matrix, polygon_t *polygon,
                char *model_file_name) {
  int flag = 0;
  if (parsingDataSize(data, model_file_name)) {
  }
  return flag;
}

/// @brief Парсинг количества вершин и полигонов
/// @param data структура данных
/// @param model_file_name наименование файла модели
/// @return 1 - ok 0 - error
int parsingDataSize(data_t *data, char *model_file_name) {
  int flag = 1;
  FILE *f;
  if ((f = fopen(model_file_name, "r")) != NULL) {
    char string_file[size] = {'\0'};
    while (fgets(string_file, size, f)) {
      if (parsingСonditions('v', string_file)) {
        data->count_of_vertexes++;
      } else if (parsingСonditions('f', string_file)) {
        data->count_of_facets++;
      }
      string_file[0] = 0;
    }
  } else {
    flag = 0;
  }
  return flag;
}

/// @brief Соответсвие условиям парсинга
/// @param c тип данных obj файла
/// @param string_file строка obj файла
/// @return 1 - ok 0 - error
int parsingСonditions(char c, char *string_file) {
  int flag = 0;
  int step = 0;
  s21_skip_space(string_file, &step);
  if (string_file[step] == c) {
    if (string_file[step + 1] == ' ') {
      flag = 1;
    }
  }
  return flag;
}

/// @brief Пропуск пробелов
/// @param str Стартовая строка
/// @param step Количество пробелов
/// @return 1 - ok 0 - error
int s21_skip_space(char *str, int *step) {
  int flag = 0;
  *step = 0;
  while (s21_is_space(str[*step]) == 1) {
    (*step)++;
    flag = 1;
  }
  return flag;
}

/// @brief Поиск пробела
/// @param c
/// @return 0 - если не пробел 1 - если пробел
int s21_is_space(char c) {
  int flag = 0;
  if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\v') || (c == '\f') ||
      (c == '\r')) {
    flag = 1;
  }
  return flag;
}
