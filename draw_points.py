import turtle
import sys


VERTICES_FILE = ".vertices.txt"
POINTS_FILE = ".points.txt"
WIDTH = int(sys.argv[1]);
HEIGHT = int(sys.argv[2]);
NUM_VERTICES = int(sys.argv[3])
NUM_POINTS = int(sys.argv[4])

# change these colors if you want
COLOR_WINDOW = "black"
COLOR_TEXT = "white"
COLOR_DOTS = "white"
COLOR_VERTICES = "green"
# change these parameters if you want, its just aesthetic
SHAPE = "circle"
SHAPESIZE = 0.15
VERTIX_SIZE = 0.5

X = []
Y = []



# WINDOW
window = turtle.Screen()
window.bgcolor("black")
window.setup(WIDTH, HEIGHT)

# POINTS COUNTER
point_tx = turtle.Turtle()
point_tx.penup()
point_tx.speed(0)
point_tx.hideturtle()
point_tx.color(COLOR_TEXT)
point_tx.setposition(-WIDTH/2 + 16, HEIGHT/2 - 58)
point_tx.write("points 0", align='left', font=('Arial', 12, 'italic'))

# DOT
d = turtle.Turtle()
d.penup()
d.shape(SHAPE)
d.hideturtle()
d.speed(0)



def read_coordinates_from_file(filename, num, xlist, ylist):
	file = open(filename, "r")
	lines_in_file = file.readlines()
	for i in range(0, num*2):
		if (i % 2 == 0):
			xlist.append(lines_in_file[i])
		else:
			ylist.append(lines_in_file[i])
	file.close()


def draw_points():
	d.color(COLOR_DOTS)
	d.shapesize(SHAPESIZE)
	read_coordinates_from_file(POINTS_FILE, NUM_POINTS, X, Y)
	for i in range(NUM_POINTS):
		d.goto(int(X[i]), int(Y[i]))
		d.stamp()
		point_txt = "iterations {}".format(i+1)
		point_tx.undo()
		point_tx.write(point_txt, align='left', font=('Arial', 12, 'italic'))


def draw_vertices():
	d.color(COLOR_VERTICES)
	d.shapesize(VERTIX_SIZE)
	read_coordinates_from_file(VERTICES_FILE, NUM_VERTICES, X, Y)
	for i in range(NUM_VERTICES):
		print("printing vertix")
		d.goto(int(X[i]), int(Y[i]))
		d.stamp()


if __name__ == '__main__':
	draw_vertices()
	draw_points()
	window.mainloop()
