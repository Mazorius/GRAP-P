//
//  main.cpp
//  exercise3a
//
//  Created by Ron Gebauer on 23.9.15.
//  Copyright © 2015 Ron Gebauer. All rights reserved.
//

#include <iostream>
#include <openGL/gl.h>
#include <openGL/glu.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#define CHECKER_SIZE 128
GLubyte check[(CHECKER_SIZE * CHECKER_SIZE) / 8];

void makeCheckerBoard()
{
	GLubyte wb[2]={0x00, 0xFF};
 
	for (int i = 0; i < CHECKER_SIZE; i++)
		for (int j = 0; j < CHECKER_SIZE; j++)
			check[i * 8 + j] = wb[(i / 8 + j) % 2];
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	glClearColor(0, 0, 0, 0);       // set black background color
	
	GLfloat pos = 100;
	
	glRasterPos3f(pos, pos, 0);
	glColor3f(1, 0, 0);
	glBitmap(CHECKER_SIZE, CHECKER_SIZE, 0, 0, 4, 4, check);
	
	glRasterPos3f(pos + 4, pos + 4, 0);
	glColor3f(0, 1, 0);
	glBitmap(CHECKER_SIZE, CHECKER_SIZE, 0, 0, 0, 0, check);

	glRasterPos3f(pos * 2, pos * 2, 0);
	glCopyPixels(pos, pos, CHECKER_SIZE, CHECKER_SIZE, GL_COLOR);

	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // set display mode
	glutInitWindowSize(400, 300);     // set window size
	glutInitWindowPosition(320, 240); // set window position on screen
	glutCreateWindow("Checkerboard"); // open the screen window
	glutDisplayFunc(display);     // register redraw function
	glutReshapeFunc(reshape);
	makeCheckerBoard();
	glutMainLoop();              // go into a perpetual loop
}