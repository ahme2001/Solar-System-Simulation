#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <cstdint>  // for uintptr_t

// Globals.
static int width, height; // Size of the OpenGL window.
std::vector<glm::vec3> points = {
glm::vec3(0.0, 0.0, 0.0),  // sun
glm::vec3(0.0, 0.0, 14.0), // mercury
glm::vec3(0.0, 0.0, 23.0),  // venus
glm::vec3(0.0, 0.0, 35.0), // earth
glm::vec3(0.0, 10.0, 35.0), // moon
glm::vec3(0.0, 0.0, 45.0),  // mars
glm::vec3(0.0, 0.0, 58.0), // jupiter
glm::vec3(0.0, 0.0, 75.0),  // saturn
glm::vec3(0.0, 0.0, 90.0), // uranus
glm::vec3(0.0, 0.0, 105.0)  // neptune
};
std::vector<float> sizePlanet = {1.8,0.4,1.0,1.0,0.25,0.5,1.4,1.2,1.1,1.08};
static int radius = 6;
static unsigned int sphere;
static float latAngle = 0.0; // Latitudinal angle.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.

// Initialization routine.
void setup(void)
{
    glEnable(GL_DEPTH_TEST);
	// Initialize global arrayAsteroids.
    sphere = glGenLists(2);
    glNewList(sphere,GL_COMPILE);
    glutSolidSphere(radius, 50, 60);
    glEndList();

	glClearColor(0.0, 0.0, 0.0, 0.0);

}

void drawingSystem(void){
    // sun
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(points[0].x,points[0].y,points[0].z);
    glScalef(sizePlanet[0],sizePlanet[0],sizePlanet[0]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mercury
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
	glRotatef(latAngle, 0.0, 1.0, 0.0);
    glTranslatef(points[1].x,points[1].y,points[1].z);
    glScalef(sizePlanet[1],sizePlanet[1],sizePlanet[1]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // venus
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
	glRotatef(latAngle*0.9, 0.0, 1.0, 0.0);
    glTranslatef(points[2].x,points[2].y,points[2].z);
    glScalef(sizePlanet[2],sizePlanet[2],sizePlanet[2]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // earth
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.8, 0.0, 1.0, 0.0);
    glTranslatef(points[3].x,points[3].y,points[3].z);
    glScalef(sizePlanet[3],sizePlanet[3],sizePlanet[3]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // moon
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
	glRotatef(latAngle*0.8, 0.0, 1.0, 0.0);
	glRotatef(40*latAngle, 0.0, 0.0, 1.0);
	glTranslatef(points[4].x,points[4].y,points[4].z);
    glScalef(sizePlanet[4],sizePlanet[4],sizePlanet[4]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mars
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(latAngle*0.7, 0.0, 1.0, 0.0);
    glTranslatef(points[5].x,points[5].y,points[5].z);
    glScalef(sizePlanet[5],sizePlanet[5],sizePlanet[5]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Jupiter
    glColor3f( 0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glRotatef(latAngle*0.6, 0.0, 1.0, 0.0);
    glTranslatef(points[6].x,points[6].y,points[6].z);
    glScalef(sizePlanet[6],sizePlanet[6],sizePlanet[6]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Saturn
    glColor3f(0.9f, 0.7f, 0.2f);
    glPushMatrix();
    glRotatef(latAngle*0.5, 0.0, 1.0, 0.0);
    glTranslatef(points[7].x,points[7].y,points[7].z);
    glScalef(sizePlanet[7],sizePlanet[7],sizePlanet[7]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Uranus
    glColor3f( 0.6f, 0.8f, 0.9f);
    glPushMatrix();
    glRotatef(latAngle*0.4, 0.0, 1.0, 0.0);
    glTranslatef(points[8].x,points[8].y,points[8].z);
    glScalef(sizePlanet[8],sizePlanet[8],sizePlanet[8]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Neptune
    glColor3f( 0.2f, 0.4f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.3, 0.0, 1.0, 0.0);
    glTranslatef(points[9].x,points[9].y,points[9].z);
    glScalef(sizePlanet[9],sizePlanet[9],sizePlanet[9]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Begin right viewport.
	glViewport(0, 0, width , height);
	glLoadIdentity();

    // Fixed camera.
    gluLookAt(0.0, 0.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Draw all the asteroids in arrayAsteroids.
    drawingSystem();
	// End right viewport.

	// Beg	in left viewport.
    glViewport(3.0 * width / 4.0, 0, width / 3.0, height/3.0);
    glLoadIdentity();

    // Fixed camera.
    gluLookAt(0.0, 200.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0);

    // Draw solar systems using sphere list.
    drawingSystem();
	// End left viewport.

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
	glMatrixMode(GL_MODELVIEW);

	// Pass the size of the OpenGL window.
	width = w;
	height = h;
}
// Timer function.
void animate(int value)
{
	if (isAnimate)
	{
		latAngle += 5.0;

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
    case ' ':
		if (isAnimate) isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	// Compute next position.
	if (key == GLUT_KEY_LEFT)
	if (key == GLUT_KEY_RIGHT)
	if (key == GLUT_KEY_UP)
	if (key == GLUT_KEY_DOWN)

	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the left/right arrow keys to turn the craft." << std::endl
		<< "Press the up/down arrow keys to move the craft." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1500, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("spaceTravel.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

