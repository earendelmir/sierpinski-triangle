import turtle
import sys


VERTICES_FILE = ".vertices"
POINTS_FILE = ".points"
WIDTH = int(sys.argv[1])
HEIGHT = int(sys.argv[2])
NUM_VERTICES = int(sys.argv[3])
NUM_POINTS = int(sys.argv[4])

# change these colors
COLOR_WINDOW = "black"
COLOR_TEXT = "white"
# change these parameters
VERTIX_COLOR = "green"
VERTIX_SHAPE = "square"
VERTIX_SIZE = 1
POINT_COLOR = "white"
POINT_SHAPE = "circle"
POINT_SIZE = 0.25


# WINDOW
window = turtle.Screen()
window.bgcolor(COLOR_WINDOW)
window.setup(WIDTH, HEIGHT)

# ITERATIONS COUNTER TEXT
counterTxt = turtle.Turtle()
counterTxt.penup()
counterTxt.speed(0)
counterTxt.hideturtle()
counterTxt.color(COLOR_TEXT)
counterTxt.setposition(-WIDTH/2 + 16, HEIGHT/2 - 58)
counterTxt.write("points: 0", align='left')

# DOT TURTLE
dot = turtle.Turtle()
dot.penup()
dot.hideturtle()
dot.speed(0)



def readCoordinates(filename, num, xList, yList):
    coordsFile = open(filename, "r")
    lines = coordsFile.readlines()
    for i in range(0, num*2):
        # X coordinates are stored in the even lines of the file
        if (i % 2 == 0):
            xList.append(int(lines[i]))
        # Y coordinates are stored in the odd lines of the file
        else:
            yList.append(int(lines[i]))
    coordsFile.close()



def updateCounter(value):
    text = "points: {}".format(value)
    counterTxt.undo()
    counterTxt.write(text, align='left', font=('Arial', 12, 'italic'))



def draw(sourceFile, total, color, shape, size, showCounter):
    X = []
    Y = []
    readCoordinates(sourceFile, total, X, Y)
    dot.color(color)
    dot.shape(shape)
    dot.shapesize(size)
    for i in range(total):
        dot.goto(X[i], Y[i])
        dot.stamp()
        if (showCounter):
            updateCounter(i+1)
    X.clear()
    Y.clear()



if __name__ == '__main__':
    print("Drawing the vertices...")
    draw(VERTICES_FILE, NUM_VERTICES, VERTIX_COLOR, VERTIX_SHAPE, VERTIX_SIZE, False)
    print("Drawing the points...")
    draw(POINTS_FILE, NUM_POINTS, POINT_COLOR, POINT_SHAPE, POINT_SIZE, True)

    # waits for the user to press a key before closing the window
    print("Done.\nPress ENTER to close the window...", end="")
    closingInput = input()
    exit(0)
