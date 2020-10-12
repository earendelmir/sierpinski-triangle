#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define NUM_VERTICES 3
// change these parameters. They won't affect the execution of the program, just its appearance
#define NUM_POINTS 1200
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 1000


struct Point { int x, y; };


void initVertices(struct Point *vertices);
struct Point *firstPoint(const struct Point *vertices);
void randomCoordinates(struct Point *point);
void nextPoint(const struct Point *vertices, struct Point *points, unsigned int num_points, const struct Point *last_point);
struct Point halfWay(const struct Point *a, const struct Point *b);
bool sameCoordinates(const struct Point *a, const struct Point *b);
void write_points_to_file(const char *file_path, const struct Point *points, unsigned int num_points);
FILE *openFile(const char *path, const char *mode);
void draw(void);



int main(void) {
  struct Point vertices[NUM_VERTICES];
  struct Point points[NUM_POINTS];
  unsigned int num_points = 0;
  srand(time(NULL));

  initVertices(vertices);
  printf("Created %hu vertices.\n", NUM_VERTICES);

  nextPoint(vertices, points, num_points, firstPoint(vertices));
  printf("Created %u points.\n", NUM_POINTS);

  write_points_to_file(".vertices", vertices, NUM_VERTICES);
  write_points_to_file(".points", points, NUM_POINTS);
  draw();
  return (EXIT_SUCCESS);
}



// initializes the vertices in an equilateral triangle shape
void initVertices(struct Point *vertices) {
  short int down_x = CANVAS_WIDTH/2 - 20;
  // the two vertices at the bottom are at the same distance from the center of the canvas (where x = 0)
  short int left_down_x = -down_x;
  short int right_down_x = down_x;
  short int down_y = -(CANVAS_HEIGHT/2 - 80);
  // the height of the triangle is calculated with the Pythagorean Theroem. Height = sqrt(hypotenuse^2 - side^2)
  short int up_y = sqrt((down_x*2)*(down_x*2) - down_x*down_x) + down_y;
  // the topmost vertix is at the center of the canvas
  short int up_x = 0;

  vertices[0].x = left_down_x;
  vertices[0].y = down_y;
  vertices[1].x = right_down_x;
  vertices[1].y = down_y;
  vertices[2].x = up_x;
  vertices[2].y = up_y;
}



// calculates the position of the first point
struct Point *firstPoint(const struct Point *vertices) {
  bool acceptable = false;
  struct Point *point = (struct Point *)malloc(sizeof(struct Point));

  while (!acceptable) {
    // gives the point random coordinates in the canvas
    randomCoordinates(point);
    acceptable = true;
    // if the point happens to be on top of one of the vertices it has to be moved somewhere else */
    for (unsigned short int i = 0; i < NUM_VERTICES; i++)
      if (sameCoordinates(point, &vertices[i])) {
        acceptable = false;
        break;
      }
  }

  return point;
}



// gets a random value for a point's coordinates
void randomCoordinates(struct Point *point) {
  // Python's Turtle library divides the screen in 4 spaces. The center point has coordinates (0,0).
  // Going rigth increases x while leftwards x becomes negative. Going up increases y while downwards y becomes negative.

  point->x = rand() % (CANVAS_WIDTH/2 - 40);
  // every x coordinate has a 50% chance of being negative
  if (rand() % 100 > 50)
    point->x = -point->x;

  point->y = rand() % (CANVAS_HEIGHT/2 - 100);
  //bevery y coordinate has a 50% chance of being negative
  if (rand() % 100 > 50)
    point->y = -point->y;
}



// gets the next point in the series. (recursive function)
void nextPoint(const struct Point *vertices, struct Point *points, unsigned int num_points, const struct Point *last_point) {
  static int iterations = -3;
  if (iterations > NUM_POINTS)
    return;

  // chooses a random vertix to consider
  unsigned short int i = rand() % NUM_VERTICES;
  // the new point will be positioned halfway between the chosen vertix and the last point created
  struct Point point = halfWay(&vertices[i], last_point);

  // The iterations counter starts at -3 because I don't want to actually draw the first 3 points.
  // I do this because the first one might occupy a position in the canvas that would - by following the algorithm - be empty.
  // I wait for the points to be aligned before printing any of them.
  if (iterations > 0)
    points[num_points++] = point;

  iterations++;
  nextPoint(vertices, points, num_points, &point);
}



// calculates the middle point between 2 points
struct Point halfWay(const struct Point *a, const struct Point *b) {
  struct Point point = {.x=(a->x + b->x) / 2, .y=(a->y + b->y) / 2};
  return point;
}



// checks wether the 2 given points have the same coordinates
bool sameCoordinates(const struct Point *a, const struct Point *b) {
  return (a->x == b->x && a->y == b->y);
}



// given the file path, the points array and the dimension of the latter, it stores all the points in the file
void write_points_to_file(const char *file_path, const struct Point *points, unsigned int num_points) {
  FILE *file = openFile(file_path, "w");
  for (unsigned short int i = 0; i < num_points; i++)
    fprintf(file, "%d\n%d\n", points[i].x, points[i].y);
  fclose(file);
}



// opens a file and checks if it exists.
FILE *openFile(const char *path, const char *mode) {
  FILE *file = fopen(path, mode);
  if (file == NULL) {
    fprintf(stdout, "Error in handling file \"%s\".\n", path);
    exit (EXIT_FAILURE);
  }
  return file;
}



// calls the python script to draw the simulation
void draw(void) {
  char python_command[60];
  sprintf(python_command, "python3 ./draw_points.py %d %d %d %d", CANVAS_WIDTH, CANVAS_HEIGHT, NUM_VERTICES, NUM_POINTS);
  system(python_command);
}
