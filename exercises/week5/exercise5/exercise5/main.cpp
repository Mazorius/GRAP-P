//
//  main.cpp
//  exercise5
//
//  Created by Ron Gebauer on 30.9.15.
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

GLint start;
bool isSelected = false;

void drawCurves(GLenum mode) {
	/* Draw the curves */
	glColor3f(0,0,0);
	for(int i=0; i<OUTER_CPTS-3; i +=3) {
		if (mode == GL_SELECT) {
			glLoadName(i);
		}
		/* Draw the outer curve using OpenGL evaluators */
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
		glMapGrid1f(30, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 30);
	}
	
	for(int i=0; i<INNER_CPTS-3; i +=3) {
		if (mode == GL_SELECT) {
			glLoadName(i+OUTER_CPTS);
		}
		/* Draw the inner curve using OpenGL evaluators */
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[OUTER_CPTS+i]);
		glMapGrid1f(30, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 30);
	}
	
	glFlush();
}

void drawPoints(void) {
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 4; i++)
		glVertex3fv(cpts[start + i]);
	glColor3f(0, 0, 0);
	glEnd();
}

/* This routine displays the control points */
static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (isSelected) {
		drawPoints();
	}
	
	drawCurves(GL_RENDER);
	glFlush();
}

void processHits (GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLint names, *ptr;
	
//	printf ("hits = %d\n", hits);
	ptr = (GLint *) buffer;
	for (i = 0; i < hits; i++) {	/*  for each hit  */
		names = *ptr;
		ptr+=3;	// skip over names and depth
		for (j = 0; j < names; j++) { /*  for each name */
			printf("%d ",*ptr);
			start = *ptr;
			ptr++;
		}
		printf ("\n");
	}
}

#define SIZE 512

// use the mouse call back to enter and leave the selection mode
void mouse(int button, int state, int x, int y)
{
	GLuint selectBuf[SIZE];
	GLint hits;
	GLint viewport[4];
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isSelected = true;
		glGetIntegerv (GL_VIEWPORT, viewport);
		
		glSelectBuffer (SIZE, selectBuf);
		glRenderMode(GL_SELECT);
		
		glInitNames(); // initialize the name stack
		glPushName(0); // with an unused name
		
		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		/*  create 5x5 pixel picking region near cursor location	*/
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
					   5.0, 5.0, viewport);
//		glOrtho(-2.0, 2.0, -2.0, 2.0,0.0,5.0); // same as in the render mode
		glViewport(0, 0, width, height);
		drawCurves(GL_SELECT); // direct call of the drawing function
		
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();
		
		hits = glRenderMode (GL_RENDER); // returns the number of hits
		processHits (hits, selectBuf);
	}
	else
	{
		isSelected = false;
	}
	
	glutPostRedisplay();
}

/* This routine handles window resizes */
void reshape(int w, int h)
{
	width = w;
	height = h;
	
	/* Set the transformations */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	if (w <= h) {
//		glOrtho(-1.0, 1.0, -1.0 * h / w, 1.0 * h / w,-1.0, 1.0);
//	} else {
//		glOrtho(-1.0 * w / h, 1.0 * w / h, -1.0, 1.0,-1.0, 1.0);
//	}
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
	glutMouseFunc(mouse);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glEnable(GL_MAP1_VERTEX_3);
	
	// determin gain
	for(int i=0;i<ncpts;i++){
		cpts[i][0]=(-16.0+cpts[i][0])/20.0;
		cpts[i][1]=(-16.0+cpts[i][1])/20.0;
		cpts[i][2]=cpts[i][2];
		//printf("\n %d %f %f",i,cpts[i][0],cpts[i][1]);
	}
	
	glutMainLoop();
}