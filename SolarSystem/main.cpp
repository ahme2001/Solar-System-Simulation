#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <cstdint>  // for uintptr_t
#define ROWS 8  // Number of rows of asteroids.
#define COLUMNS 1 // Number of columns of asteroids.
#define FILL_PROBABILITY 100 // Percentage probability that a particular row-column slot will be
                             // filled with an asteroid. It should be an integer between 0 and 100.

// Globals.
static uintptr_t font = reinterpret_cast<uintptr_t>(GLUT_BITMAP_8_BY_13); // Font selection.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 0; // Co-ordinates of the spacecraft.
static int isCollision = 0; // Is there collision between the spacecraft and an asteroid?
static unsigned int spacecraft; // Display lists base index.
static int frameCount = 0; // Number of frames

std::vector<glm::vec3> points = {
glm::vec3(0.0, 5.0, -140.0),  // sun
glm::vec3(19.0, 5.0, -140.0), // mercury
glm::vec3(30.0, 5.0, -140.0),  // venus
glm::vec3(43.0, 5.0, -140.0), // earth
glm::vec3(40.0, 5.0, -190.0), // moon
glm::vec3(53.0, 5.0, -140.0),  // mars
glm::vec3(66.0, 5.0, -140.0), // jupiter
glm::vec3(85.0, 5.0, -140.0),  // saturn
glm::vec3(102.5, 5.0, -140.0), // uranus
glm::vec3(120.0, 5.0, -140.0)  // neptune
};
std::vector<float> sizePlanet = {1.8,0.4,1.0,1.0,0.25,0.5,1.4,1.2,1.1,1.08};
static int radius = 6;
static unsigned int sphere;
static float latAngle = 0.0; // Latitudinal angle.
static float longAngle = 0.0; // Longitudinal angle.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
   if (value != 0) // No output the first time frameCounter() is called (from main()).
	  std::cout << "FPS = " << frameCount << std::endl;
   frameCount = 0;
   glutTimerFunc(1000, frameCounter, 1);
}

int checkSpheresIntersection(float x1, float y1, float z1, float r1,
	float x2, float y2, float z2, float r2)
{
	return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2) <= (r1 + r2)*(r1 + r2));
}

// Function to check if the spacecraft collides with an asteroid when the center of the base
// of the craft is at (x, 0, z) and it is aligned at an angle a to to the -z direction.
// Collision detection is approximate as instead of the spacecraft we use a bounding sphere.
int asteroidCraftCollision(float x, float z, float a)
{
	int i, j;

	// Check for collision with each asteroid.
    for (i = 0; i<points.size(); i++)
            if (checkSpheresIntersection(x - 5 * sin((M_PI / 180.0) * a), 0.0,
                z - 5 * cos((M_PI / 180.0) * a), 7.072,
                points[i].x, points[i].y,
                points[i].z, sizePlanet[i]*radius))
                return 1;
	return 0;
}

// Initialization routine.
void setup(void)
{
	int i, j;

	spacecraft = glGenLists(1);
	glNewList(spacecraft, GL_COMPILE);
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
	glColor3f(1.0, 1.0, 1.0);
	glutWireCone(5.0, 10.0, 10, 10);
	glPopMatrix();
	glEndList();

	// Initialize global arrayAsteroids.
    sphere = glGenLists(2);
    glNewList(sphere,GL_COMPILE);
    glutWireSphere(radius, 50, 30);
    glEndList();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
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
	glRotatef(latAngle, 0.0, 0.0, 1.0);
    glTranslatef(points[1].x,points[1].y,points[1].z);
    glScalef(sizePlanet[1],sizePlanet[1],sizePlanet[1]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // venus
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
	glRotatef(latAngle*0.9, 0.0, 0.0, 1.0);
    glTranslatef(points[2].x,points[2].y,points[2].z);
    glScalef(sizePlanet[2],sizePlanet[2],sizePlanet[2]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // earth
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.8, 0.0, 0.0, 1.0);
    glTranslatef(points[3].x,points[3].y,points[3].z);
    glScalef(sizePlanet[3],sizePlanet[3],sizePlanet[3]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // moon
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
	//glRotatef(0.1 *longAngle, 0.0, 1.0, 0.0);
	glRotatef(4*longAngle, 0.0, 0.0, 1.0);
	glRotatef(40 *longAngle, 1.0, 0.0, 1.0);
	glTranslatef(points[4].x,points[4].y,points[4].z);
    glScalef(sizePlanet[4],sizePlanet[4],sizePlanet[4]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mars
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(latAngle*0.7, 0.0, 0.0, 1.0);
    glTranslatef(points[5].x,points[5].y,points[5].z);
    glScalef(sizePlanet[5],sizePlanet[5],sizePlanet[5]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Jupiter
    glColor3f( 0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glRotatef(latAngle*0.6, 0.0, 0.0, 1.0);
    glTranslatef(points[6].x,points[6].y,points[6].z);
    glScalef(sizePlanet[6],sizePlanet[6],sizePlanet[6]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Saturn
    glColor3f(0.9f, 0.7f, 0.2f);
    glPushMatrix();
    glRotatef(latAngle*0.5, 0.0, 0.0, 1.0);
    glTranslatef(points[7].x,points[7].y,points[7].z);
    glScalef(sizePlanet[7],sizePlanet[7],sizePlanet[7]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Uranus
    glColor3f( 0.6f, 0.8f, 0.9f);
    glPushMatrix();
    glRotatef(latAngle*0.4, 0.0, 0.0, 1.0);
    glTranslatef(points[8].x,points[8].y,points[8].z);
    glScalef(sizePlanet[8],sizePlanet[8],sizePlanet[8]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Neptune
    glColor3f( 0.2f, 0.4f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.3, 0.0, 0.0, 1.0);
    glTranslatef(points[9].x,points[9].y,points[9].z);
    glScalef(sizePlanet[9],sizePlanet[9],sizePlanet[9]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
   frameCount++; // Increment number of frames every redraw.

   int i, j;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Beg	in left viewport.
   glViewport(3.0 * width / 4.0, 0, width / 3.0, height/3.0);
   glLoadIdentity();

   // Write text in isolated (i.e., before gluLookAt) translate block.
   glPushMatrix();
   glColor3f(1.0, 0.0, 0.0);
   glRasterPos3f(-28.0, 25.0, -30.0);
   if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
   glPopMatrix();

   // Fixed camera.
   gluLookAt(0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Draw solar systems using sphere list.
    drawingSystem();

	// Draw spacecraft.
	glPushMatrix();
	glTranslatef(xVal, 0.0, zVal);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(spacecraft);
	glPopMatrix();
	// End left viewport.

	// Begin right viewport.
	glViewport(0, 0, width , height);//demo
	glLoadIdentity();

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-28.0, 25.0, -30.0);
	if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
	glPopMatrix();

	// Locate the camera at the tip of the cone and pointing in the direction of the cone.
	gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 10 * cos((M_PI / 180.0) * angle),
		xVal - 11 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 11 * cos((M_PI / 180.0) * angle),
		0.0,
		1.0,
		0.0);

	// Draw all the asteroids in arrayAsteroids.
    drawingSystem();
	// End right viewport.

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
		//if (latAngle > 360.0) latAngle -= 360.0;
		longAngle += 1.0;
		//if (longAngle > 360.0) longAngle -= 360.0;

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
	if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
	{
		isCollision = 0;
		xVal = tempxVal;
		zVal = tempzVal;
		angle = tempAngle;
	}
	else isCollision = 1;

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

