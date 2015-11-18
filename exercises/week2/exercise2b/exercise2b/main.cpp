//
//  main.cpp
//  exercise2b
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

GLfloat spin = 0.0;

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
	glClearDepth(25.0);                   // Set background depth to farthest
	
	/*
	 We need to enable depth-test to remove the hidden surface, and set the function used for the
	 depth test.
	 */
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glEnable(GL_LIGHT0);
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
 
	GLfloat position[] = {0.0f, 0.0f, 1.5f, 1.0f};
	GLfloat ambient[] = {2, 2, 2, 1};
	GLfloat diffuse[] = {2, 2, 2, 1};
	GLfloat specular[] = {0, 0, 0, 1};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glPushMatrix(); // ISOLATE OTHER RENDERING
	
		glPushMatrix(); // red push/pop pair: ISOLATE LIGHT FROM CUBE
		glRotatef(spin, 1.0, 0.0, 0.0);
		// this rotates light position (x-axis) and translated
		// wirecube, which visualizes the lightposition
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glTranslated(0.0, 0.0, 1.5);
		glDisable(GL_LIGHTING); //do not want to light the cube itself
		glColor3f(0.0, 1.0, 1.0);
		glutWireCube(0.1);
		glEnable(GL_LIGHTING);
		glPopMatrix(); // red push/pop pair
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		GLfloat frontAmbientBrass[4] = {0.329412, 0.223529, 0.027451, 1.0};
		GLfloat frontDiffuseBrass[4] = {0.780392, 0.568627, 0.113725, 1.0};
		GLfloat frontSpecularBrass[4] = {0.992157, 0.941176, 0.807843, 1.0};
		GLfloat frontShininessBrass = 0.21794872;
		glMaterialfv(GL_FRONT, GL_AMBIENT, frontAmbientBrass);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, frontDiffuseBrass);
		glMaterialfv(GL_FRONT, GL_SPECULAR, frontSpecularBrass);
		glMaterialf(GL_FRONT, GL_SHININESS, frontShininessBrass);
		glutSolidCone(0.5, 1.0, 100.0, 100.0);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, -2.0);
		GLfloat frontAmbientRed[4] = {0.0, 0.0, 0.0, 1.0};
		GLfloat frontDiffuseRed[4] = {0.5, 0.0, 0.0, 1.0};
		GLfloat frontSpecularRed[4] = {0.7, 0.6, 0.6, 1.0};
		GLfloat frontShininessRed = 0.25;
		glMaterialfv(GL_FRONT, GL_AMBIENT, frontAmbientRed);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, frontDiffuseRed);
		glMaterialfv(GL_FRONT, GL_SPECULAR, frontSpecularRed);
		glMaterialf(GL_FRONT, GL_SHININESS, frontShininessRed);
		glutSolidCone(0.5, 1.0, 100.0, 100.0);
		glPopMatrix();

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

void onClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			spin = spin + 15 % 360;
			glutPostRedisplay();
		}
	}
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
	
	glutMouseFunc(onClick);
	
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