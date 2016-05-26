#ifndef HOUSEROW_H
#define HOUSEROW_H

#include "compositeGraphic.h"
#include <iterator>
#include <list>

class HouseRow : public CompositeGraphic {
public:
	HouseRow(float x, float y, float z, float distance, int count);
};

#endif