#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define NUM_VERTICES 3
#define NUM_POINTS 700
#define WIDTH 1500
#define HEIGHT 800


typedef struct point {
	int x, y;
} Point;

Point vertices[NUM_VERTICES];
Point points[NUM_POINTS];
unsigned int num = 0;


void init_vertices();
void random_coordinates(int *x, int *y);
Point *first_point();
void next_point(const Point *last);
Point half_way(const Point *a, const Point *b);
void draw();
void write_points_to_file(const char *, const Point *, int);
FILE *OpenFile(const char *, const char *);


int main(int argc, char **argv) {
	srand(time(NULL));
	init_vertices();
	printf("initiated vertices\n");
	next_point(first_point());
	printf("done points\n");

	write_points_to_file(".vertices.txt", vertices, NUM_VERTICES);
	write_points_to_file(".points.txt", points, NUM_POINTS);
	
	draw();
	return (EXIT_SUCCESS);
}



void random_coordinates(int *x, int *y) {
	int negative;
	*x = rand() % (WIDTH/2 - 20);
	*y = rand() % (HEIGHT/2 - 50);
	
	negative = rand() % 100;
	if (negative > 50)
		*x = -*x;
	
	negative = rand() % 100;
	if (negative > 50)
		*y = -*y;
}


void init_vertices() {
	int negative;
	for (unsigned short int i = 0; i < NUM_VERTICES; i++)
		random_coordinates(&vertices[i].x, &vertices[i].y);
}


Point *first_point() {
	Point *p;
	random_coordinates(&p->x, &p->y);	
	return p;
}


void next_point(const Point *last_point) {
	static int iterations = 0;
	if (iterations > NUM_POINTS) return;

	int i = rand() % NUM_VERTICES;
	Point p = half_way(&vertices[i], last_point);

	if (iterations > 3)
		points[num++] = p;

	iterations++;
	next_point(&p);
}


Point half_way(const Point *a, const Point *b) {
	unsigned int x = (a->x + b->x) / 2;
	unsigned int y = (a->y + b->y) / 2;
	Point p = {x, y};
	return p;
}


void draw() {
	char python_command[120];
	sprintf(python_command, "python3 ./draw_points.py %d %d %d %d", WIDTH, HEIGHT, NUM_VERTICES, NUM_POINTS);
	system(python_command);
}


/* given the file path, the points array and the dimension of the latter, it stores all the points in the file */
void write_points_to_file(const char *filename, const Point *pnts, int num) {
	FILE *file = OpenFile(filename, "w");
	for (unsigned short int i = 0; i < num; i++)
		fprintf(file, "%d\n%d\n", pnts[i].x, pnts[i].y);
	fclose(file);
}


/* opens a file and checks if it exists. */
FILE *OpenFile(const char *name, const char *mode) {
	FILE *file = fopen(name, mode);
	if (!file) {
		system("echo \"FILE NOT FOUND\"");
		exit (EXIT_FAILURE);
	}
	return file;
}

