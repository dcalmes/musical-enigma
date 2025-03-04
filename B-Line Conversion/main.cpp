// FILE NAME : Bezier
// DESCRIPTION : This program will draw a bezier curve based on 4 mouse inputs
//			it will allow you to move the curve using keyboard inputs
// DATE : November 2017
// WRITTEN BY: Douglas G Calmes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "glut.h"
#include "cs_graphics_setup.h"
#include <algorithm>
#include <iostream>

// Set up display window variables
#define WINDOW_XS 400
#define WINDOW_YS 500
#define WINDOW_NAME "Interactive Spline"

typedef struct pt
{
	GLint x, y;
	void setcoords(float newX, float newY) {
		x = newX;
		y = newY;
	}
}MyPoint;

// Prototype Functions
void display_func();
void createBoundaryPoint(int, int);
void drawLine(MyPoint, MyPoint);
void mouse(int, int, int, int);
void keyboard_func(unsigned char, int, int);
void print_func(int, int, float, float, float, void*, char*);
void draw_text_func();
void draw_button();
void draw_axes();
int factorial(int);
float binomialCof(float, float);
MyPoint Bezier(MyPoint[], double);
void drawCurve();
void boundary();


// Global Variables
MyPoint start_button;
MyPoint reset_button;
MyPoint firstPoint;
MyPoint secondPoint;
MyPoint boundaryPoints[4];
MyPoint beginingPoints[4];
int vertexCounter = 0;
int width = 0, height= 0;
int points = 0;
int mouseInput = 4;
int start = 0;
int reset = 0;
int angle = 0;
int rotate = 0;

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	init_setup(WINDOW_XS, WINDOW_YS, WINDOW_NAME);

	// center points of draw and reset button
	start_button.x = 360;
	start_button.y = 20;
	reset_button.x = 40;
	reset_button.y = 20;

	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 1;
}
// this function calls all the drawing functions to produce output on screen
void display_func() {
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(0, 400);
	glVertex2i(400, 400);
	glEnd();

	draw_button();
	draw_axes();

	// this is called when the user clicks the draw button at any time
	if (start == 1) {
		boundary();
		drawCurve();
	}

	if (reset == 1) {
		points = 0;
		for (int i = 0; i < mouseInput; i++) {
			boundaryPoints[i].y = -5;
			boundaryPoints[i].x = -5;
			glutPostRedisplay();
		}
	}
	
	reset = 0;
	draw_text_func();

	glFlush();
}
// This will create a boundary point based on the x and y coordinates of mouse input
void createBoundaryPoint(int x, int y) {
	glColor3f(1.0, 2.0, 0.1);
	// Set boundary point limits
	int pointHeight = 2;
	int pointWidth = 2;
	// Create boundary point based on x and y input from mouse
	glBegin(GL_POINTS);
	for (height = -pointHeight; height <= pointHeight; height++) {
		for (width = -pointWidth; width <= pointWidth; width++) {
			glVertex2i(x + width, y + height);
		}
	}
	glEnd();
	glFlush();
}
// This is a basic line drawing function for whenever lines need to be drawn
void drawLine(MyPoint p1, MyPoint p2) {
	// Draw line based on two inputs (x and y)
	glBegin(GL_LINE_LOOP);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}
// This function gets user input from the mouse to produce the graph generated by the program
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && points != mouseInput && reset == 0) {
		beginingPoints[points].setcoords((float)x, (float)(500 - y));
		boundaryPoints[points].setcoords((float)x, (float)(500 - y));
		points++;
	}

	// reset drawing if right mouse clicks on reset button
	// currently ends program
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// condition is confirmed if button is clicked
		if ((x <= reset_button.x + 35 && x >= reset_button.x - 35) && (y <= 495 && y >= 465)) {
			reset = 1;
		}
	}

	// Only draw curve if the start button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && points == mouseInput) {
		// condition is confirmed if button is clicked
		if ((x <= start_button.x + 35 && x >= start_button.x - 35) && (y <= 495 && y >= 465)) {
			start = 1;
			glutPostRedisplay();
		}
	}
}
// This funciton takes user input from the keyboard to edit the graph and exit the program
void keyboard_func(unsigned char c, int x, int y) {
	int temp = 0;
	switch (c)
	{
	case 'Q':
	case 'q':
		exit(0);
	}
	// Move graph based on user input
	if (c == 'Y') {
		for (int i = 0; i < mouseInput; i++) {
			boundaryPoints[i].y += 10;
		}
	}
	if (c == 'y') {
		for (int i = 0; i < mouseInput; i++) {
			boundaryPoints[i].y -= 10;
		}
	}
	if (c == 'X') {
		for (int i = 0; i < mouseInput; i++) {
			boundaryPoints[i].x -= 10;
		}
	}
	if (c == 'x') {
		for (int i = 0; i < mouseInput; i++) {
			boundaryPoints[i].x += 10;
		}
	}
	if (c == 'S') {
		for (int i = 0; i < mouseInput; i++) {
			glColor3f(3.0, 0.0, 0.0);
			boundaryPoints[i].x = beginingPoints[i].x;
			boundaryPoints[i].y = beginingPoints[i].y;
		}
	}
}
// This function will print out text on the screen
void print_func(int x, int y, float r, float g, float b, void* font, char *string) {
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int numCharacters;

	numCharacters = (int)strlen(string); // Set length of the string to numCharacters

	// Run a loop to read in each character of the string until there is no more characters left
	for (int currentCharacter = 0; currentCharacter < numCharacters; currentCharacter++) {
		glutBitmapCharacter(font, string[currentCharacter]);
	}
}
// This function is used to pass into the print function to print out the text given
void draw_text_func() {
	print_func(20, 430, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "PLEASE PRESS THE DRAW BUTTON AFTER YOU RESET THE DRAWING");
	print_func(75, 415, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "IN ORDER TO BEGIN DRAWING A NEW CURVE");
	print_func(75, 450, 0, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Douglas Gerard Calmes");
	print_func(345, 17, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "BEGIN");
	print_func(22, 17, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "RESET");
	print_func(205, 390, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "y");
	print_func(390, 205, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "x");
	print_func(205, 205, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "origin");
}
// This function will draw the draw and reset buttons
void draw_button() {
	//-------------------------Draw back target
	// Uses the height, width, and midpoints to create object
	glColor3f(0.0, 1.0, 0.0);
	int startButtonHeight = 15;
	int startButtonWidth = 35;
	glBegin(GL_POINTS);
	for (height = -startButtonHeight; height <= startButtonHeight; height++) {
		for (width = -startButtonWidth; width <= startButtonWidth; width++) {
			glVertex2i(start_button.x + width, start_button.y + height);
		}
	}
	glEnd();
	//-----------------------Draw front target
	// Uses the height, width, and midpoints to create object

	glColor3f(1.0, 0.0, 0.0);
	int resetButtonHeight = 15;
	int resetButtonWidth = 35;
	glBegin(GL_POINTS);
	for (height = -resetButtonHeight; height <= resetButtonHeight; height++) {
		for (width = -resetButtonWidth; width <= resetButtonWidth; width++) {
			glVertex2i(reset_button.x + width, reset_button.y + height);
		}
	}
	glEnd();
}
// This funciton will draw the axes on the screen
void draw_axes() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(200, 0);
	glVertex2i(200, 400);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(0, 200);
	glVertex2i(400, 200);
	glEnd();
}
// Basic factorial function used for graphing
int factorial(int i)
{
	if (i <= 1) {
		return(1);
	}
	else {
		i = i*factorial(i - 1);
	}
	return i;
}
// Basic binomial coff function used for graphing
float binomialCof(float i, float j)
{
	float result;
	result = factorial(i) / (factorial(j)*factorial(i - j));
	return result;
}
// This function will generate the bezier curve
MyPoint Bezier(MyPoint boundaryPoint[], double t) {
	MyPoint Point;
	Point.x = 0; Point.y = 0;
	for (int i = 0; i<mouseInput; i++){
		Point.x = Point.x + binomialCof((float)(mouseInput - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (mouseInput - 1 - i)) * boundaryPoint[i].x;
		Point.y = Point.y + binomialCof((float)(mouseInput - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (mouseInput - 1 - i)) * boundaryPoint[i].y;
	}
	return Point;
}
// This function will draw curve and boarder
void drawCurve() {
	int input = 0;
	// Create Boundary Line Based on mouse input
	if (points == mouseInput) {
		glColor3f(1.0, 0.4, 0.4);
		for (input = 0; input < mouseInput - 1; input++)
			drawLine(boundaryPoints[input], boundaryPoints[input + 1]);
		if (input = 3) {
			glColor3f(1.0, 1.0, 1.0);
			drawLine(boundaryPoints[input], boundaryPoints[input - 3]);
		}
	}
	firstPoint = boundaryPoints[0];
	// create curve startin with first boundary point
	glColor3f(0.0, 1.0, 0.4);
	for (double t = 0.0; t <= 1.0; t += 0.09) {
		// generates second point based on bezier curve function
		secondPoint = Bezier(boundaryPoints, t);
		// draws line between the two points
		drawLine(firstPoint, secondPoint);
		// continue curve by making fist point equal to second point
		firstPoint = secondPoint;
	}
}
// This function store boundary
void boundary() {
	createBoundaryPoint(boundaryPoints[0].x, boundaryPoints[0].y);
	createBoundaryPoint(boundaryPoints[1].x, boundaryPoints[1].y);
	createBoundaryPoint(boundaryPoints[2].x, boundaryPoints[2].y);
	createBoundaryPoint(boundaryPoints[3].x, boundaryPoints[3].y);
}