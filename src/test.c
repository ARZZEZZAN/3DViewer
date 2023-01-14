#include "s21_3DViewer_v1.h"
int main() {
  int s_size = 10;
  polygon_t *polygon = (polygon_t *)calloc((s_size), sizeof(polygon_t));
  polygon[0].numbers_of_vertexes_in_facets = 0;
  printf("polygon[0].numbers_of_vertexes_in_facets = %d\n",
         polygon[0].numbers_of_vertexes_in_facets);
  return 0;
}
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