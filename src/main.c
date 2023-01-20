#include "s21_3DViewer_v1.h"
void printf_matrix(matrix_t matrix);
void printf_polygons(data_t data);
void printf_massiv(data_t data);
void max_min_dot(data_t data);
int main() {
  data_t data = {0};
  char model_file_name[S_SIZE] = "./objFiles/Dany.obj";

  if (s21_parsing(&data, model_file_name)) {
    // printf("dot: %d\n", data.count_of_vertexes);
    // printf("pol: %d\n", data.count_of_facets);
    printf_massiv(data);
    // printf("\n");
    // printf_polygons(data);
    max_min_dot(data);
  } else {
    printf("DATA STATUS: ERROR\n");
  }
  s21_remove_data(&data);
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
  for (int i = 0; i < data.count_of_facets; i++) {
    // printf("f ");
    for (int j = 0; j < data.polygons[i].numbers_of_vertexes_in_facets * 2;
         j++) {
      printf("%d", data.polygons[i].vertexes[j]);
      if ((j - 1) != data.polygons[i].numbers_of_vertexes_in_facets * 2) {
        printf(", ");
      }
    }
    printf("\n");
  }
}

void printf_massiv(data_t data) {
  for (int i = 3; i < (data.count_of_vertexes + 1) * 3; i++) {
    // if (((i) % 3 == 0) || i == 0) {
    //   printf("v  ");
    // }
    printf("%.16lf", data.massiv[i]);
    if (((i + 1) % 3 == 0) && ((i - 1) != (data.count_of_vertexes + 1) * 3)) {
      printf(",\n");
    } else {
      printf(", ");
    }
  }
}

void max_min_dot(data_t data) {
  int maxX = 0;
  int minX = 0;

  int maxY = 0;
  int minY = 0;

  int maxZ = 0;
  int minZ = 0;

  int dotMaxX = 0;
  int dotMaxY = 0;
  int dotMaxZ = 0;

  int dotMinX = 0;
  int dotMinY = 0;
  int dotMinZ = 0;

  for (int i = 0; i < data.matrix_3d.rows; i++) {
    for (int j = 0; j < data.matrix_3d.cols; j++) {
      if (j == 0) {
        if (maxX < data.matrix_3d.matrix[i][j]) {
          maxX = data.matrix_3d.matrix[i][j];
          dotMaxX = i;
        }
        if (minX > data.matrix_3d.matrix[i][j]) {
          minX = data.matrix_3d.matrix[i][j];
          dotMinX = i;
        }
      } else if (j == 1) {
        if (maxY < data.matrix_3d.matrix[i][j]) {
          maxY = data.matrix_3d.matrix[i][j];
          dotMaxY = i;
        }
        if (minY > data.matrix_3d.matrix[i][j]) {
          minY = data.matrix_3d.matrix[i][j];
          dotMinY = i;
        }
      } else if (j == 2) {
        if (maxZ < data.matrix_3d.matrix[i][j]) {
          maxZ = data.matrix_3d.matrix[i][j];
          dotMaxZ = i;
        }
        if (minZ > data.matrix_3d.matrix[i][j]) {
          minZ = data.matrix_3d.matrix[i][j];
          dotMinZ = i;
        }
      }
    }
  }
  printf("dotMaxX = %d\n", dotMaxX);
  printf("dotMaxY = %d\n", dotMaxY);
  printf("dotMaxZ = %d\n", dotMaxZ);
  printf("\n");
  printf("dotMinX = %d\n", dotMinX);
  printf("dotMinY = %d\n", dotMinY);
  printf("dotMinZ = %d\n", dotMinZ);
  printf("\n");

  printf("data.matrix_3d.matrix[dotMaxX] = %lf\n",
         data.matrix_3d.matrix[dotMaxX][0]);
  printf("data.matrix_3d.matrix[dotMaxY] = %lf\n",
         data.matrix_3d.matrix[dotMaxY][1]);
  printf("data.matrix_3d.matrix[dotMaxZ] = %lf\n",
         data.matrix_3d.matrix[dotMaxZ][2]);
  printf("\n");

  printf("data.matrix_3d.matrix[dotMinX] = %lf\n",
         data.matrix_3d.matrix[dotMinX][0]);
  printf("data.matrix_3d.matrix[dotMinY] = %lf\n",
         data.matrix_3d.matrix[dotMinY][1]);
  printf("data.matrix_3d.matrix[dotMinZ] = %lf\n",
         data.matrix_3d.matrix[dotMinZ][2]);
}