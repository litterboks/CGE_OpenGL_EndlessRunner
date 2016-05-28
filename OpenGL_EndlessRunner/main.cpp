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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 0, -15);
	glRotatef(rotation_x, 1, 0, 0);
	glRotatef(rotation_y, 0, 1, 0);
	glRotatef(rotation_z, 0, 0, 1);
	/*MyRectangle* r1 = new MyRectangle(-1.0f, 0.0f, 1.0f, 4.0f, 4.0f, 0, 0, 0);
	r1->setTexture("house.tga");
	r1->draw();*/
	HouseRow* hr1 = new HouseRow(-12.0f, 1.0f, 1.0f, 4.0f, 8);
	hr1->draw();

	hr1->move(0.0f, -4.0f, 0.0f);
	hr1->draw();
	hr1->move(0.0f, 12.0f, 0.0f);
	hr1->scale(0.5f, 0.5f, 0.5f);
	hr1->draw();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
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
	GLfloat light_position[] = { -1, 0, 1, 0.0 };

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