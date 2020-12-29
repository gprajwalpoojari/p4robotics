#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define PI 3.1415
#define CONSTANT PI/180

typedef struct point {
  double x;
  double y;
} point_t;

typedef struct line {
  point_t points[2];
} line_t;

typedef struct polygon {
  int n_sides;
  line_t *lines;
  point_t *points;
} polygon_t;
//calculates cross product between a line and a point
double cross_product(line_t line, point_t point) {
  point_t vector[2];
  vector[0].x = line.points[1].x - line.points[0].x;
  vector[0].y = line.points[1].y - line.points[0].y;
  vector[1].x = point.x - line.points[0].x;
  vector[1].y = point.y - line.points[0].y;
  double product = vector[0].x * vector[1].y - vector[0].y * vector[1].x;
  return product;
}
//returns true if two points lie on the opposite side of a line, else prints false
bool check_opposite(line_t line, line_t points) {
  double cross[2];
  cross[0] = cross_product(line, points.points[0]);
  cross[1] = cross_product(line, points.points[1]);
  if (cross[0] * cross[1] <= 0) {
    //parallel and intersecting/not intersecting case is ambiguous. Hence returns false.
    //This won't be a problem as collisions, if any, can be detected in other combinations of lines.
    if (cross[0] == 0 && cross[1] == 0) {
      return false;
    }
    else {
      return true;
    }
  }
  return false;
}
//returns true if one polygon is contained in another, else returns false
bool contains(polygon_t *polygons) {
  bool check[2] = {true, true};
  for (int i = 0, k = 1; i < 2; i++, k--) {
    int count_pos = 0;
    int count_neg = 0;
    int count_zero = 0;
    for (int j = 0; j < polygons[i].n_sides; j++) {
      if (cross_product(polygons[i].lines[j], polygons[k].points[0]) > 0) {
        count_pos++;
      }
      else if (cross_product(polygons[i].lines[j], polygons[k].points[0]) < 0) {
        count_neg++;
      }
      else {
        count_zero++;
      }
    }
    if (count_pos > 0 && count_neg > 0) {
      check[i] = false;
    }
  }
  return (check[0] || check[1]);
}
//performs translation and rotation of vertices
void transform_points(polygon_t *polygon, double *transformation_matrix) {
  for (int i = 0; i < polygon->n_sides; i++) {
    double x_rotation = polygon->points[i].x * cos(CONSTANT * transformation_matrix[2]) - polygon->points[i].y * sin(CONSTANT * transformation_matrix[2]);
    double y_rotation = polygon->points[i].x * sin(CONSTANT * transformation_matrix[2]) + polygon->points[i].y * cos(CONSTANT * transformation_matrix[2]);
    polygon->points[i].x = x_rotation;
    polygon->points[i].y = y_rotation;
    polygon->points[i].x += transformation_matrix[0];
    polygon->points[i].y += transformation_matrix[1];
  }
}
//enters data for data type line_t inside polygon_t
void construct_lines(polygon_t *polygon) {
  for (int i = 0; i < polygon->n_sides; i++) {
    polygon->lines[i].points[0] = polygon->points[i];
    if (i + 1 == polygon->n_sides) {
      polygon->lines[i].points[1] = polygon->points[0];
    }
    else {
      polygon->lines[i].points[1] = polygon->points[i + 1];
    }
  }
}
//outputs EOF error
void file_error() {
  fprintf(stderr, "Unexpected EOF while reading file\n");
  exit(1);
}
//reads and fills data for tansformation matrix
void read_transformation_matrix(FILE *f, double *transformation_matrix) {
  for (int j = 0; j < 3; j++) {
    double buff;
    fscanf(f, "%lf", &buff);
    if (buff == EOF) {
      file_error();
    }
    transformation_matrix[j] = buff;
  }
}
//reads and fills initial coordinates as mentioned in the FILE
void read_coordinates(FILE *f, polygon_t *polygon) {
  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < polygon->n_sides; k++) {
      double coordinate;
      fscanf(f, "%lf", &coordinate);
      if (coordinate == EOF) {
        file_error();
      }
      if (j == 0) {
        polygon->points[k].x = coordinate;
      }
      else {
        polygon->points[k].y = coordinate;
      }
    }
  }
}

int main(void) {
  polygon_t *polygons = calloc(2, sizeof(polygon_t));
  FILE *f = fopen("polygons.csv", "r");
  if (!f) {
    perror("Could not open polygons.csv");
    exit(1);
  }
  char buff;
  while (buff != '\n') {
    fscanf(f, "%c", &buff);
  }
  for (int i = 0; i < 2; i++) {
    double transformation_matrix[3] = { 0 };
    read_transformation_matrix(f, transformation_matrix);
    int n_points = 0;
    fscanf(f, "%d", &n_points);
    if (n_points == EOF) {
      file_error();
    }
    if (n_points > 16) {
      fprintf(stderr, "Points cannot be greater than 16\n");
      exit(1);
    }
    polygons[i].n_sides = n_points;
    polygons[i].points = calloc(n_points, sizeof(point_t));
    polygons[i].lines = calloc(n_points, sizeof(line_t));

    read_coordinates(f, &polygons[i]);
    transform_points(&polygons[i], transformation_matrix);
    construct_lines(&polygons[i]);
  }
  for (int i = 0; i < polygons[0].n_sides; i++){
    for (int j = 0; j < polygons[1].n_sides;j++) {
      line_t lines[2] = {polygons[0].lines[i], polygons[1].lines[j]};
      bool opposites[2] = {false, false};
      opposites[0] = check_opposite(lines[0], lines[1]);
      opposites[1] = check_opposite(lines[1], lines[0]);
      if (opposites[0] && opposites[1]) {
        printf("Collision\n");
        return 0;
      }
      else {
        if (contains(polygons)) {
          printf("Collision\n");
        }
        else {
          printf("No Collision!\n");
        }
        return 0;
      }
    }
  }
  free(polygons);
}
