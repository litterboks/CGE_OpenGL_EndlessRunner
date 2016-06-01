#ifndef HOUSE_H
#define HOUSE_H

#include <iterator>
#include <list>

#include "compositeGraphic.h"

class House : public CompositeGraphic {
private:

public:
	House(float x,float y,float z);
	~House();
	void rotate(float x);
};

#endif