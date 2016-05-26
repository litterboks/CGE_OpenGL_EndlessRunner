#include "houserow.h"
#include "house.h"

HouseRow::HouseRow(float x, float y, float z, float distance, int count)
{
	float limit = count*distance;

	for (float i = 0; i < limit; i = i + distance) {
		House* h1 = new House(x+i, y, z);
		this->add(h1);
	}
}
