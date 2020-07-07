#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define NUM_VERTICES 3
/* change these parameters. They won't affect the execution of the program, just its appearance */
#define NUM_POINTS 3500
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 1000


struct Point { int x, y; };



void init_vertices(struct Point *vertices);
struct Point *first_point(const struct Point *vertices);
struct Point *random_coordinates(void);
void next_point(const struct Point *vertices, struct Point *points, unsigned int num_points, const struct Point *last_point);
struct Point half_way(const struct Point *a, const struct Point *b);
bool same_coordinates(const struct Point *a, const struct Point *b);
void write_points_to_file(const char *file_path, const struct Point *points, unsigned int num_points);
FILE *open_file(const char *path, const char *mode);
void draw(void);



int main(int argc, char **argv) {
	struct Point vertices[NUM_VERTICES];
	struct Point points[NUM_POINTS];
	unsigned int num_points = 0;

	srand(time(NULL));
	init_vertices(vertices);
	printf("created vertex points\n");
	next_point(vertices, points, num_points, first_point(vertices));
	printf("created points\n");

	write_points_to_file(".vertices", vertices, NUM_VERTICES);
	write_points_to_file(".points", points, NUM_POINTS);

	draw();
	return (EXIT_SUCCESS);
}



/* gets the coordinates of the vertices */
void init_vertices(struct Point *vertices) {
	/* this initializes the vertices in an equilateral triangle shape */
	short int down_x = (rand() % (CANVAS_WIDTH/2 - 10)) + 80;
	short int left_down_x = -down_x;
	short int right_down_x = down_x;
	short int down_y = -(CANVAS_HEIGHT/2 - 80);
	short int up_y = sqrt((down_x*2)*(down_x*2) - down_x*down_x) + down_y;
	short int up_x = 0;

	vertices[0].x = left_down_x;
	vertices[0].y = down_y;
	vertices[1].x = right_down_x;
	vertices[1].y = down_y;
	vertices[2].x = up_x;
	vertices[2].y = up_y;
}



/* calculates the position of the first point */
struct Point *first_point(const struct Point *vertices) {
	bool acceptable = true;
	struct Point *point = (struct Point *)malloc(sizeof(struct Point));

	do {
		/* gives the point random coordinates in the canvas */
		point = random_coordinates();
		/* if the point happens to be on top of one of the vertices it has to be moved somewhere else */
		for (unsigned short int i = 0; i < NUM_VERTICES; i++)
			if (same_coordinates(point, &vertices[i]))
				acceptable = false;
			else
				acceptable = true;
	} while (!acceptable);

	return point;
}



/* gets a random value for a point's coordinates */
struct Point *random_coordinates(void) {
	struct Point *point = (struct Point *)malloc(sizeof(struct Point));
	/* python Turtle library divides the screen in 4 spaces. The center point has coordinates (0,0).
	 * going rigth increases x while leftwards x becomes negative.
	 * going up increases y while downwards y becomes negative. */

	/* gets a random value between 0 and the total width (almost) */
	point->x = rand() % (CANVAS_WIDTH/2 - 40);
	/* every x coordinate has a 50% chance of being negative */
	if (rand() % 100 > 50)
		point->x = -point->x;

	/* gets a random value between 0 and the total height of the canvas (almost) */
	point->y = rand() % (CANVAS_HEIGHT/2 - 100);
	/* every y coordinate has a 50% chance of being negative */
	if (rand() % 100 > 50)
		point->y = -point->y;
	
	return point;
}



/* gets the next point in the series. (recursive function) */
void next_point(const struct Point *vertices, struct Point *points, unsigned int num_points, const struct Point *last_point) {
	static int iterations = -3;
	if (iterations > NUM_POINTS)
		return;

	/* chooses a random vertix to consider */
	unsigned short int i = rand() % NUM_VERTICES;
	/* the new point will be at halfway between the chosen vertix and the last point created */
	struct Point point = half_way(&vertices[i], last_point);

	/* The iterations count starts at -3 because I don't want to visualize the first 3 points.
	 * This because the first one might occupy a position in the canvas that would otherwise
	 * be empty. So I wait for the points to be aligned before printing any of them.
	 * Usually after the first 2 or 3 points it is safe to display them. */
	if (iterations > 0)
		points[num_points++] = point;

	iterations++;
	next_point(vertices, points, num_points, &point);
}



/* calculates the middle point between 2 points */
struct Point half_way(const struct Point *a, const struct Point *b) {
	unsigned int x = (a->x + b->x) / 2;
	unsigned int y = (a->y + b->y) / 2;
	struct Point point = {.x=x, .y=y};
	return point;
}



/* checks wether the 2 given points have the same coordinates */
bool same_coordinates(const struct Point *a, const struct Point *b) {
	return (a->x == b->x && a->y == b->y);
}



/* given the file path, the points array and the dimension of the latter, it stores all the points in the file */
void write_points_to_file(const char *file_path, const struct Point *points, unsigned int num_points) {
	FILE *file = open_file(file_path, "w");
	for (unsigned short int i = 0; i < num_points; i++)
		fprintf(file, "%d\n%d\n", points[i].x, points[i].y);
	fclose(file);
}



/* opens a file and checks if it exists. */
FILE *open_file(const char *path, const char *mode) {
	FILE *file = fopen(path, mode);
	if (file == NULL) {
		fprintf(stdout, "Error in handling file \"%s\".\n", path);
		exit (EXIT_FAILURE);
	}
	return file;
}



/* calls the python script to draw the simulation */
void draw(void) {
	char python_command[60];
	sprintf(python_command, "python3 ./draw_points.py %d %d %d", CANVAS_WIDTH, CANVAS_HEIGHT, NUM_POINTS);
	system(python_command);
}
