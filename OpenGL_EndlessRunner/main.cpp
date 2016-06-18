#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <vector>

#include "myrectangle.h"
#include "mySphere.h"
#include "Platform.h"
#include "main.h"
using namespace std;
int window;
float rotation_x, rotation_y, rotation_z;
int animating = 1;
float rot = 0;
float velocity_y;
mySphere *character = new mySphere(1.f, 20, 20, MyPoint(-5.f, -1.f, 1.f));
vector<Platform> platforms;
Platform *p = new Platform(-2.f, -1.f, 1.f, 2.f, 5.f, 2.f);

void display(void)
{
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	character->jump(velocity_y);
	character->draw();
	for (vector<Platform>::iterator it = platforms.begin(); it < platforms.end(); it++) {
		it->draw();
	}
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
	GLfloat mat_shininess[] = { 5.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

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
}

void keyPressed(unsigned char key, int x, int y)
{

	if (key == 27) {
		glutDestroyWindow(window);
		exit(0);
	}
	else if (key == 32)
	{
		if (!character->isJumping)
		{
			velocity_y = 5.f;
			character->isJumping = true;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("EndlessRunner");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	init(640, 480);
	p->setTexture("roof.tga");
	platforms.push_back(*p);
	glutMainLoop();
	return 0;
}