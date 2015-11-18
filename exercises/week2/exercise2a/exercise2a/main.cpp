//
//  main.cpp
//  exercise2a
//
//  Created by Ron Gebauer on 9.9.15.
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


//Global variables
char title[] = "exercise2a";

int x = 50;
int y = 25;
int width = 640;
int height = 480;

void initGL() {
	/*
	 Set the clearing (background) color to black (R=0, G=0, B=0) and opaque (A=1), and the clearing
	 (background) depth to the farthest (Z=1). In display(), we invoke glClear() to clear the color
	 and depth buffer, with the clearing color and depth, before rendering the graphics. (Besides the
	 color buffer and depth buffer, OpenGL also maintains an accumulation buffer and a stencil buffer
	 which shall be discussed later.)
	*/
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	
	/*
	 We need to enable depth-test to remove the hidden surface, and set the function used for the
	 depth test.
	 */
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	
	/*
	 We enable smooth shading in color transition. The alternative is GL_FLAT. Try it out and see
	 the difference.
	 */
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	
	/*
	 In graphics rendering, there is often a trade-off between processing speed and visual quality.
	 We can use glHint() to decide on the trade-off. In this case, we ask for the best perspective
	 correction, which may involve more processing. The default is GL_DONT_CARE.
	 */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
	// Render a color-cube consisting of 6 quads with different colors
	//glLoadIdentity();                 // Reset the model-view matrix

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glutWireCube(0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1f, 1.1f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireTetrahedron();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.0f, 2.0f, 0.0f);
	glScalef(2.0f, 1.0f, 1.0f); // 2 a b
	glutWireCube(0.5f);
	glPopMatrix();
	
	glFlush();

	glutSwapBuffers();
}

void reshape(GLsizei newWidth, GLsizei newHeight) {
	// Compute aspect ratio of the new window
	if (newHeight == 0) newHeight = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)newWidth / (GLfloat)newHeight;
 
	// Set the viewport to cover the new window
	glViewport(0, 0, newWidth, newHeight);
 
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(50.0f, aspect, 1.0f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 4.5, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
	/*
	 Initializes the GLUT.
	 */
	glutInit(&argc, argv); // Initialize GLUT
	
	/*
	 Enables double buffering. In display(), we use glutSwapBuffers() to signal to the GPU to
	 swap the front-buffer and back-buffer during the next VSync (Vertical Synchronization).
	 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Enable double buffered mode, true colored, z-buffer
	
	/*
	 Creates a window with a title, initial width and height positioned at initial top-left corner.
	 */
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);        // Create window with the given title
	
	/*
	 Registers display() as the re-paint event handler. That is, the graphics sub-system calls
	 back display() when the window first appears and whenever there is a re-paint request.
	 */
	glutDisplayFunc(display); // Register callback handler for window re-paint event
	
	/*
	 Registers reshape() as the re-sized event handler. That is, the graphics sub-system calls
	 back reshape() when the window first appears and whenever the window is re-sized.
	 */
	glutReshapeFunc(reshape); // Register callback handler for window re-size event
	
	/*
	 Invokes the initGL() once to perform all one-time initialization tasks.
	 */
	initGL();  // Our own OpenGL initialization

	/*
	 Finally, enters the event-processing loop.
	 */
	glutMainLoop(); // Enter the infinite event-processing loop

	return 0;
}