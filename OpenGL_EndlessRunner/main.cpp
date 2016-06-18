#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <vector>

#include "myrectangle.h"
#include "mySphere.h"
#include "Platform.h"
#include <math.h>
#include "main.h"

int window;
float rotation_x, rotation_y, rotation_z;
int animating = 1;
float rot = 0;
float velocity_y;
float x_movement = .01f;
mySphere *character = new mySphere(1.f, 20, 20, MyPoint(-12.f, -1.f, 1.f));
GLfloat light0_position[4] = { 1.0, 1.0, 10.0, 1.0 };

list<Platform*> platformlist = list<Platform*>();
Platform *p = new Platform(-12.f, -4.f, 1.f, 2.f, 7.f, 1.f);
Platform *p2 = new Platform(0.f, -1.f, 1.f, 2.f, 15.f, 1.f);

void moveLight();

void display(void)
{
	x_movement += 0.001f;
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Move the world
	glTranslatef(0, 0, -30);
	
	// lets the character jump if velocity_y is > 0
	character->jump(velocity_y, platformlist);

	for (list<Platform*>::iterator it = platformlist.begin(); it != platformlist.end(); it++) {
		(*it)->draw();
		(*it)->move(-0.005,0,0);
	}

	float rightEnd = platformlist.back()->RightTop.posX;

	if (rightEnd <= 12.0f) {
		Platform *platform = new Platform(12 + rand() % 7, -3 + rand() % 6, 1, 2, 3 + rand() % 8, 1);
		platformlist.push_back(platform);
	}

	float leftEnd = platformlist.front()->LeftTop.posX;

	if (leftEnd <= -100) {
		Platform *platform = platformlist.front();
		delete platform;
		platformlist.pop_front();
	}
	
	// Move the light around the character
	moveLight();
	character->draw();

	glutSwapBuffers();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60.0, &timer, 1);
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

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

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
			velocity_y = character->position.posY + 5.f;
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
	glutTimerFunc(1000 / 60.0, &timer, 1);
	init(640, 480);
	srand(time_t());
	p->setTexture("roof.tga");
	p2->setTexture("roof.tga");
	platformlist.push_back(p);
	platformlist.push_back(p2);
	glutMainLoop();
	return 0;
}

void moveLight()
{
	rot += .05;
	glPushMatrix();
	glTranslatef(character->position.posX, character->position.posY, character->position.posZ);
	glRotatef(rot, 0, 0, 1);
	GLfloat light0_pos[4] = { light0_position[0] - character->position.posX, light0_position[1] - character->position.posY, light0_position[2] - character->position.posZ, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glPopMatrix();
}

Main::Main()
{
}


Main::~Main()
{
}
