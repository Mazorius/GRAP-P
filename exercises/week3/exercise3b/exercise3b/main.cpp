//
//  main.cpp
//  exercise3b
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
#include "SOIL.h"

GLfloat vertices[][3] = {
	{-1.0,-1.0,-1.0},
	{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0},
	{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},
	{1.0,-1.0,1.0},
	{1.0,1.0,1.0},
	{-1.0,1.0,1.0}
};

GLfloat colors[][3] = {
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,1.0,0.0},
	{0.0,1.0,1.0},
	{1.0,0.0,1.0}
};

GLuint texture[2];

int loadGLTextures() {
	texture[0] = SOIL_load_OGL_texture("/Users/ron/Desktop/Semester 9 (SoFa)/grap/exercises/week3/exercise3b/exercise3b/tex1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[1] = SOIL_load_OGL_texture("/Users/ron/Desktop/Semester 9 (SoFa)/grap/exercises/week3/exercise3b/exercise3b/tex2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	
	if (texture[0] == 0 || texture[1] == 0) {
		return false;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	
	return true;
}

void polygon(int a, int b, int c , int d)
{
	/* draw a polygon via list of vertices */
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex3fv(vertices[a]);
		glTexCoord2f(0, 1);
		glVertex3fv(vertices[b]);
		glTexCoord2f(1, 1);
		glVertex3fv(vertices[c]);
		glTexCoord2f(1, 0);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{
	
	/* map vertices to faces */
	glColor3fv(colors[0]);
	polygon(0,3,2,1);
	glColor3fv(colors[1]);
	polygon(2,3,7,6);
	glColor3fv(colors[2]);
	polygon(3,0,4,7);
	glColor3fv(colors[3]);
	polygon(1,2,6,5);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3fv(colors[4]);
	polygon(4,5,6,7);
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3fv(colors[5]);
	polygon(5,4,0,1);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

void display(void)
{
	/* display callback, clear frame buffer and z buffer,
	 rotate cube and draw, swap buffers */
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	
	colorcube();
	
	glFlush();
	glutSwapBuffers();
}

void spinCube()
{
	
	/* Idle callback, spin cube 2 degrees about selected axis */
	
	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	
	/* mouse callback, selects an axis about which to rotate */
	
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
				2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
				2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	
	/* need both double buffering and z buffer */
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
	loadGLTextures();
	glutMainLoop();
}