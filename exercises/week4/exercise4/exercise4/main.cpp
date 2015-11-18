//
//  main.cpp
//  exercise4
//
//  Created by Ron Gebauer on 24.9.15.
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

//#include "letter_b.h"
//#include "letter_i.h"
#include "number_9.h"

int ncpts = OUTER_CPTS + INNER_CPTS;
//int ncpts = 0;

static int width = 500, height = 500;           /* Window width and height */

void drawCurves() {
	int 		i;
	GLfloat gain;
	
	/* Draw the curves */
	glColor3f(0,0,0);
	for(i=0; i<OUTER_CPTS-3; i +=3) {
		/* Draw the outer curve using OpenGL evaluators */
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
		glMapGrid1f(30, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 30);
	}
	
	for(i=0; i<INNER_CPTS-3; i +=3) {
		/* Draw the inner curve using OpenGL evaluators */
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[OUTER_CPTS+i]);
		glMapGrid1f(30, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 30);
	}
	
	glFlush();
	
	// determin gain
	for(i=0;i<ncpts;i++){
		cpts[i][0]=(-16.0+cpts[i][0])/20.0;
		cpts[i][1]=(-16.0+cpts[i][1])/20.0;
		cpts[i][2]=cpts[i][2];
		//printf("\n %d %f %f",i,cpts[i][0],cpts[i][1]);
	}
}

/* This routine displays the control points */
static void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POINTS);
	for (i = 0; i < ncpts; i++)
		glVertex3fv(cpts[i]);
	glEnd();
	
	drawCurves();
	glFlush();
}

/* This routine handles window resizes */
void reshape(int w, int h)
{
	width = w;
	height = h;
	
	/* Set the transformations */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
	/* Intialize the program */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("curves");
	
	/* Register the callbacks */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glEnable(GL_MAP1_VERTEX_3);
	
	glutMainLoop();
}