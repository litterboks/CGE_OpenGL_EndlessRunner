#include "compositeGraphic.h"

void CompositeGraphic::add(Graphic * graphic)
{
	this->_graphic.push_back(graphic);
}

void CompositeGraphic::remove(Graphic * graphic)
{
	this->_graphic.remove(graphic);
}

typename std::list<typename Graphic*>::iterator* CompositeGraphic::CreateIterator()
{
	return new std::list<typename Graphic*>::iterator();
}

void CompositeGraphic::draw() {
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		(*it)->draw();
	}
}

void CompositeGraphic::move(float x, float y, float z)
{
	
	for (std::list<Graphic*>::iterator it = this->_graphic.begin(); it != this->_graphic.end(); it++) {
		(*it)->move(x,y,z);
	}
}

void CompositeGraphic::scale(float x, float y, float z)
{
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		(*it)->scale(x,y,z);
	}
}

CompositeGraphic::CompositeGraphic(float x, float y, float z) {
	this->position.posX = x;
	this->position.posY = y;
	this->position.posZ = z;
}