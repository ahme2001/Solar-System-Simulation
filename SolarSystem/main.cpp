#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
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
    glutSolidSphere(6, 50, 62);
    glEndList();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
}

void drawingSystem(void){
    // sun
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 5.0, -140.0);
    glScalef(1.8,1.8,1.8);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mercury
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
	glRotatef(latAngle, 0.0, 0.0, 1.0);
    glTranslatef(19.0, 5.0, -140.0);
    glScalef(0.4,0.4,0.4);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // venus
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
	glRotatef(latAngle*0.9, 0.0, 0.0, 1.0);
    glTranslatef(30.0, 5.0, -140.0);
    glScalef(1.0,1.0,1.0);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // moon
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
	glRotatef(1.1 * latAngle, 0.0, 0.0, 1.0);
    glTranslatef(43.0, 6.0, -140.0);
    glScalef(0.25,0.25,0.25);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // earth
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.8, 0.0, 0.0, 1.0);
    glTranslatef(43.0, 5.0, -140.0);
    glScalef(1.0,1.0,1.0);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // mars
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(latAngle*0.7, 0.0, 0.0, 1.0);
    glTranslatef(53.0, 5.0, -140.0);
    glScalef(0.5,0.5,0.5);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Jupiter
    glColor3f( 0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glRotatef(latAngle*0.6, 0.0, 0.0, 1.0);
    glTranslatef(66.0, 5.0, -140.0);
    glScalef(1.4,1.4,1.4);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Saturn
    glColor3f(0.9f, 0.7f, 0.2f);
    glPushMatrix();
    glRotatef(latAngle*0.5, 0.0, 0.0, 1.0);
    glTranslatef(85.0, 5.0, -140.0);
    glScalef(1.2,1.2,1.2);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Uranus
    glColor3f( 0.6f, 0.8f, 0.9f);
    glPushMatrix();
    glRotatef(latAngle*0.4, 0.0, 0.0, 1.0);
    glTranslatef(102.5, 5.0, -140.0);
    glScalef(1.1,1.1,1.1);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    // Neptune
    glColor3f( 0.2f, 0.4f, 1.0f);
    glPushMatrix();
    glRotatef(latAngle*0.3, 0.0, 0.0, 1.0);
    glTranslatef(120.0, 5.0, -140.0);
    glScalef(1.08,1.08,1.08);
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
   //if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
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
	//if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
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
/*
	// Move spacecraft to next position only if there will not be collision with an asteroid.
	if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
	{
		isCollision = 0;
		xVal = tempxVal;
		zVal = tempzVal;
		angle = tempAngle;
	}
	else isCollision = 1;
*/
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

