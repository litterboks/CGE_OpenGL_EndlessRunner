#ifndef HOUSE_H
#define HOUSE_H

#include <iterator>
#include <list>

#include "compositeGraphic.h"

class House : public CompositeGraphic {
public:
	House(float x,float y,float z);
};

#endif