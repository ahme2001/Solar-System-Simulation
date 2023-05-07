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
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 130; // Co-ordinates of the spacecraft.
static unsigned int spacecraft; // Display lists base index.

// Initialization routine.
void setup(void)
{
    glEnable(GL_DEPTH_TEST);
	// Initialize global arrayAsteroids.
	spacecraft = glGenLists(1);
	glNewList(spacecraft, GL_COMPILE);
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
	glColor3f(1.0, 1.0, 1.0);
	glutWireCone(5.0, 10.0, 10, 10);
	glPopMatrix();
	glEndList();

    sphere = glGenLists(2);
    glNewList(sphere,GL_COMPILE);
    glutSolidSphere(radius, 50, 60);
    glEndList();

	glClearColor(0.0, 0.0, 0.0, 0.0);

	 // Enable lighting and specify light properties.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {points[0].x, points[0].y, points[0].z, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


    GLfloat planet_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat planet_shininess[] = {50.0};
    // Specify material properties.
    glMaterialfv(GL_FRONT, GL_SPECULAR, planet_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, planet_shininess);

}

void drawingSystem(void){
    // sun
    glColor3f(1.0, 1.0, 0.0);
    GLfloat sun_ambient[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat sun_diffuse[] = {1.0, 1.0, 0.0, 1.0}; // Change this line
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    glPushMatrix();
    glTranslatef(points[0].x,points[0].y,points[0].z);
    glScalef(sizePlanet[0],sizePlanet[0],sizePlanet[0]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mercury
    //glColor3f(0.8f, 0.8f, 0.8f);
    GLfloat mercury_ambient[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mercury_diffuse[] = {0.2, 0.2, 0.2, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mercury_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mercury_diffuse);
    glPushMatrix();
	glRotatef(latAngle, 0.0, 1.0, 0.0);
    glTranslatef(points[1].x,points[1].y,points[1].z);
    glScalef(sizePlanet[1],sizePlanet[1],sizePlanet[1]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // venus
    //glColor3f(1.0f, 0.5f, 0.0f);
    GLfloat venus_ambient[] = {0.0, 0.5, 1.0, 1.0};
    GLfloat venus_diffuse[] = {1.0f, 0.5f, 0.0f, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, venus_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, venus_diffuse);
    glPushMatrix();
	glRotatef(latAngle*0.9, 0.0, 1.0, 0.0);
    glTranslatef(points[2].x,points[2].y,points[2].z);
    glScalef(sizePlanet[2],sizePlanet[2],sizePlanet[2]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // earth
    //glColor3f(0.0f, 0.0f, 1.0f);
    GLfloat earth_ambient[] = {1.0, 1.0 , 0.0, 1.0};
    GLfloat earth_diffuse[] = {0.0f, 0.0f, 1.0f, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_diffuse);
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
    //glColor3f(1.0f, 0.0f, 0.0f);
    GLfloat mars_ambient[] = {0.0, 1.0, 1.0, 0.5};
    GLfloat mars_diffuse[] = {1.0f, 0.0f, 0.0f, 0.5};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mars_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mars_diffuse);
    glPushMatrix();
    glRotatef(latAngle*0.7, 0.0, 1.0, 0.0);
    glTranslatef(points[5].x,points[5].y,points[5].z);
    glScalef(sizePlanet[5],sizePlanet[5],sizePlanet[5]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Jupiter
    //glColor3f(0.8f, 0.6f, 0.3f);
    GLfloat Jupiter_ambient[] = {0.2, 0.4, 0.7, 1.0};
    GLfloat Jupiter_diffuse[] = {0.8f, 0.6f, 0.3f, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, Jupiter_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Jupiter_diffuse);
    glPushMatrix();
    glRotatef(latAngle*0.6, 0.0, 1.0, 0.0);
    glTranslatef(points[6].x,points[6].y,points[6].z);
    glScalef(sizePlanet[6],sizePlanet[6],sizePlanet[6]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Saturn
    //glColor3f(0.9f, 0.7f, 0.2f);
    GLfloat Saturn_ambient[] = {0.1, 0.3, 0.8, 1.0};
    GLfloat Saturn_diffuse[] = {0.9f, 0.7f, 0.2f, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, Saturn_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Saturn_diffuse);
    glPushMatrix();
    glRotatef(latAngle*0.5, 0.0, 1.0, 0.0);
    glTranslatef(points[7].x,points[7].y,points[7].z);
    glScalef(sizePlanet[7],sizePlanet[7],sizePlanet[7]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Uranus
    //glColor3f( 0.6f, 0.8f, 0.9f);
    GLfloat Uranus_ambient[] = {0.4, 0.2, 0.1, 1.0};
    GLfloat Uranus_diffuse[] = {0.6f, 0.8f, 0.9f, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Uranus_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Uranus_diffuse);
    glPushMatrix();
    glRotatef(latAngle*0.4, 0.0, 1.0, 0.0);
    glTranslatef(points[8].x,points[8].y,points[8].z);
    glScalef(sizePlanet[8],sizePlanet[8],sizePlanet[8]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Neptune
    //glColor3f( 0.2f, 0.4f, 1.0f);
    GLfloat Neptune_ambient[] = {0.8, 0.6, 0.0, 1.0};
    GLfloat Neptune_diffuse[] = {0.2f, 0.4f, 1.0f, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, Neptune_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Neptune_diffuse);
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
    //gluLookAt(0.0, 0.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 10 * cos((M_PI / 180.0) * angle),
		xVal - 11 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 11 * cos((M_PI / 180.0) * angle),
		0.0,
		1.0,
		0.0);
	// Draw solar system.
    drawingSystem();

	// End space craft viewport.

	// Beg	in plane viewport.
    glViewport(3.0 * width / 4.0, 0, width / 3.0, height/3.0);
    glLoadIdentity();

    // separate two views
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5.0);
	// Draw vertical line.
    glBegin(GL_LINES);
    glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);
    glEnd();
    // Draw horizontal line.
    glBegin(GL_LINES);
	glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glEnd();
	glLineWidth(1.0);

    // Fixed camera.
    gluLookAt(0.0, 140.0, 150.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Draw spacecraft.
    glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(xVal, 0.0, zVal);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(spacecraft);
	glPopMatrix();
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
	float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

	// Compute next position.
	if (key == GLUT_KEY_LEFT) tempAngle = angle + 5.0;
	if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
	if (key == GLUT_KEY_UP)
	{
		tempxVal = xVal - sin(angle * M_PI / 180.0);
		tempzVal = zVal - cos(angle * M_PI / 180.0);
	}
	if (key == GLUT_KEY_DOWN)
	{
		tempxVal = xVal + sin(angle * M_PI / 180.0);
		tempzVal = zVal + cos(angle * M_PI / 180.0);
	}

	// Angle correction.
	if (tempAngle > 360.0) tempAngle -= 360.0;
	if (tempAngle < 0.0) tempAngle += 360.0;

	// Move spacecraft to next position only if there will not be collision with an asteroid.
	//if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
	//{
		xVal = tempxVal;
		zVal = tempzVal;
		angle = tempAngle;
	//}

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

