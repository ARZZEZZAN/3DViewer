#include "s21_3DViewer_v1.h"

int main() {
  data_t data = {0};
  matrix_t matrix = {0};
  char model_file_name[size] = "./objFiles/cube.obj";

  if (parsingData(&data, &matrix, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  printf_matrix(matrix);
  s21_remove_matrix(&matrix);
  return 0;
}

int parsingData(data_t *data, matrix_t *matrix, char *model_file_name) {
  int flag = 1;
  char string_file[size] = {'\0'};
  FILE *f;
  int row = 1;
  if (parsingDataSize(data, model_file_name)) {
    if (s21_create_matrix(++data->count_of_vertexes, 3, matrix) == 0) {
      if ((f = fopen(model_file_name, "r")) != NULL) {
        while (fgets(string_file, size, f)) {
          int step = 0;
          if (parsingСonditions('v', string_file, &step)) {
            for (int i = 0; i < 3; i++) {
              int s = 0;
              double num = 0;
              s21_string_to_double(&string_file[step], &s, &num);
              matrix->matrix[row][i] = num;
              step += s;
            }
            row++;
          }
          string_file[0] = 0;
        }
      } else {
        flag = 0;
      }
    } else {
      flag = 0;
    }
  } else {
    flag = 0;
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
  char string_file[size] = {'\0'};
  if ((f = fopen(model_file_name, "r")) != NULL) {
    while (fgets(string_file, size, f)) {
      if (parsingСonditions('v', string_file, NULL)) {
        data->count_of_vertexes++;
      } else if (parsingСonditions('f', string_file, NULL)) {
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
int parsingСonditions(char c, char *string_file, int *step) {
  int flag = 0;
  int s = 0;
  s21_skip_space(string_file, &s);
  if (string_file[s] == c) {
    if (string_file[s + 1] == ' ') {
      flag = 1;
    }
  }
  step ? *step = s + 2 : 0;
  return flag;
}

/// @brief Создание матриц
/// @param rows
/// @param columns
/// @param result
/// @return 0 - OK 1 - Ошибка, некорректная матрица
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 1;
  if (rows > 0 && columns > 0) {
    double **matrix =
        calloc(rows * columns * sizeof(double) + rows * sizeof(double *), 1);

    if (matrix != NULL) {
      double *ptr = (double *)(matrix + rows);
      for (int i = 0; i < rows; i += 1) {
        matrix[i] = ptr + columns * i;
      }
      result->matrix = matrix;
      result->cols = columns;
      result->rows = rows;
      res = 0;
    }
  }
  return res;
}

/// @brief Обнуление матриц
/// @param A
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) free(A->matrix);
  A->matrix = NULL;
  A->cols = 0;
  A->rows = 0;
}

/// @brief Перевод из строки в double
/// @param str Стартовая строка
/// @param end Указатель на последнее вхождение
/// @param numbur Число
/// @return 1 - ok 0 - error
int s21_string_to_double(char *str, int *step, double *number) {
  int flag = 1;
  double num = 0;
  int dot = 0;
  int i = 0;
  int neg = 1;
  s21_skip_space(str, &i);
  if (s21_is_digit(str[i]) == 0) {
    if (str[i] == '-' || str[i] == '+') {
      if (str[i] == '-') {
        neg = -1;
      }
      i++;
    } else {
      flag = 0;
    }
  }
  if (flag == 1) {
    for (;; i++) {
      if (s21_is_digit(str[i]) == 0) {
        if (str[i] != '.') {
          break;
        }
      }
      if (str[i] == '.') {
        dot = 10;
      }
      if (dot == 0) {
        num = (num * 10) + (double)(str[i] - '0');
      } else if (str[i] != '.') {
        num += (double)(str[i] - '0') / dot;
        dot *= 10;
      }
    }
  }
  *step = i;
  *number = num * neg;
  return flag;
}

/// @brief Поиск цифры
/// @param c
/// @return 0 - если не цифра 1 - если цифра
int s21_is_digit(char c) {
  int flag = 0;
  if (c >= '0' && c <= '9') {
    flag = 1;
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

void printf_matrix(matrix_t matrix) {
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.cols; j++) {
      printf("%lf ", matrix.matrix[i][j]);
    }
    printf("\n");
  }
}