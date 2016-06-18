#ifndef PLATFORM_H
#define PLATFORM_H

#include "compositeGraphic.h"

class Platform : public CompositeGraphic
{
public:
	Platform(float posX, float posY, float posZ, float height, float width, float depth);
	void setTexture(std::string texture);
	~Platform();
};

#endif