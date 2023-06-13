#pragma once

#include "food.h"
#include "grapes.h"

class Grapes : public Food {
public:
	std::string type() override {
		return GRAPES_IMG_PATH;
	}
	int score() override {
		return GRAPES_SCORE;
	}
};
