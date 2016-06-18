#include "mySphere.h"
#include "tga.h"
#include <iostream>


mySphere::mySphere(float radius, unsigned int slices, unsigned int stacks, MyPoint position)
{
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
	this->position = position;
	this->inity = position.posY;
}


mySphere::~mySphere()
{
}

void mySphere::draw()
{
	GLfloat blankMaterial[] = { 0.0, 0.0, 0.0 };
	GLfloat redDiffuseMaterial[] = { 1.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
	glPushMatrix();
		glTranslatef(this->position.posX, this->position.posY, this->position.posZ);
		glutSolidSphere(this->radius, this->slices, this->stacks);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
}

void mySphere::move(float x, float y , float z)
{
	position.posX += x;
	position.posY += y;
	position.posZ += z;
}

void mySphere::scale(float, float, float){


}

void mySphere::rotate(MyPoint basePoint, float transformAngle, char axis)
{

}

void mySphere::jump(float velocity, vector<Platform> p)
{
	vector<Platform> platforms = p;

	//Collision detection (is the character coliding with the plattforms)

	// Falling of the edge
	if (!isFalling && !isJumping)
	{
		for (vector<Platform>::iterator it = platforms.begin(); it < platforms.end(); it++) {

			//Check if x position of character is not on top of a plattform
			if (!((this->position.posX > (*it).LeftTop.posX) && (this->position.posX < (*it).RightTop.posX)))
			{
				this->isFalling = true;
			}
		}
	}
	// Starts Jumping
	else if ((this->position.posY <= this->inity + velocity) && (this->isJumping) && (!isFalling))
	{
		this->move(0, .005f, 0);
	}
	// Starts Falling after jumping
	else if ((this->position.posY >= this->inity + velocity) && (this->isJumping) && (!isFalling))
	{
		this->isFalling = true;
	}
	//Drops below the level
	else if ((isFalling) && (this->position.posY < -10))
	{
		//Game Over
		exit(0);
	}
	// Is currently Falling
	else if ((isFalling))
	{
		this->move(0, -.005f, 0);
		for (vector<Platform>::iterator it = platforms.begin(); it < platforms.end(); it++) {

			//Check if x position of character is on top of a plattform
			if (( this->position.posX > (*it).LeftTop.posX ) && (this->position.posX < (*it).RightTop.posX ))
			{
				//Check if y position of charcter toughing the plattform
				if ( (this->position.posY -0.5 >= (*it).LeftTop.posY - 0.5) && ( this->position.posY -0.5 <= (*it).LeftTop.posY + 0.5) )
				{
					this->isFalling = false;
					this->isJumping = false;
				}
			}
		}
	}
}
void mySphere::InitTexture()
{
	GLsizei w, h;
	int mode;
	tgaInfo* info2 = tgaLoad(texture);

	if (info2->status != TGA_OK) {
		fprintf(stderr, "error loading texture2 image: %d\n", info2->status);

		return;
	}
	if (info2->width != info2->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info2->width, info2->height);
		return;
	}

	mode = info2->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &texture2);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Upload the texture2 bitmap. 
	w = info2->width;
	h = info2->height;

	//reportGLError("before uploading texture2");

	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info2->imageData);
	//reportGLError("after uploading texture2");

	tgaDestroy(info2);
}

void mySphere::setTexture(std::string texture)
{
	char* cstr = new char[texture.length() + 1];
	strcpy_s(cstr, texture.length() + 1, texture.c_str());
	this->texture = cstr;
	InitTexture();
}