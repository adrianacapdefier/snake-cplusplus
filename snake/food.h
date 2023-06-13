#pragma once

#include "point2d.h"
#include <string>

class Food
{
	Point2D position;
public:
	
	Point2D getPosition() const;
	void setPosition(Point2D position);
	virtual std::string type()=0;
	virtual int score()=0;
	virtual ~Food() {};
};

