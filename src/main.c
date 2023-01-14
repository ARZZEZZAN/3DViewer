#include "s21_3DViewer_v1.h"
void printf_matrix(matrix_t matrix);
void printf_polygons(data_t data);

int main() {
  data_t data = {0};
  char model_file_name[size] = "./objFiles/cube.obj";

  if (s21_parsing(&data, model_file_name)) {
    printf("ok\n");
  } else {
    printf("error\n");
  }
  printf("count_of_vertexes = %d\n", data.count_of_vertexes);
  printf("count_of_facets = %d\n", data.count_of_facets);
  printf_matrix(data.matrix_3d);
  printf_polygons(data);
  s21_remove_matrix(&data.matrix_3d);
  s21_remove_polygons(data);
  return 0;
}

void printf_matrix(matrix_t matrix) {
  printf("\nmatrix:\n");
  printf("{\n");
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.cols; j++) {
      printf("%lf, ", matrix.matrix[i][j]);
    }
    printf("\n");
  }
  printf("}");
}

void printf_polygons(data_t data) {
  printf("\npolygons:\n");
  printf("{\n");
  for (int i = 0; i < data.count_of_facets; i++) {
    for (int j = 0; j < data.polygons[i].numbers_of_vertexes_in_facets * 2;
         j++) {
      printf("%d, ", data.polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  printf("}");
}