#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
/* change these parameters. They won't affect the execution of the program, just its appearance */
#define NUM_POINTS 1000
#define WIDTH 1000
#define HEIGHT 1000
/* changing the following parameter gives different outcomes but the simulation should work as well
*	 bear in mind I only coded a way to handle 3 vertices.
*	 A higher number would work as well but no pattern would emerge from it
*/
#define NUM_VERTICES 3


typedef struct point {
	int x, y;
} Point;

Point vertices[NUM_VERTICES];
Point points[NUM_POINTS];
unsigned int num = 0;


void init_vertices();
void triangle();
void random_coordinates(int *x, int *y);
Point *first_point();
void next_point(const Point *last);
Point half_way(const Point *a, const Point *b);
bool same_coordinates(const Point *a, const Point *b);
void draw();
void write_points_to_file(const char *, const Point *, int);
FILE *OpenFile(const char *, const char *);
void print_point(const Point *p);



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


/* gets a random value for a point's coordinates */
void random_coordinates(int *x, int *y) {
	int negative;
	/* python Turtle library divides the screen in 4 spaces. The center point has coordinates (0,0).
		 going rigth increases x while leftwards x becomes negative.
		 going up increases y while downwards y becomes negative.
	*/

	/* gets a random value between 0 and the total width (almost) */
	*x = rand() % (WIDTH/2 - 40);
	negative = rand() % 100;	/* every x coordinate has a 50% chance of being negative */
	if (negative > 50)
		*x = -*x;

	/* gets a random value between 0 and the total height of the canvas (almost) */
	*y = rand() % (HEIGHT/2 - 100);
	negative = rand() % 100;	/* every y coordinate has a 50% chance of being negative */
	if (negative > 50)
		*y = -*y;
}


/* get the coordinates of the vertices */
void init_vertices() {
	if (NUM_VERTICES == 3)
		triangle();
	else
		for (unsigned short int i = 0; i < NUM_VERTICES; i++)
			random_coordinates(&vertices[i].x, &vertices[i].y);
}


/* calculates the vertices' coordinates in order to have a regular triangle */
void triangle() {
	int down_x = (rand() % (WIDTH/2 - 10)) + 80;
	int left_down_x = -down_x;
	int right_down_x = down_x;
	int down_y = -(HEIGHT/2 - 80);
	int up_y = sqrt((down_x*2)*(down_x*2) - down_x*down_x) + down_y;
	int up_x = 0;

	vertices[0].x = left_down_x;
	vertices[0].y = down_y;
	vertices[1].x = right_down_x;
	vertices[1].y = down_y;
	vertices[2].x = up_x;
	vertices[2].y = up_y;
}


/* calculates the first point of the series */
Point *first_point() {
	bool acceptable = true;
	Point *p;

	do {
		random_coordinates(&p->x, &p->y);	/* gives the point random coordinates in the canvas */
		for (unsigned short int i = 0; i < NUM_VERTICES; i++) /* for all the vertices */
			if (same_coordinates(p, &vertices[i]))	/* checks that the point just created is not equal to one of them */
				acceptable = false;	/* if it does, it calculates new random coordinates */
	} while (!acceptable);

	return p;
}


/* gets the next point in the series */
void next_point(const Point *last_point) {
	static int iterations = -3;	/* this is a recursive function */
	if (iterations > NUM_POINTS) return;	/* and calls itself for a number of times equal to the number of points to calculate */

	int i = rand() % NUM_VERTICES;	/* chooses a random vertix to consider */
	Point p = half_way(&vertices[i], last_point);	/* the new point will be at halfway between the chosen vertix and the last point */

	/* the iterations count starts at -3 because I don't want to visualize the first 3 points.
		 This because the first one might occupy a position in the canvas that would otherwise - according to Sierpinski's algorythm -
		 be empty. So I wait for the points to be aligned before printing any of them.
		 Usually after the first 2 or 3 points it is safe to display them. */
	if (iterations > 0)
		points[num++] = p;

	iterations++;
	next_point(&p);
}


/* calculates the middle point between 2 points */
Point half_way(const Point *a, const Point *b) {
	unsigned int x = (a->x + b->x) / 2;
	unsigned int y = (a->y + b->y) / 2;
	Point p = {x, y};
	return p;
}


/* checks wether the 2 given points are the same by checking their coordinates */
bool same_coordinates(const Point *a, const Point *b) {
	return (a->x == b->x && a->y == b->y);
}


/* calls the python script to draw the simulation */
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


void print_point(const Point *p) {
	printf("x: %d   y: %d\n", p->x, p->y);
}
