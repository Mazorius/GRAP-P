//
//  main.cpp
//  exercise3.3
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
	-0.5, -0.5, 0.0,
	-0.5, 0.5, 0.0,
	0.5, 0.5, 0.0,
	0.5, -0.5, 0.0
};

GLfloat colors[] = {
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 0.0, 1.0
};

GLfloat lineWidth = 1.0;

GLint drawMode = GL_QUADS;
bool drawDiagionals = true;
bool drawStipped = false;

void draw(void) {
	//Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (drawStipped) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00FF);
		glLineWidth(lineWidth);
	}
	
	glBegin(drawMode);
	for (int i = 0; i < 12; i = i + 3) {
		glColor3f(colors[i], colors[i+1], colors[i+2]);
		glVertex3f(vertices[i], vertices[i + 1], vertices[i+2]);
	}
	glEnd();
	
	if (drawDiagionals) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00FF);
		glLineWidth(lineWidth);
		
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(vertices[0], vertices[1], vertices[2]);
		glVertex3f(vertices[6], vertices[7], vertices[8]);

		glVertex3f(vertices[3], vertices[4], vertices[5]);
		glVertex3f(vertices[9], vertices[10], vertices[11]);
		glEnd();
		
		glDisable(GL_LINE_STIPPLE);
	}
	
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

void menu(int value) {
	if (value == 1) {
		drawDiagionals = !drawDiagionals;
		glutPostRedisplay();
	}
}

void changeFill(int value) {
	if (value == 1) {
		drawMode = GL_QUADS;
		drawStipped = false;
	} else {
		drawMode = GL_LINE_LOOP;
		drawStipped = value != 3 ? false : true;
	}
	
	glutPostRedisplay();
}

void changeLineWidth(int value) {
	if (value == 1) {
		lineWidth = 1.0;
	} else {
		lineWidth = 2.0;
	}
	
	glutPostRedisplay();
}

static int lineWidthMenu;
static int fillMenu;
static int contextMenu;

void createMenu(void) {
	lineWidthMenu = glutCreateMenu(changeLineWidth);
	glutAddMenuEntry("Width 1", 1);
	glutAddMenuEntry("Width 2", 2);

	fillMenu = glutCreateMenu(changeFill);
	glutAddMenuEntry("Filled", 1);
	glutAddMenuEntry("Outline", 2);
	glutAddMenuEntry("Stipple Outline", 3);
	
	contextMenu = glutCreateMenu(menu);
	glutAddSubMenu("Line Width", lineWidthMenu);
	glutAddSubMenu("Fill Menu", fillMenu);
	glutAddMenuEntry("Toggle Diagonials", 1);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	createMenu();
	
	glutReshapeFunc(resize);
	
	//Call the drawing function
	glutDisplayFunc(draw);
	
	glutMainLoop();
	
	return 0;
}