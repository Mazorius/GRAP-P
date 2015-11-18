//
//  main.cpp
//  exercise2.1
//
//  Created by Ron Gebauer on 2.9.15.
//  Copyright (c) 2015 Ron Gebauer. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif


int x = 50;
int y = 25;
int width = 500;
int height = 500;
GLfloat vertices[] = {
	-0.5, -0.5,
	0.25, 0.25,
	0.5, 0.0,
	0.5, 0.25,
	0.0, 0.4,
	-0.15, 0.25,
	-0.25, 0.5
};

void draw(void) {
	//Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 14; i = i + 2) {
		glVertex2f(vertices[i], vertices[i + 1]);
	}
	
	glEnd();
	
	glFlush();
}

void resize(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	if (newWidth <= newHeight) {
		gluOrtho2D(-1.0, 1.0, -1.0 * newHeight / newWidth, 1.0 * newHeight / newWidth);
	} else {
		gluOrtho2D(-1.0 * newWidth / newHeight, 1.0 * newWidth / newHeight, -1.0, 1.0);
	}
	
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	//Command line commandos will be initiate
	glutInit(&argc, argv);
	
	/*
	 Setting up the display
	 RGB color model + Alpha channel = GLUT_RGBA
	 Single buffered window GLUT_SINGLE
	*/
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	
	//Configure window position and size
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	
	//Create window and set window name
	glutCreateWindow("Hello openGL");
	
	glutReshapeFunc(resize);
	
	//Call the drawing function
	glutDisplayFunc(draw);

	glutMainLoop();
	
    return 0;
}