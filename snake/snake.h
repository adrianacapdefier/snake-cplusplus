#pragma once

#include <list>
#include <string>
#include "point2d.h"
#include "position.h"
#include "direction.h"
#include "config.h"

class Snake
{
	Direction direction;
	std::list<Position> body;

public:
	Snake() {
		initBody();
	}
	void move();
	std::list<Position> getBody() const;
	Direction getDirection() const;
	void setDirection(Direction direction);
	void insertNode();

private:
	void initBody();
    void goUp();
    void goRight();
    void goDown();
    void goLeft();
};

