#include "food.h"
#include "position.h"
#include <string>


Point2D Food::getPosition() const {
	return position;
}

void Food::setPosition(Point2D position) {
	this->position = position;
}