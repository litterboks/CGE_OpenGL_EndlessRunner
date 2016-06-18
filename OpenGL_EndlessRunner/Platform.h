#ifndef PLATFORM_H
#define PLATFORM_H

#include "compositeGraphic.h"

//The Platform is a Composite Graphic Class, it has a list of 6 MyRectangles which form a cuboid.
//Every transformation applied to the Platform will be applied to it's childen -> MyRectangles -> MyTriangles

class Platform : public CompositeGraphic
{
public:

	//Contructor with position of lower left point's coordinates, height, width and depth where depth
	Platform(float posX, float posY, float posZ, float height, float width, float depth);

	//Applies the texture to all subobjects
	void setTexture(std::string texture);
	~Platform();
	void move(float x, float y, float z);
	MyPoint LeftTop;
	MyPoint RightTop;
};

#endif
