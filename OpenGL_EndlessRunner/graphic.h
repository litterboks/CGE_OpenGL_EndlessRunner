#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <list>
#include "mypoint.h"

//Graphic class, all graphics should be derived from this class to ensure they all can be accesed in the same way

class Graphic {
public:
	//Destructor has to be implemented in every derived class
	virtual ~Graphic();

	const char* Name() {
		return _name;
	}

	//draws the graphic
	virtual void draw();

	//move the graphic on screen
	virtual void move(float,float,float);

	//scales the graphic
	virtual void scale(float,float,float);

	//rotates the graphic around a basePoint, angle are degrees, axis is a char x,y or z
	virtual void rotate(MyPoint basePoint, float angle, char axis);

	//adds subgraphics to this graphic, implemented in compositeGraphic, empty implementation for base graphics like triangle or rectangle
	virtual void add(Graphic* graphic);
	//removes subgraphics
	virtual void remove(Graphic* graphic);

	//assigns a texture to this graphic via texture file name
	virtual void setTexture(std::string texture);

protected:
	Graphic();

private:
	const char* _name;
};

#endif