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
#include <time.h>

int window;
float rotation_x, rotation_y, rotation_z;
int animating = 1;
float rot = 0;
float velocity_y;
float x_movement = .01f;
mySphere *character = new mySphere(1.f, 20, 20, MyPoint(-12.f, -1.f, 1.f));
GLfloat light0_position[4] = { 0.5f, 0.5f, 10.f, 1.0f };
GLfloat light_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };

list<Platform*> platformlist = list<Platform*>();
Platform *p = new Platform(-12.f, -4.f, 1.f, 2.f, 7.f, 1.f);
Platform *p2 = new Platform(0.f, -1.f, 1.f, 2.f, 15.f, 1.f);

void moveLight();

void display(void)
{
	x_movement += 0.02f;
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Move the world
	glTranslatef(0, -7, -30);
	
	// lets the character jump if velocity_y is > 0
	character->jump(velocity_y, platformlist);
	
	//Draws all platforms in list
	for (list<Platform*>::iterator it = platformlist.begin(); it != platformlist.end(); it++) {
		(*it)->draw();
		(*it)->move(-0.2,0,0);
	}

	float rightEnd = platformlist.back()->RightTop.posX;

	//If the newest platform moves under a certain x value, create another platform and add it to the list
	if (rightEnd <= 12.0f) {
		Platform *platform = new Platform(12.2 + rand() % 7, -3 + rand() % 6, 1, 2, 3 + rand() % 8, 1);
		platformlist.push_back(platform);
	}


	float leftEnd = platformlist.front()->LeftTop.posX;
	//If the oldest platform moves under a certain x value it will be destroyed
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

//60 Frames Per Second
void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60, &timer, 1);
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
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	//Makes light darker if further away
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);
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
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("EndlessRunner");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutTimerFunc(1000 / 60.0, &timer, 1);
	init(800, 600);
	srand(time(time_t()));
	p->setTexture("wall.tga");
	p2->setTexture("wall.tga");
	platformlist.push_back(p);
	platformlist.push_back(p2);
	glutMainLoop();
	return 0;
}

/* Our lightsource spins around the character*/
void moveLight()
{
	rot -=5;
	if (rot <= -360) {
		rot = 0;
	}
	glPushMatrix();
	glTranslatef(character->position.posX, character->position.posY, character->position.posZ);
	glRotatef(rot, 0, 0, 1);
	GLfloat light0_pos[4] = { 1  , 1 , 1, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glPopMatrix();
}

Main::Main()
{
}


Main::~Main()
{
}
