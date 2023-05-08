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
std::vector<glm::vec3> points = {
glm::vec3(0.0, 0.0, 0.0),  // sun
glm::vec3(0.0, 0.0, 40.0), // mercury
glm::vec3(0.0, 0.0, 50.0),  // venus
glm::vec3(0.0, 0.0, 62.0), // earth
glm::vec3(0.0, 10.0, 62.0), // moon
glm::vec3(0.0, 0.0, 75.0),  // mars
glm::vec3(0.0, 0.0, 100.0), // jupiter
glm::vec3(0.0, 0.0, 140.0),  // saturn
glm::vec3(0.0, 0.0, 170.0), // uranus
glm::vec3(0.0, 0.0, 190.0)  // neptune
};
GLfloat solar_diffuses[][4] = {
{1.0, 1.0, 0.0, 1.0}, // sun
{0.6f, 0.6f, 0.6f, 1.0}, // mercury
{0.8f, 0.5f, 0.2, 1.0}, // venus
{0.0f, 0.5f, 1.0f, 1.0}, // earth
{0.8f, 0.8f, 0.8f, 1.0}, // moon
{1.0f, 0.2f, 0.0f, 1.0},
{0.8f, 0.6f, 0.4f, 1.0},
{1.0f, 0.9f, 0.6f, 1.0},
{0.6f, 0.9f, 0.9f, 1.0},
{0.2f, 0.4f, 1.0f, 1.0}};
GLfloat rotation[] = {0.0,1.59,1.17,1.0,1.0,0.8,0.46,0.33,0.228,0.182};
std::vector<GLfloat> sizePlanet = {5.0,0.4,0.9,1.0,0.25,0.6,3.0,2.8,1.25,1.2};

static int width, height; // Size of the OpenGL window.
static float latAngle = 0.0; // Latitudinal angle.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
static float angle = 90.0 , xVal = 220, zVal = 0; // Angle & Co-ordinates of the spacecraft.
static unsigned int spacecraft; // Display lists base index.
static unsigned int sphere;

// lighting
static float d = 3.0; // Diffuse and specular white light intensity.
static int localViewer = 1; // Local viewpoint?
static float p = 1.0; // Positional light?
static float t = 0.0; // Quadratic attenuation factor.
// Initialization routine.
void setup(void)
{
    glEnable(GL_DEPTH_TEST);

	spacecraft = glGenLists(1);
	glNewList(spacecraft, GL_COMPILE);
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
	glScalef(2.0,2.0,2.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCone(5.0, 10.0, 10, 10);
	glPopMatrix();
	glEndList();

    sphere = glGenLists(2);
    glNewList(sphere,GL_COMPILE);
    glutSolidSphere(6, 50, 60);
    glEndList();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);
	// Material property vectors.
	float matAmbAndDif[] = { 0.0, 0.0, 0.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
	float matShine[] = { 100.0 };
	// Material properties of ball.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
	// Cull back faces.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void drawingSystem(void){
    // sun
    glColor3f(1.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, solar_diffuses[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, solar_diffuses[0]);
    glPushMatrix();
    glTranslatef(points[0].x,points[0].y,points[0].z);
    glScalef(sizePlanet[0],sizePlanet[0],sizePlanet[0]);
    glCallList(sphere); // Execute display list.
    glPopMatrix();
    glEnable(GL_LIGHTING);
    // draw planets and moon
    for(int i=1;i<10;i++){
        glMaterialfv(GL_FRONT, GL_AMBIENT, solar_diffuses[i]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, solar_diffuses[i]);
        glPushMatrix();
        glRotatef(latAngle*rotation[i], 0.0, 1.0, 0.0);
        if(i == 4) glRotatef(50*latAngle, 0.0, 0.0, 1.0); // control rotation of moon around earth
        glTranslatef(points[i].x,points[i].y,points[i].z);
        glScalef(sizePlanet[i],sizePlanet[i],sizePlanet[i]);
        glCallList(sphere);
        if(i == 7){// draw ring around saturn
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(40.0,1.0,0.0,0.0);
            glutSolidTorus(1.0, 7.0, 5, 20);
        }
        glPopMatrix();
    }
}

// Drawing routine.
void drawScene(void)
{
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec0[] = { d, d, d, 1.0 };
	float lightPos0[] = { 0.0, 0.0, 0.0, p };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer); // Enable local viewpoint
	glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Begin right viewport.
	glViewport(0, 0, width , height);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);
	glLoadIdentity();
    // Fixed camera.
    gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 10 * cos((M_PI / 180.0) * angle),
		xVal - 11 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 11 * cos((M_PI / 180.0) * angle),
		0.0,
		1.0,
		0.0);
    glDisable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	// Draw solar system.
    drawingSystem();
	// End space craft viewport.

	// Begin plane viewport.
    glViewport(3.0 * width / 4.0, 0, width / 3.0, height/3.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);
    glLoadIdentity();

    // separate two views
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5.0);
    glBegin(GL_LINES); // Draw vertical line.
    glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);
    glEnd();
    glBegin(GL_LINES); // Draw horizontal line.
	glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glEnd();
	glLineWidth(1.0);

    // Fixed camera.
    gluLookAt(0.0, 250.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Draw spacecraft.
    glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(xVal, 0.0, zVal);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(spacecraft);
	glPopMatrix();

	glDisable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    // Draw solar systems
    drawingSystem();
	// End plane viewport.

	glutSwapBuffers();
}
// Timer function.
void animate(int value)
{
	if (isAnimate)
	{
		latAngle += 1.0;

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
    case 'p':
		if (p) p = 0.0; else p = 1.0;
		glutPostRedisplay();
		break;
	case 'P':
		if (p) p = 0.0; else p = 1.0;
		glutPostRedisplay();
		break;
	case 'd':
		if (d > 0.0) d -= 0.05;
		glutPostRedisplay();
		break;
	case 'D':
		if (d < 3.0) d += 0.05;
		glutPostRedisplay();
		break;
    case 'l':
		if (localViewer) localViewer = 0; else localViewer = 1;
		glutPostRedisplay();
		break;
	case 'L':
		if (localViewer) localViewer = 0; else localViewer = 1;
		glutPostRedisplay();
		break;
    case 't':
		if (t > 0.0) t -= 0.01;
		glutPostRedisplay();
		break;
	case 'T':
		t += 0.01;
		glutPostRedisplay();
		break;
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
// OpenGL window reshape routine.
void resize(int w, int h)
{
    // Pass the size of the OpenGL window.
	width = w;
	height = h;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -5.0, 5.0, 5.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System Simulation.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

