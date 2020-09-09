import turtle
import sys


VERTICES_FILE = ".vertices"
POINTS_FILE = ".points"
WIDTH = int(sys.argv[1])
HEIGHT = int(sys.argv[2])
NUM_POINTS = int(sys.argv[3])
NUM_VERTICES = 3

# change these colors
COLOR_WINDOW = "black"
COLOR_TEXT = "white"
COLOR_POINTS = "white"
COLOR_VERTICES = "green"
# change these parameters
SHAPE = "circle"
POINT_SIZE = 0.20
VERTIX_SIZE = 1


# WINDOW
window = turtle.Screen()
window.bgcolor(COLOR_WINDOW)
window.setup(WIDTH, HEIGHT)

# ITERATIONS COUNTER TEXT
point_tx = turtle.Turtle()
point_tx.penup()
point_tx.speed(0)
point_tx.hideturtle()
point_tx.color(COLOR_TEXT)
point_tx.setposition(-WIDTH/2 + 16, HEIGHT/2 - 58)
point_tx.write("points: 0", align='left', font=('Arial', 12, 'italic'))

# DOT TURTLE
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
	
	

def update_counter(value):
		point_txt = "points: {}".format(value)
		point_tx.undo()
		point_tx.write(point_txt, align='left', font=('Arial', 12, 'italic'))



def draw(source_file, total_num, color, size, counter):
	X = []
	Y = []
	read_coordinates_from_file(source_file, total_num, X, Y)
	d.color(color)
	d.shapesize(size)
	for i in range(total_num):
		d.goto(int(X[i]), int(Y[i]))
		d.stamp()
		if (counter):
			update_counter(i+1)



if __name__ == '__main__':
	print("drawing vertices")
	draw(VERTICES_FILE, NUM_VERTICES, COLOR_VERTICES, VERTIX_SIZE, False)
	print("drawing points")
	draw(POINTS_FILE, NUM_POINTS, COLOR_POINTS, POINT_SIZE, True)
	print("done")
	window.mainloop()
