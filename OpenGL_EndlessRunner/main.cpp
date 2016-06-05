#include <Windows.h>
#include <stdio.h>

#include <glut.h>

#include "myrectangle.h"
#include "house.h"
#include "houserow.h"

#include "main.h"

int window;
float rotation_x, rotation_y, rotation_z;
int animating = 1;
float rot = 0;
//House h1 = House(.0f, -1.0f, 1.0f);
MyTriangle *t1 = new MyTriangle(MyPoint(-1.0f, 0.0f, .0f), MyPoint(.0f, 1.0f, .0f), MyPoint(1.0f, .0f, .0f));
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 0, -15);
	glPushMatrix();
	glRotatef(rot, 0, 1, 0);
	rot += .3f;
	t1->draw();
	glPopMatrix();
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void init(int width, int height)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 1 };
	GLfloat light_position[] = { 0, 0, -8, 0.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	resize(width, height);
	t1->setTexture("roof.tga"); 
	t1->mapTexture(0, 0.f, 0.f);
	t1->mapTexture(1, 1.f, 0.f);
	t1->mapTexture(2, 1.f, 1.f);
}

void keyPressed(unsigned char key, int x, int y)
{

	if (key == 27) {
		glutDestroyWindow(window);
		exit(0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("EndlessRunner");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	init(640, 480);
	glutMainLoop();
	return 0;
}